#pragma once
#include "FlipbookActor.h"

class Player : public FlipbookActor
{
	using Super = FlipbookActor;
public:
	Player();
	virtual ~Player();

	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

	virtual void OnComponentBeginOverlap(Collider* collider, Collider* other);
	virtual void OnComponenteEndOverlap(Collider* collider, Collider* other);

private:
	Flipbook* _flipbookUp = nullptr;
	Flipbook* _flipbookDown = nullptr;
	Flipbook* _flipbookRight = nullptr;
	Flipbook* _flipbookLeft = nullptr;
};

