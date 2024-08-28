#include "pch.h"
#include "Sprite.h"
#include "Texture.h"

HDC Sprite::GetDC()
{
	return _texture->GetDC();
}

int32 Sprite::GetTransparent()
{
	return _texture->GetTransparent();
}
