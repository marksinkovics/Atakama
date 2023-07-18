//
//	Based on: 
//		* https://github.com/Limeoats/L2DFileDialog
//		* https://github.com/Iam1337/ImGui-FileDialog
//

#pragma once

#include <chrono>
#include <string>
#include <filesystem>
#include <sstream>

#include "FileDialog.hpp"

using namespace std::chrono_literals;


enum ImGuiFileDialogSortOrder
{
	Up,
	Down,
	None
};

struct HumanReadable 
{
	std::uintmax_t size{};

	std::string str()
	{
		std::stringstream stream;
		stream << *this;
		return stream.str();
	}

private: 
	friend std::ostream& operator<<(std::ostream& os, HumanReadable hr) 
	{
		int i{};
		double mantissa = hr.size;
		for (; mantissa >= 1024.; mantissa /= 1024., ++i) {}
		mantissa = std::ceil(mantissa * 10.) / 10.;
		if (i == 0) 
		{
			return os << hr.size << " B";
		}
		os << mantissa << " " << "BKMGTPE"[i] << "B";
		return os;
	}
};

void RefreshInfo(FileDialogInfo* dialogInfo)
{
	dialogInfo->refreshInfo = false;
	dialogInfo->currentIndex = 0;
	dialogInfo->currentFiles.clear();
	dialogInfo->currentDirectories.clear();

	for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(dialogInfo->directoryPath))
	{
		if (entry.is_directory())
		{
			dialogInfo->currentDirectories.push_back(entry);
		}
		else
		{
			dialogInfo->currentFiles.push_back(entry);
		}
	}
}

bool ImGui::FileDialog(bool* open, FileDialogInfo* dialogInfo)
{
	if (!*open) return false;

	static float initialSpacingColumn0 = 230.0f;
	static float initialSpacingColumn1 = 80.0f;
	static float initialSpacingColumn2 = 90.0f;
	static ImGuiFileDialogSortOrder fileNameSortOrder = ImGuiFileDialogSortOrder::None;
	static ImGuiFileDialogSortOrder sizeSortOrder = ImGuiFileDialogSortOrder::None;
	static ImGuiFileDialogSortOrder dateSortOrder = ImGuiFileDialogSortOrder::None;
	static ImGuiFileDialogSortOrder typeSortOrder = ImGuiFileDialogSortOrder::None;

	assert(dialogInfo != nullptr);

	bool complete = false;

	ImGui::PushID(dialogInfo);
	ImGui::SetNextWindowSize(ImVec2(740.0f, 410.0f), ImGuiCond_FirstUseEver);

	if (ImGui::Begin(dialogInfo->title.c_str(), open))
	{
        if ((dialogInfo->currentFiles.empty() && dialogInfo->currentDirectories.empty()) || dialogInfo->refreshInfo)
			RefreshInfo(dialogInfo);

		// Draw path
		ImGui::Text("Path: "); ImGui::SameLine();
		static const size_t pathBufferSize = 200;
		static char pathBuffer[pathBufferSize];
		size_t pathSize = std::max(pathBufferSize - 1, dialogInfo->directoryPath.string().size());
		std::strncpy(pathBuffer, dialogInfo->directoryPath.string().c_str(), pathSize);
		ImGui::PushItemWidth(-FLT_MIN);
		ImGuiInputTextFlags pathInputTextFlags = ImGuiInputTextFlags_EnterReturnsTrue;
		if (ImGui::InputText("##path", pathBuffer, IM_ARRAYSIZE(pathBuffer), pathInputTextFlags))
		{
			dialogInfo->directoryPath = std::filesystem::path(pathBuffer);
			dialogInfo->fileName.clear();
			RefreshInfo(dialogInfo);
		}

		ImGui::BeginChild("##browser", ImVec2(ImGui::GetWindowContentRegionWidth(), 300), true, ImGuiWindowFlags_HorizontalScrollbar);
		ImGui::Columns(4);

		// Columns size
		if (initialSpacingColumn0 > 0)
		{
			ImGui::SetColumnWidth(0, initialSpacingColumn0);
			initialSpacingColumn0 = 0.0f;
		}
		if (initialSpacingColumn1 > 0)
		{
			ImGui::SetColumnWidth(1, initialSpacingColumn1);
			initialSpacingColumn1 = 0.0f;
		}
		if (initialSpacingColumn2 > 0)
		{
			ImGui::SetColumnWidth(2, initialSpacingColumn2);
			initialSpacingColumn2 = 0.0f;
		}

		// File Columns
		if (ImGui::Selectable("Name"))
		{
			sizeSortOrder = ImGuiFileDialogSortOrder::None;
			dateSortOrder = ImGuiFileDialogSortOrder::None;
			typeSortOrder = ImGuiFileDialogSortOrder::None;
			fileNameSortOrder = fileNameSortOrder == ImGuiFileDialogSortOrder::Down ? ImGuiFileDialogSortOrder::Up : ImGuiFileDialogSortOrder::Down;
		}
		ImGui::NextColumn();
		if (ImGui::Selectable("Size"))
		{
			fileNameSortOrder = ImGuiFileDialogSortOrder::None;
			dateSortOrder = ImGuiFileDialogSortOrder::None;
			typeSortOrder = ImGuiFileDialogSortOrder::None;
			sizeSortOrder = sizeSortOrder == ImGuiFileDialogSortOrder::Down ? ImGuiFileDialogSortOrder::Up : ImGuiFileDialogSortOrder::Down;
		}
		ImGui::NextColumn();
		if (ImGui::Selectable("Type"))
		{
			fileNameSortOrder = ImGuiFileDialogSortOrder::None;
			dateSortOrder = ImGuiFileDialogSortOrder::None;
			sizeSortOrder = ImGuiFileDialogSortOrder::None;
			typeSortOrder = typeSortOrder == ImGuiFileDialogSortOrder::Down ? ImGuiFileDialogSortOrder::Up : ImGuiFileDialogSortOrder::Down;
		}
		ImGui::NextColumn();
		if (ImGui::Selectable("Date"))
		{
			fileNameSortOrder = ImGuiFileDialogSortOrder::None;
			sizeSortOrder = ImGuiFileDialogSortOrder::None;
			typeSortOrder = ImGuiFileDialogSortOrder::None;
			dateSortOrder = dateSortOrder == ImGuiFileDialogSortOrder::Down ? ImGuiFileDialogSortOrder::Up : ImGuiFileDialogSortOrder::Down;
		}
		ImGui::NextColumn();

		// File Separator
		ImGui::Separator();

		// Sort directories
		auto* directories = &dialogInfo->currentDirectories;

		if (fileNameSortOrder != ImGuiFileDialogSortOrder::None || sizeSortOrder != ImGuiFileDialogSortOrder::None || typeSortOrder != ImGuiFileDialogSortOrder::None)
		{
			std::sort(directories->begin(), directories->end(), [](const std::filesystem::directory_entry& a, const std::filesystem::directory_entry& b)
				{
					if (fileNameSortOrder == ImGuiFileDialogSortOrder::Down)
					{
						return a.path().filename() > b.path().filename();
					}

					return a.path().filename() < b.path().filename();
				});
		}
		else if (dateSortOrder != ImGuiFileDialogSortOrder::None)
		{
			std::sort(directories->begin(), directories->end(), [](const std::filesystem::directory_entry& a, const std::filesystem::directory_entry& b)
				{
					if (dateSortOrder == ImGuiFileDialogSortOrder::Down)
					{
						return a.last_write_time() > b.last_write_time();
					}
					return a.last_write_time() < b.last_write_time();
				});
		}

		// Sort files
		auto* files = &dialogInfo->currentFiles;

		if (fileNameSortOrder != ImGuiFileDialogSortOrder::None)
		{
			std::sort(files->begin(), files->end(), [](const std::filesystem::directory_entry& a, const std::filesystem::directory_entry& b)
				{
					if (fileNameSortOrder == ImGuiFileDialogSortOrder::Down)
					{
						return a.path().filename() > b.path().filename();
					}

					return a.path().filename() < b.path().filename();
				});
		}
		else if (sizeSortOrder != ImGuiFileDialogSortOrder::None)
		{
			std::sort(files->begin(), files->end(), [](const std::filesystem::directory_entry& a, const std::filesystem::directory_entry& b)
				{
					if (sizeSortOrder == ImGuiFileDialogSortOrder::Down)
					{
						return a.file_size() > b.file_size();
					}
					return a.file_size() < b.file_size();
				});
		}
		else if (typeSortOrder != ImGuiFileDialogSortOrder::None)
		{
			std::sort(files->begin(), files->end(), [](const std::filesystem::directory_entry& a, const std::filesystem::directory_entry& b)
				{
					if (typeSortOrder == ImGuiFileDialogSortOrder::Down)
					{
						return a.path().extension() > b.path().extension();
					}

					return a.path().extension() < b.path().extension();
				});
		}
		else if (dateSortOrder != ImGuiFileDialogSortOrder::None)
		{
			std::sort(files->begin(), files->end(), [](const std::filesystem::directory_entry& a, const std::filesystem::directory_entry& b)
				{
					if (dateSortOrder == ImGuiFileDialogSortOrder::Down)
					{
						return a.last_write_time() > b.last_write_time();
					}
					return a.last_write_time() < b.last_write_time();
				});
		}

		size_t index = 0;

		// Draw parent
		if (dialogInfo->directoryPath.has_parent_path())
		{
			if (ImGui::Selectable("..", dialogInfo->currentIndex == index, ImGuiSelectableFlags_AllowDoubleClick | ImGuiSelectableFlags_SpanAllColumns, ImVec2(ImGui::GetWindowContentRegionWidth(), 0)))
			{
				dialogInfo->currentIndex = index;

				if (ImGui::IsMouseDoubleClicked(0))
				{
					dialogInfo->directoryPath = dialogInfo->directoryPath.parent_path();
					dialogInfo->refreshInfo = true;
				}
			}
			ImGui::NextColumn();
			std::string fileSizeStr("-");
			float fileSizeTextWidth = ImGui::CalcTextSize(fileSizeStr.c_str()).x;
			ImGui::SetCursorPosX(ImGui::GetCursorPosX() + ImGui::GetContentRegionAvail().x - fileSizeTextWidth);
			ImGui::TextUnformatted(fileSizeStr.c_str());
			ImGui::NextColumn();
			ImGui::TextUnformatted("<parent>");
			ImGui::NextColumn();
			ImGui::TextUnformatted("-");
			ImGui::NextColumn();

			index++;
		}

		// Draw directories
		for (size_t i = 0; i < directories->size(); ++i)
		{
			auto directoryEntry = dialogInfo->currentDirectories[i];
			auto directoryPath = directoryEntry.path();
			auto directoryName = directoryPath.filename();

			if (ImGui::Selectable(directoryName.string().c_str(), dialogInfo->currentIndex == index, ImGuiSelectableFlags_AllowDoubleClick | ImGuiSelectableFlags_SpanAllColumns, ImVec2(ImGui::GetWindowContentRegionWidth(), 0)))
			{
				dialogInfo->currentIndex = index;

				if (ImGui::IsMouseDoubleClicked(0))
				{
					dialogInfo->directoryPath = directoryPath;
					dialogInfo->refreshInfo = true;
				}
			}

			ImGui::NextColumn();
			std::string fileSizeStr("-");
			float fileSizeTextWidth = ImGui::CalcTextSize(fileSizeStr.c_str()).x;
			ImGui::SetCursorPosX(ImGui::GetCursorPosX() + ImGui::GetContentRegionAvail().x - fileSizeTextWidth);
			ImGui::TextUnformatted(fileSizeStr.c_str());
			ImGui::NextColumn();
			ImGui::TextUnformatted("<directory>");
			ImGui::NextColumn();

			auto lastWriteTime = directoryEntry.last_write_time();
			auto st = std::chrono::time_point_cast<std::chrono::system_clock::duration>(lastWriteTime - decltype(lastWriteTime)::clock::now() + std::chrono::system_clock::now());
			std::time_t tt = std::chrono::system_clock::to_time_t(st);
			std::tm mt;
        #ifdef __APPLE__
            localtime_r(&tt, &mt);
        #else
			localtime_s(&mt, &tt);
        #endif
			std::stringstream ss;
			ss << std::put_time(&mt, "%F %R");
			ImGui::TextUnformatted(ss.str().c_str());
			ImGui::NextColumn();

			index++;
		}

		// Draw files
		for (size_t i = 0; i < files->size(); ++i)
		{
			auto fileEntry = dialogInfo->currentFiles[i];
			auto filePath = fileEntry.path();
			auto fileName = filePath.filename();

			if (ImGui::Selectable(fileName.string().c_str(), dialogInfo->currentIndex == index, ImGuiSelectableFlags_AllowDoubleClick | ImGuiSelectableFlags_SpanAllColumns, ImVec2(ImGui::GetWindowContentRegionWidth(), 0)))
			{
				dialogInfo->currentIndex = index;
				dialogInfo->fileName = fileName;
			}

			ImGui::NextColumn();

            std::string fileSizeStr {std::move(HumanReadable{fileEntry.file_size()}.str())};
			float fileSizeTextWidth = ImGui::CalcTextSize(fileSizeStr.c_str()).x;
			ImGui::SetCursorPosX(ImGui::GetCursorPosX() + ImGui::GetContentRegionAvail().x - fileSizeTextWidth);
			ImGui::TextUnformatted(fileSizeStr.c_str());
			ImGui::NextColumn();
			ImGui::TextUnformatted(filePath.extension().string().c_str());
			ImGui::NextColumn();

			auto lastWriteTime = fileEntry.last_write_time();
			auto st = std::chrono::time_point_cast<std::chrono::system_clock::duration>(lastWriteTime - decltype(lastWriteTime)::clock::now() + std::chrono::system_clock::now());
			std::time_t tt = std::chrono::system_clock::to_time_t(st);
			std::tm mt;
        #ifdef __APPLE__
            localtime_r(&tt, &mt);
        #else
            localtime_s(&mt, &tt);
        #endif
			std::stringstream ss;
			ss << std::put_time(&mt, "%F %R");
			ImGui::TextUnformatted(ss.str().c_str());
			ImGui::NextColumn();

			index++;
		}
		ImGui::EndChild();

		// Draw filename
		static const size_t fileNameBufferSize = 200;
		static char fileNameBuffer[fileNameBufferSize];

		std::string fileNameStr = dialogInfo->fileName.string();
		size_t fileNameSize = fileNameStr.size();

		if (fileNameSize >= fileNameBufferSize)	fileNameSize = fileNameBufferSize - 1;
		std::memcpy(fileNameBuffer, fileNameStr.c_str(), fileNameSize);
		fileNameBuffer[fileNameSize] = 0;

		ImGui::PushItemWidth(ImGui::GetWindowContentRegionWidth());
		if (ImGui::InputText("File Name", fileNameBuffer, fileNameBufferSize))
		{
			dialogInfo->fileName = std::string(fileNameBuffer);
			dialogInfo->currentIndex = 0;
		}

		if (ImGui::Button("Cancel"))
		{
			fileNameSortOrder = ImGuiFileDialogSortOrder::None;
			sizeSortOrder = ImGuiFileDialogSortOrder::None;
			typeSortOrder = ImGuiFileDialogSortOrder::None;
			dateSortOrder = ImGuiFileDialogSortOrder::None;

			dialogInfo->refreshInfo = false;
			dialogInfo->currentIndex = 0;
			dialogInfo->currentFiles.clear();
			dialogInfo->currentDirectories.clear();

			*open = false;
		}

		ImGui::SameLine();

		if (dialogInfo->type == FileDialogInfo::Type::OpenFile)
		{
			if (ImGui::Button("Open"))
			{
				dialogInfo->resultPath = dialogInfo->directoryPath / dialogInfo->fileName;

				if (std::filesystem::exists(dialogInfo->resultPath))
				{
					fileNameSortOrder = ImGuiFileDialogSortOrder::None;
					sizeSortOrder = ImGuiFileDialogSortOrder::None;
					typeSortOrder = ImGuiFileDialogSortOrder::None;
					dateSortOrder = ImGuiFileDialogSortOrder::None;

					dialogInfo->refreshInfo = false;
					dialogInfo->currentIndex = 0;
					dialogInfo->currentFiles.clear();
					dialogInfo->currentDirectories.clear();

					complete = true;
					*open = false;
				}
			}
		}
		else if (dialogInfo->type == FileDialogInfo::Type::SaveFile)
		{
			if (ImGui::Button("Save"))
			{
				dialogInfo->resultPath = dialogInfo->directoryPath / dialogInfo->fileName;

				if (!std::filesystem::exists(dialogInfo->resultPath))
				{
					fileNameSortOrder = ImGuiFileDialogSortOrder::None;
					sizeSortOrder = ImGuiFileDialogSortOrder::None;
					typeSortOrder = ImGuiFileDialogSortOrder::None;
					dateSortOrder = ImGuiFileDialogSortOrder::None;

					dialogInfo->refreshInfo = false;
					dialogInfo->currentIndex = 0;
					dialogInfo->currentFiles.clear();
					dialogInfo->currentDirectories.clear();

					complete = true;
					*open = false;
				}
			}
		}
	}

	ImGui::End();
	ImGui::PopID();

	return complete;
}
