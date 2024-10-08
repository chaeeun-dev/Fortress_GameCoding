#pragma once
#include "Actor.h"

class Flipbook;

class FlipbookActor : public Actor
{
	using Super = Actor;
public:
	FlipbookActor();
	virtual ~FlipbookActor();

	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

	void SetFlipbook(Flipbook* flipbook);
	void Reset();

protected:
	Flipbook* _flipbook = nullptr;
	float _sumTime = 0.f;
	int32 _idx = 0;			// 몇 번째 애니메이션을 실행할지
};

