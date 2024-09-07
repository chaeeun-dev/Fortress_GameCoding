#pragma once
#include "Scene.h"

class Actor;
class UI;

class DevScene : public Scene
{
	using Super = Scene;
public:
	DevScene();
	virtual ~DevScene() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	void Clear();

	class TilemapActor* _tilemapActor = nullptr;	// TilemapActor는 map에서 중요하게 사용될 확률이 높음, 특수한 애들은 빠르게 찾을 수 있도록 따로 저장
};

