#include "pch.h"
#include "SpriteActor.h"

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
}
