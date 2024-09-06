#include "pch.h"
#include "TilemapActor.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Tilemap.h"
#include "Sprite.h"
#include "ResourceManager.h"

TilemapActor::TilemapActor()
{
}

TilemapActor::~TilemapActor()
{
}

void TilemapActor::BeginPlay()
{
	Super::BeginPlay();
}

void TilemapActor::Tick()
{
	Super::Tick();
}

void TilemapActor::Render(HDC hdc)
{
	Super::Render(hdc);

	if (_tilemap == nullptr)
		return;

	if (_showDebug == false)
		return;

	const Vec2Int mapSize = _tilemap->GetMapSize();			
	// [][][][][][]		 이런 식으로 깔림
	// [][][][][][]
	const int32 tileSize = _tilemap->GetTileSize();	// 타일 하나하나가 몇 픽셀을 차지하는지

	vector<vector<Tile>>& tiles = _tilemap->GetTiles();

	// 갈 수 있는 영역은 O, 갈 수 없는 영역은 X 표시 해줄 것(리소스에 있는 그림으로!)
	Sprite* spriteO = GET_SINGLE(ResourceManager)->GetSprite(L"Tile0");
	Sprite* spriteX = GET_SINGLE(ResourceManager)->GetSprite(L"TileX");

	Vec2 cameraPos = GET_SINGLE(SceneManager)->GetCameraPos();

	for (int32 y = 0; y < mapSize.y; y++)
	{
		for (int32 x = 0; x < mapSize.x; x++)
		{
			if (x < 0 || x > mapSize.x || y < 0 || y > mapSize.y)
		}
	}
}
