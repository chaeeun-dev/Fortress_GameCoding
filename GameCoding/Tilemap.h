#pragma once
#include "ResourceBase.h"

struct Tile
{
	// TODO
	int32 value = 0;	// 0���̸� O, 1���̸� X �̷� ������ �׸��� ���
};

enum TILE_SIZE
{
	TILE_WIDTH = 63,	// Ÿ�� ��� ����
	TILE_HEIHGT = 43,
	TILE_SIZEX = 48,	// �ȼ� ������ -> ���� �ʺ� : 3024 = 63 x 48
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
	// ���� ���� - 1. � �����͸� ������ ���ΰ�? - runtime�� ����Ǵ� �����͵��� ���� ����� �ʿ䰡 ����. / 2. � �������� ������ ���ΰ�(formating)?
	Vec2Int _mapSize = {};
	int32 _tileSize = 0;
	vector<vector<Tile>> _tiles;	// ���ߺ���!!! _tiles[y][x]

	// [1][1][1][0][0][0][0][0][0][0]
	// [1][0][1][0][0][0][0][0][0][0]
	// [0][0][0][0][0][0][0][0][0][0]
	// [0][0][0][0][0][0][0][0][0][0]
};