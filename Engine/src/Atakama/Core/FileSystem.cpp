#include "FileSystem.hpp"

#include "Args.hpp"

namespace Atakama
{

const std::filesystem::path FileSystem::GetBinaryPath()
{
  return std::filesystem::weakly_canonical(std::filesystem::path(GetArgv()[0])).parent_path();
}

const std::filesystem::path FileSystem::GetShaderPath()
{
  return FileSystem::GetBinaryPath() / "shaders";
}

const std::filesystem::path FileSystem::GetShaderFile(const std::string& file)
{
  return FileSystem::GetShaderPath() / file;
}

const std::filesystem::path FileSystem::GetTexturePath()
{
  return FileSystem::GetBinaryPath() / "assets" / "textures";
}

const std::filesystem::path FileSystem::GetModelPath()
{
  return FileSystem::GetBinaryPath() / "assets" / "models";
}

const std::filesystem::path FileSystem::GetConfigsPath()
{
	return FileSystem::GetBinaryPath() / "configs";
}

const std::filesystem::path FileSystem::GetImGuiInitPath()
{
	return FileSystem::GetConfigsPath() / "imgui.ini";
}

}
