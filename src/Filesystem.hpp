#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <filesystem>

namespace OGLSample
{

class FileSystem
{
public:
  static const std::filesystem::path GetBinaryPath();
  static const std::filesystem::path GetShaderPath();
};

}

#endif
