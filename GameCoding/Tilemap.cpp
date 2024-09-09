#include "pch.h"
#include "Tilemap.h"
#include <fstream>
#include <iostream>

Tilemap::Tilemap()
{
}

Tilemap::~Tilemap()
{
}

// 파일 입출력은 C든 C++이든 본인이 원하는 코드로 쓰면 됨! 정답은 없으니 끌리는대로~~
void Tilemap::LoadFile(const wstring& path)
{
	// C 스타일 - 실제 파일에 4byte 정수가 저장됨
	if (false)		// if (false)를 하면 무시됨!
	{
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

	// C++ 스타일 - 실제 파일에 아스키 번호가 저장됨, C++은 기본이 텍스트 포맷! binary 모드로 바꾸는 방법은 구글링하기. cf) 메모리 까는 프로그램 Hex Editor
	// txt vs binary - 줄바꿈이 txt에선 0D 0A, binary에선 0A 일 수 있음. 저장되는 값이 달라질 수 있는 것!
	{
		wifstream ifs;	// output file stream

		ifs.open(path);

		ifs >> _mapSize.x;		// 몇 바이트인지 기입 안 해도 알아서 잘 처리함(C 스타일과 차이점). <- 템플릿 처리가 되어 있어서
		ifs >> _mapSize.y;

		for (int32 y = 0; y < _mapSize.x; y++)
		{
			wstring line;
			ifs >> line;

			for (int32 x = 0; x < _mapSize.x; x++)
			{
				_tiles[y][x].value = line[x] - L'0';
			}
		}

		ifs.close();
	}
}

void Tilemap::SaveFile(const wstring& path)
{ 
	// C 스타일
	if (false)
	{
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

	// C++ 스타일
	{
		wofstream ofs;	// output file stream

		ofs.open(path);

		ofs << _mapSize.x << endl;
		ofs << _mapSize.y << endl;

		for (int32 y = 0; y < _mapSize.x; y++)
		{
			for (int32 x = 0; x < _mapSize.x; x++)
			{
				ofs << _tiles[y][x].value;
			}
		}

		ofs.close();
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
