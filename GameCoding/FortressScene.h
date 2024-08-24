#pragma once
#include "Scene.h"

enum
{
	MAX_PLAYERS = 2
};

class FortressScene : public Scene
{
public:
	FortressScene();
	virtual ~FortressScene() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	void ChangePlayerTurn();

private:
	int32 _playerTurn = 1;
	float _sumTime = 0.f;
};