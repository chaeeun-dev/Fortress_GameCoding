#pragma once
#include "Actor.h"
//#include "Tilemap.h"

class Tilemap;

class TilemapActor : public Actor	// Reource는 공통으로, 하나만 존재 / Actor가 있어야 게임에 배치할 수 있음
{
	using Super = Actor;

public:
	TilemapActor();
	virtual ~TilemapActor();

	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

	void TilePicking();

	void SetTilemap(Tilemap* tilemap) { _tilemap = tilemap; }
	Tilemap* GetTilemap() { return _tilemap; }

	void SetShowDebug(bool showDebug) { _showDebug = showDebug; }

protected:
	Tilemap* _tilemap = nullptr;
	bool _showDebug = false;
};

