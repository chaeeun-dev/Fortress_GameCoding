#include "pch.h"
#include "SpriteActor.h"
#include "Sprite.h"

SpriteActor::SpriteActor()
{
}

SpriteActor::~SpriteActor()
{
}

void SpriteActor::BeginPlay()
{
	Super::BeginPlay();		// 부모 것을 먼저 호출 하는 게 좋음!!!
}

void SpriteActor::Tick()
{
	Super::Tick();
}

void SpriteActor::Render(HDC hdc)
{
	Super::Render(hdc);

	if (_sprite == nullptr)
		return; 

	Vec2Int size = _sprite->GetSize();

	//::BitBlt(hdc,
	//	(int32)_pos.x - size.x / 2, (int32)_pos.y - size.y / 2,		// 플레이어의 중심을 기준으로 절반 위치를 뺀 게 시작점
	//	size.x,
	//	size.y,
	//	_sprite->GetDC(),
	//	_sprite->GetPos().x,
	//	_sprite->GetPos().y,
	//	SRCCOPY);

	::TransparentBlt(hdc,
		(int32)_pos.x - size.x / 2,
		(int32)_pos.y - size.y / 2,		// 플레이어의 중심을 기준으로 절반 위치를 뺀 게 시작점
		size.x,
		size.y,
		_sprite->GetDC(),
		_sprite->GetPos().x,
		_sprite->GetPos().y,
		_sprite->GetSize().x,
		_sprite->GetSize().y,
		RGB(255, 255, 255));
}
