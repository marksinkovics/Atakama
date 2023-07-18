#ifndef ATAKAMA_EDITOR_ICON_MAP_HPP
#define ATAKAMA_EDITOR_ICON_MAP_HPP

namespace Atakama
{

class Texture;

namespace Editor
{

class IconMap
{
public:
	enum class Icon
	{
		Cursor,
		Move,
		Rotate,
		Scale,
	};

public:
	IconMap(const std::filesystem::path& path, float size, float tileSize);
	~IconMap() = default;

	uint32_t GetId();

	glm::vec2 GetUVStartPos(Icon icon);
	glm::vec2 GetUVEndPos(Icon icon);
	glm::ivec2 GetIndices(Icon icon);

private:
	float m_TileOffset;
	Ref<Texture> m_IconMap;
};

}

}

#endif

