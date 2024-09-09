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
	// C 스타일
	{
		FILE* file = nullptr;		// 파일 포인터
		_wfopen_s(&file, path.c_str(), L"rb");	// wb - write(읽기 전용), binary(or text)
		assert(file != nullptr);	// 파일이 없으면 크래시 발생

		// _mapSize.x
		::fread(&_mapSize.x, sizeof(_mapSize.x), 1, file);		// _mapSize의 주소, 4바이트, 1개, file에 저장
		::fread(&_mapSize.y, sizeof(_mapSize.y), 1, file);		// _mapSize의 주소, 4바이트, 1개, file에 저장

		SetMapSize(_mapSize);	// _tiles를 초기화 해야 함

		for (int32 y = 0; y < _mapSize.y; y++)
		{
			for (int32 x = 0; x < _mapSize.x; x++)
			{
				int32 value = -1;
				::fread(&value, sizeof(value), 1, file);
				_tiles[y][x].value = value;
			}
		}
	}
}

void Tilemap::SaveFile(const wstring& path)
{ 
	// C 스타일
	{
		FILE* file = nullptr;		// 파일 포인터
		_wfopen_s(&file, path.c_str(), L"wb");	// wb - write(읽기 전용), binary(or text)
		assert(file != nullptr);	// 파일이 없으면 크래시 발생

		// _mapSize.x를 기록하고 싶다면?
		::fwrite(&_mapSize.x, sizeof(_mapSize.x), 1, file);		// _mapSize의 주소, 4바이트, 1개, file에 저장
		::fwrite(&_mapSize.y, sizeof(_mapSize.y), 1, file);		// _mapSize의 주소, 4바이트, 1개, file에 저장

		for (int32 y = 0; y < _mapSize.y; y++)
		{
			for (int32 x = 0; x < _mapSize.x; x++)
			{
				int32 value = _tiles[y][x].value;
				::fwrite(&value, sizeof(value), 1, file);
			}
		}
	}
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
