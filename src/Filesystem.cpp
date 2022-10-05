#include "Filesystem.hpp"
#include "Args.hpp"

namespace OGLSample
{

const std::filesystem::path FileSystem::GetBinaryPath()
{
  return std::filesystem::weakly_canonical(std::filesystem::path(GetArgv()[0])).parent_path();
}

const std::filesystem::path FileSystem::GetShaderPath()
{
  return FileSystem::GetBinaryPath() / "shaders";
}

const std::filesystem::path FileSystem::GetTexturePath()
{
  return FileSystem::GetBinaryPath() / "assets" / "textures";
}

}
