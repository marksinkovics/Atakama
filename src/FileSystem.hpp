#ifndef FILESYSTEM_H
#define FILESYSTEM_H

namespace OGLSample
{

class FileSystem
{
public:
  static const std::filesystem::path GetBinaryPath();
  static const std::filesystem::path GetShaderPath();
  static const std::filesystem::path GetShaderFile(const std::string& file);
  static const std::filesystem::path GetTexturePath();
  static const std::filesystem::path GetModelPath();
};

}

#endif
