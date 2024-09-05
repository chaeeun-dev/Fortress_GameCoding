#include "pch.h"
#include "Tilemap.h"

Tilemap::Tilemap()
{
}

Tilemap::~Tilemap()
{
}

void Tilemap::LoadFile(const wstring& path)
{
}

void Tilemap::SaveFile(const wstring& path)
{
}

Tile* Tilemap::GetTileAt(Vec2Int pos)
{
	if (pos.x < 0 || pos.x >= _mapSize.x || pos.y < 0 || pos.y >= _mapSize.y)
		return nullptr;

	return &_tiles[pos.y][pos.x];	// 주소값을 넘겨줄 것임
}

void Tilemap::SetMapSize(Vec2Int size)
{
	_mapSize = size;

	_tiles = vector<vector<Tile>>(size.y, vector<Tile>(size.x));	// size를 세팅하고, _tiles도 다시 세팅해야 함

	for (int32 y = 0; y < size.y; y++)
	{
		for (int32 x = 0; x < size.x; x++)
		{
			_tiles[y][x] = Tile{ 0 };
		}
	}
}

void Tilemap::SetTileSize(int32 size)
{
	_tileSize = size;
}
