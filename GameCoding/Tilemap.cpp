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

// ���� ������� C�� C++�̵� ������ ���ϴ� �ڵ�� ���� ��! ������ ������ �����´��~~
void Tilemap::LoadFile(const wstring& path)
{
	// C ��Ÿ�� - ���� ���Ͽ� 4byte ������ �����
	if (false)		// if (false)�� �ϸ� ���õ�!
	{
		{
			FILE* file = nullptr;		// ���� ������
			_wfopen_s(&file, path.c_str(), L"rb");	// wb - write(�б� ����), binary(or text)
			assert(file != nullptr);	// ������ ������ ũ���� �߻�

			// _mapSize.x
			::fread(&_mapSize.x, sizeof(_mapSize.x), 1, file);		// _mapSize�� �ּ�, 4����Ʈ, 1��, file�� ����
			::fread(&_mapSize.y, sizeof(_mapSize.y), 1, file);		// _mapSize�� �ּ�, 4����Ʈ, 1��, file�� ����

			SetMapSize(_mapSize);	// _tiles�� �ʱ�ȭ �ؾ� ��

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

	// C++ ��Ÿ�� - ���� ���Ͽ� �ƽ�Ű ��ȣ�� �����, C++�� �⺻�� �ؽ�Ʈ ����! binary ���� �ٲٴ� ����� ���۸��ϱ�. cf) �޸� ��� ���α׷� Hex Editor
	// txt vs binary - �ٹٲ��� txt���� 0D 0A, binary���� 0A �� �� ����. ����Ǵ� ���� �޶��� �� �ִ� ��!
	{
		wifstream ifs;	// output file stream

		ifs.open(path);

		ifs >> _mapSize.x;		// �� ����Ʈ���� ���� �� �ص� �˾Ƽ� �� ó����(C ��Ÿ�ϰ� ������). <- ���ø� ó���� �Ǿ� �־
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
	// C ��Ÿ��
	if (false)
	{
		{
			FILE* file = nullptr;		// ���� ������
			_wfopen_s(&file, path.c_str(), L"wb");	// wb - write(�б� ����), binary(or text)
			assert(file != nullptr);	// ������ ������ ũ���� �߻�

			// _mapSize.x�� ����ϰ� �ʹٸ�?
			::fwrite(&_mapSize.x, sizeof(_mapSize.x), 1, file);		// _mapSize�� �ּ�, 4����Ʈ, 1��, file�� ����
			::fwrite(&_mapSize.y, sizeof(_mapSize.y), 1, file);		// _mapSize�� �ּ�, 4����Ʈ, 1��, file�� ����

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

	// C++ ��Ÿ��
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

	return &_tiles[pos.y][pos.x];	// �ּҰ��� �Ѱ��� ����
}

void Tilemap::SetMapSize(Vec2Int size)
{
	_mapSize = size;

	_tiles = vector<vector<Tile>>(size.y, vector<Tile>(size.x));	// size�� �����ϰ�, _tiles�� �ٽ� �����ؾ� ��

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
