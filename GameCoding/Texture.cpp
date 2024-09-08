#include "pch.h"
#include "Texture.h"

Texture::Texture()
{
}

Texture::~Texture()
{
}

Texture* Texture::LoadBmp(HWND hwnd, const wstring& path)
{
	HDC hdc = ::GetDC(hwnd);

	// 이미지 로드는 개념적으로 크게 중요한 건 아니니 깊게 생각하진 말자
	_hdc = ::CreateCompatibleDC(hdc);
	_bitmap = (HBITMAP)::LoadImage(nullptr, path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	if (_bitmap == 0)		// 이미지가 없으면 경고 메세지
		::MessageBox(hwnd, path.c_str(), L"Image Load Failed", NULL);

	HBITMAP prev = (HBITMAP)::SelectObject(_hdc, _bitmap);
	::DeleteObject(prev);

	BITMAP bit = {};
	::GetObject(_bitmap, sizeof(BITMAP), &bit);

	_size.x = bit.bmWidth;
	_size.y = bit.bmHeight;

	return this;
}

HDC Texture::GetDC()
{
	//return HDC();	// 삽질 기록..^^ - ctrl + . + enter 눌러서 기본적으로 생성되는 함수 내용물을 안 고쳐서!!!
	return _hdc;
}
