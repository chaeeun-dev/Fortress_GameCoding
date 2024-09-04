#include "pch.h"
#include "DevScene.h"
#include "Utils.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "Texture.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "Sprite.h"
#include "Actor.h"
#include "SpriteActor.h"
#include "Player.h"
#include "Flipbook.h"
#include "BoxCollider.h"
#include "SphereCollider.h"
#include "CollisionManager.h"
#include "UI.h"
#include "Button.h"

DevScene::DevScene()
{

}

DevScene::~DevScene()
{

}

void DevScene::Init()
{
	GET_SINGLE(ResourceManager)->LoadTexture(L"Stage01", L"Sprite\\Map\\Stage01.bmp");
	//GET_SINGLE(ResourceManager)->LoadTexture(L"Sword", L"Sprite\\Item\\Sward.bmp");
	GET_SINGLE(ResourceManager)->LoadTexture(L"Potion", L"Sprite\\UI\\Mp.bmp");
	GET_SINGLE(ResourceManager)->LoadTexture(L"PlayerDown", L"Sprite\\Player\\PlayerDown.bmp", RGB(128, 128, 128));		// 플레이어 이미지 배경이 회색이기 때문에.. 
	GET_SINGLE(ResourceManager)->LoadTexture(L"PlayerUp", L"Sprite\\Player\\PlayerUp.bmp", RGB(128, 128, 128));
	GET_SINGLE(ResourceManager)->LoadTexture(L"PlayerLeft", L"Sprite\\Player\\PlayerLeft.bmp", RGB(128, 128, 128));
	GET_SINGLE(ResourceManager)->LoadTexture(L"PlayerRight", L"Sprite\\Player\\PlayerRight.bmp", RGB(128, 128, 128));
	GET_SINGLE(ResourceManager)->LoadTexture(L"Start", L"Sprite\\UI\\Start.bmp");
	GET_SINGLE(ResourceManager)->LoadTexture(L"Edit", L"Sprite\\UI\\Edit.bmp");
	GET_SINGLE(ResourceManager)->LoadTexture(L"Exit", L"Sprite\\UI\\Exit.bmp");

	GET_SINGLE(ResourceManager)->CreateSprite(L"Stage01", GET_SINGLE(ResourceManager)->GetTexture(L"Stage01"));
	GET_SINGLE(ResourceManager)->CreateSprite(L"Start_Off", GET_SINGLE(ResourceManager)->GetTexture(L"Start"), 0, 0, 150, 150);
	GET_SINGLE(ResourceManager)->CreateSprite(L"Start_On", GET_SINGLE(ResourceManager)->GetTexture(L"Start"), 150, 0, 150, 150);
	GET_SINGLE(ResourceManager)->CreateSprite(L"Edit_Off", GET_SINGLE(ResourceManager)->GetTexture(L"Edit"), 0, 0, 150, 150);
	GET_SINGLE(ResourceManager)->CreateSprite(L"Edit_On", GET_SINGLE(ResourceManager)->GetTexture(L"Edit"), 150, 0, 150, 150);
	GET_SINGLE(ResourceManager)->CreateSprite(L"Exit_Off", GET_SINGLE(ResourceManager)->GetTexture(L"Stage01"), 0, 0, 150, 150);
	GET_SINGLE(ResourceManager)->CreateSprite(L"Exit_On", GET_SINGLE(ResourceManager)->GetTexture(L"Stage01"), 150, 0, 150, 150);

	// 이렇게 플립북 만들어 놓으면 언제든지 사용할 수 있게됨!
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"PlayerUp");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_MoveUp");
		fb->SetInfo({ texture, L"FB_MoveUp", { 200, 200 }, 0, 9, 1, 0.5f });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"PlayerDown");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_MoveDown");
		fb->SetInfo({ texture, L"FB_MoveDown", { 200, 200 }, 0, 9, 1, 0.5f });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"PlayerLeft");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_MoveLeft");
		fb->SetInfo({ texture, L"FB_MoveLeft", { 200, 200 }, 0, 9, 1, 0.5f });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"PlayerRight");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_MoveRight");
		fb->SetInfo({ texture, L"FB_MoveRight", { 200, 200 }, 0, 9, 1, 0.5f });
	}

	// 레이어를 설정하니까 background보다 player를 먼저 배치해도 아무 문제가 없음!
	{
		Player* player = new Player();
		{
			SphereCollider* collider = new SphereCollider();
			collider->SetRadius(100);
			player->AddComponent(collider);
			GET_SINGLE(CollisionManager)->AddCollider(collider);
		}
		AddActor(player);
	}

	// 충돌 검사를 위한 Actor 생성
	{
		Actor* player = new Actor();
		{
			SphereCollider* collider = new SphereCollider();
			collider->SetRadius(100);
			player->AddComponent(collider);
			GET_SINGLE(CollisionManager)->AddCollider(collider);
			player->SetPos({ 400, 200 });
		}
		AddActor(player);
	}
	{
		Sprite* sprite = GET_SINGLE(ResourceManager)->GetSprite(L"Stage01");

		SpriteActor* background = new SpriteActor();
		background->SetSprite(sprite);
		background->SetLayer(LAYER_BACKGROUND);
		background->SetPos(Vec2(0, 0));

		AddActor(background);
	}

	{
		Button* ui = new Button();

		ui->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Start_Off"), BS_Default);
		ui->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Start_On"), BS_Clicked);
		ui->SetPos({ 200, 200 });
		_uis.push_back(ui);
	}
	
	for (const vector<Actor*>& actors : _actors)
		for (Actor* actor : actors)
			actor->BeginPlay();

	for (UI* ui : _uis)
		ui->BeginPlay();
}

void DevScene::Update()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	GET_SINGLE(CollisionManager)->Update();

	for (const vector<Actor*>& actors : _actors)
		for (Actor* actor : actors)
			actor->Tick();

	for (UI* ui : _uis)
		ui->Tick();
}


void DevScene::Render(HDC hdc)
{
	for (const vector<Actor*>& actors : _actors)
		for (Actor* actor : actors)
		actor->Render(hdc);

	for (UI* ui : _uis)
		ui->Render(hdc);
}

void DevScene::AddActor(Actor* actor)
{
	if (actor == nullptr)
		return;

	_actors[actor->GetLayer()].push_back(actor);
}

void DevScene::RemoveActor(Actor* actor)
{
	if (actor == nullptr)
		return;

	vector<Actor*>& v = _actors[actor->GetLayer()];

	v.erase(std::remove(v.begin(), v.end(), actor));	// remove와 erase는 짝꿍!!
}
