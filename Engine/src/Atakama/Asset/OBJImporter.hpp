#ifndef ATAKAMA_OBJ_IMPORTER_HPP
#define ATAKAMA_OBJ_IMPORTER_HPP

#include <Atakama/Engine/Vertex.hpp>

namespace Atakama
{

class OBJImporter
{
public:
    OBJImporter() = default;
    bool Import(const std::filesystem::path& path, std::vector<Vertex>& vertices, std::vector<uint32_t>& indices);
};

}

#endif