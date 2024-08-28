#include "pch.h"
#include "Player.h"
#include "InputManager.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::BeginPlay()
{
	Super::BeginPlay();		// 상위 계층 코드 꼭 넣기
}

void Player::Tick()
{
	Super::Tick();

	// TODO
	if (GET_SINGLE(InputManager)->GetButton(KeyType::W))
	{

	}
}

void Player::Render(HDC hdc)
{
	Super::Render;
}
