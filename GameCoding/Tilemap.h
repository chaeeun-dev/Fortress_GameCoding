#pragma once
#include "ResourceBase.h"

struct Tile
{
	// TODO
	int32 value = 0;	// 0번이면 O, 1번이면 X 이런 식으로 그리는 방식
};

enum TILE_SIZE
{
	TILE_WIDTH = 63,	// 타일 까는 개수
	TILE_HEIHGT = 43,
	TILE_SIZEX = 48,	// 픽셀 사이즈 -> 맵의 너비 : 3024 = 63 x 48
	TILE_SIZEY = 48
};

class Tilemap : public ResourceBase
{
public:
	Tilemap();
	virtual ~Tilemap() override;

	virtual void LoadFile(const wstring& path) override;
	virtual void SaveFile(const wstring& path) override;
	
	Vec2Int GetMapSize() { return _mapSize; }
	int32 GetTileSize() { return _tileSize; }
	Tile* GetTileAt(Vec2Int pos);
	vector<vector<Tile>>& GetTiles() { return _tiles; }

	void SetMapSize(Vec2Int size);
	void SetTileSize(int32 size);

private:
	Vec2Int _mapSize = {};
	int32 _tileSize = 0;
	vector<vector<Tile>> _tiles;	// 이중벡터!!! _tiles[y][x]
};

