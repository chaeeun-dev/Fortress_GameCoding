#pragma once
#include "ResourceBase.h"

class Texture : public ResourceBase
{
public:
	Texture();
	virtual ~Texture();

public:
	Texture* LoadBmp(HWND hwnd, const wstring& path);
	HDC GetDC();

private:
	HDC _hdc = {};
	HBITMAP _bitmap = {};
	Vec2Int _size = {};
	uint32 _transparent = {};
};

