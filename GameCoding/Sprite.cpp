#include "pch.h"
#include "Sprite.h"
#include "Texture.h"

Sprite::~Sprite()
{
}

HDC Sprite::GetDC()
{
	return _texture->GetDC();
}

int32 Sprite::GetTransparent()
{
	return _texture->GetTransparent();
	//return RGB(255, 0, 255);
}
