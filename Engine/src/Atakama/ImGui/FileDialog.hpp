//
//	Based on: 
//		* https://github.com/Limeoats/L2DFileDialog
//		* https://github.com/Iam1337/ImGui-FileDialog
//

#ifndef ATAKAMA_FILE_DIALOG
#define ATAKAMA_FILE_DIALOG

#include <filesystem>
#include <imgui.h>

struct FileDialogInfo
{
	enum Type
	{
		OpenFile,
		SaveFile,
		COUNT
	};

	std::string title;
	Type type;

	std::filesystem::path fileName;
	std::filesystem::path directoryPath;
	std::filesystem::path resultPath;

	bool refreshInfo;
	size_t currentIndex;
	std::vector<std::filesystem::directory_entry> currentFiles;
	std::vector<std::filesystem::directory_entry> currentDirectories;
};

namespace ImGui
{
	IMGUI_API bool FileDialog(bool* open, FileDialogInfo* dialogInfo);
}

#endif