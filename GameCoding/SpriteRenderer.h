#pragma once
#include "Component.h"

class Sprite; 

class SpriteRenderer : public Component
{
public:
	virtual void Start() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	void SetSprite(Sprite* sprite) { _sprite = sprite; }

private:
	Sprite* _sprite = nullptr;

};

