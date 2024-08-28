#pragma once
#include "ResourceBase.h"

class Texture;

// 영역을 잡아서 어디부터 어디까지 사용할 것인지 - Texture vs Sprite - Sprite가 잘라서 쓰는 개념
class Sprite : public ResourceBase
{
public:
	Sprite(Texture* texture, int32 x, int32 y, int32 cx, int32 cy) : _texture(texture), _x(x), _y(y), _cx(cx), _cy(cy) {}
	virtual ~Sprite();

	HDC GetDC();
	int32 GetTransparent();
	Vec2Int GetPos() { return Vec2Int{ _x, _y }; }
	Vec2Int GetSize() { return Vec2Int{ _cx, _cy }; }

private:
	Texture* _texture = nullptr;
	int32 _x;
	int32 _y;
	int32 _cx;
	int32 _cy;
};

