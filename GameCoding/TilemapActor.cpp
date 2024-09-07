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

	TilePicking();
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

	// 컬링 : 보여야 할 애들만 보여주기(카메라가 찍는 부분 외에는 그리지 않아서 프레임 속도 낮아지는 문제 완화)
	int32 leftX = ((int32)cameraPos.x - GWinSizeX / 2);		// 카메라의 좌상단 위치
	int32 leftY = ((int32)cameraPos.y - GWinSizeY / 2);
	int32 rightX = ((int32)cameraPos.x + GWinSizeX / 2);	// 카메라의 우하단 위치
	int32 rightY = ((int32)cameraPos.y + GWinSizeY / 2);

	int32 startX = (leftX - _pos.x) / TILE_SIZEX;
	int32 startY = (leftY - _pos.y) / TILE_SIZEY;
	int32 endX = (leftY + _pos.x) / TILE_SIZEX;
	int32 endY = (leftY + _pos.y) / TILE_SIZEY;
	

	for (int32 y = startY; y <= endY; y++)
	{
		for (int32 x = startX; x <= endX; x++)
		{
			if (x < 0 || x >= mapSize.x)		// 예외 처리
				continue;
			if (y < 0 || y >= mapSize.y)
				continue;

			switch (tiles[y][x].value)
			{
			case 0: 
				::TransparentBlt(hdc,
					_pos.x + x * TILE_SIZEX - ((int32)cameraPos.x - GWinSizeX / 2),
					_pos.y + y * TILE_SIZEY - ((int32)cameraPos.y - GWinSizeY / 2),
					TILE_SIZEX,
					TILE_SIZEY,
					spriteO->GetDC(),
					spriteO->GetPos().x,
					spriteO->GetPos().y,
					TILE_SIZEX,
					TILE_SIZEY,
					spriteO->GetTransparent());
				break;

			case 1:
				::TransparentBlt(hdc,
					_pos.x + x * TILE_SIZEX - ((int32)cameraPos.x - GWinSizeX / 2),
					_pos.y + y * TILE_SIZEY - ((int32)cameraPos.y - GWinSizeY / 2),
					TILE_SIZEX,
					TILE_SIZEY,
					spriteX->GetDC(),
					spriteX->GetPos().x,
					spriteX->GetPos().y,
					TILE_SIZEX,
					TILE_SIZEY,
					spriteX->GetTransparent());
				break;
			}
		}
	}
}

void TilemapActor::TilePicking()
{
	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::LeftMouse))
	{
		Vec2 cameraPos = GET_SINGLE(SceneManager)->GetCameraPos();
		int32 screenX = cameraPos.x - GWinSizeX / 2;
		int32 screenY = cameraPos.y - GWinSizeY / 2;

		POINT mousePos = GET_SINGLE(InputManager)->GetMousePos();
		int32 posX = mousePos.x + screenX;
		int32 posY = mousePos.y + screenY;

		int32 x = posX / TILE_SIZEX;
		int32 y = posY / TILE_SIZEY;

		Tile* tile = _tilemap->GetTileAt({ x, y });
		if (tile)
			tile->value = 1;
	}
}
