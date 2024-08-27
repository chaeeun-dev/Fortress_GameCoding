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

	void SetSize(Vec2Int size) { _size = size; }
	Vec2Int GetSize() { return _size; }

	void SetTransparent(uint32 transparent) { _transparent = transparent; }
	uint32 GetTransparent() { return _transparent; }

private:
	HDC			_hdc = {};
	HBITMAP		_bitmap = {};
	Vec2Int		_size = {};
	uint32		_transparent = RGB(255, 0, 255);		// 어떤 색을 투명 처리 할 것인가?(지금 리소스는 회색이 배경임 - 회색을 투명 처리 하자!)
};

