
#include "IconMap.hpp"

#include <Atakama/Core/FileSystem.hpp>
#include <Atakama/Engine/Texture.hpp>

namespace Atakama::Editor
{

	IconMap::IconMap(const std::filesystem::path& path, float size, float tileSize)
{
	m_TileOffset = 1.f / (size / tileSize);
	m_IconMap = Texture2D::Create(path);
}

uint32_t IconMap::GetId()
{
	return m_IconMap->GetId();
}
glm::vec2 IconMap::GetUVStartPos(Icon icon)
{
	glm::ivec2 indices = GetIndices(icon);
	return glm::vec2(indices.x * m_TileOffset, indices.y * m_TileOffset);
}

glm::vec2 IconMap::GetUVEndPos(Icon icon)
{
	glm::ivec2 indices = GetIndices(icon);
	return glm::vec2((indices.x + 1) * m_TileOffset, (indices.y + 1) * m_TileOffset);
}

glm::ivec2 IconMap::GetIndices(Icon icon)
{
	glm::ivec2 result;
	switch (icon) 
	{
		case Icon::Cursor: return { 0, 0 };
		case Icon::Move: return { 1, 0 };
		case Icon::Rotate: return { 2, 0 };
		case Icon::Scale: return { 3, 0 };
	}
}

}
