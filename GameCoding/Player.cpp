#include "pch.h"
#include "Player.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "ObjectManager.h"
#include "ResourceManager.h"
#include "LineMesh.h"
#include "UIManager.h"
#include "Bullet.h"

Player::Player() : Object(ObjectType::Player)
{

}

Player::~Player()
{

}

void Player::Init()
{
	// TODO : Data
	_stat.hp = 100;
	_stat.maxHp = 100;
	_stat.speed = 500;

	_pos.x = 0;
	_pos.y = 0;

	_radius = 50.f;
	_fireAngle = 30.f;
}

void Player::Update()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	// 거리 = 시간 * 속도

	// 아래부터는 입력
	if (_playerTurn == false)
		return;

	// 매 프레임 때리자
	UpdateFireAngle();

	if (GET_SINGLE(InputManager)->GetButton(KeyType::A))
	{
		float stamina = GET_SINGLE(UIManager)->GetStaminaPercent();
		stamina = max(0, stamina - 100 * deltaTime);
		GET_SINGLE(UIManager)->SetStaminaPercent(stamina);

		if (stamina > 0)
			_pos.x -= _stat.speed * deltaTime;

		_dir = MoveDir::Left;
	}

	if (GET_SINGLE(InputManager)->GetButton(KeyType::D))
	{
		float stamina = GET_SINGLE(UIManager)->GetStaminaPercent();
		stamina = max(0, stamina - 100 * deltaTime);
		GET_SINGLE(UIManager)->SetStaminaPercent(stamina);
		
		if (stamina > 0)
			_pos.x += _stat.speed * deltaTime;

		_dir = MoveDir::Right;
	}

	// clamp 함수 - min max
	if (GET_SINGLE(InputManager)->GetButton(KeyType::W))
		_fireAngle = ::clamp(_fireAngle + 50 * deltaTime, 0.f, 75.f);

	if (GET_SINGLE(InputManager)->GetButton(KeyType::S))
		_fireAngle = ::clamp(_fireAngle - 50 * deltaTime, 0.f, 75.f);

	if (GET_SINGLE(InputManager)->GetButton(KeyType::SpaceBar))
	{
		float percent = GET_SINGLE(UIManager)->GetPowerPercent();
		percent = min(100, percent + 100 * deltaTime);
		GET_SINGLE(UIManager)->SetPowerPercent(percent);
	}

	if (GET_SINGLE(InputManager)->GetButtonUp(KeyType::SpaceBar))
	{
		_playerTurn = false;	// 스페이스 바 떼면 바로 다음 턴

		// SpaceBar 비례해서 속도를 산정.
		float percent = GET_SINGLE(UIManager)->GetPowerPercent();		
		float speed = static_cast<float>(10.f * percent); // MaxSpeed = 3000
		float angle = GET_SINGLE(UIManager)->GetBarrelAngle();

		Bullet* bullet = GET_SINGLE(ObjectManager)->CreateObject<Bullet>();
		bullet->SetOwner(this);
		bullet->SetPos(_pos);
		bullet->SetSpeed(Vector{speed * cos(angle * PI / 180), -1 * speed * sin(angle * PI / 180)});
		GET_SINGLE(ObjectManager)->Add(bullet);
	}

	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::KEY_1))
	{
		GET_SINGLE(UIManager)->SetSpecialWeapon(false);
	}

	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::KEY_2))
	{
		GET_SINGLE(UIManager)->SetSpecialWeapon(true);
	}
}

void Player::Render(HDC hdc)
{
	// Player
	if (_dir == MoveDir::Left)
	{
		const LineMesh* mesh = GET_SINGLE(ResourceManager)->GetLineMesh(GetMeshKey());
		if (mesh)
			mesh->Render(hdc, _pos, 0.5f, 0.5f);
	}
	else
	{
		const LineMesh* mesh = GET_SINGLE(ResourceManager)->GetLineMesh(GetMeshKey());
		if (mesh)
			mesh->Render(hdc, _pos, -0.5f, 0.5f);
	}
	
	// UI - 나중에는 이렇게 하드코딩X, 툴 이용해서 할 것!
	if (_playerTurn)
	{
		RECT rect;
		rect.bottom = static_cast<LONG>(_pos.y - 60);
		rect.left = static_cast<LONG>(_pos.x - 10);
		rect.right = static_cast<LONG>(_pos.x + 10);
		rect.top = static_cast<LONG>(_pos.y - 80);

		HBRUSH brush = ::CreateSolidBrush(RGB(250, 236, 197));
		HBRUSH oldBrush = (HBRUSH)::SelectObject(hdc, brush);

		::Ellipse(hdc, rect.left, rect.top, rect.right, rect.bottom);

		::SelectObject(hdc, oldBrush);
		::DeleteObject(brush);
	}
}

std::wstring Player::GetMeshKey()
{
	if (_playerType == PlayerType::MissileTank)
		return L"MissileTank";
	else
		return L"CanonTank";
}

void Player::UpdateFireAngle()
{
	if (_dir == MoveDir::Right)
	{
		GET_SINGLE(UIManager)->SetBarrelAngle(_fireAngle);
		GET_SINGLE(UIManager)->SetPlayerAngle(0);
	}
	else
	{
		GET_SINGLE(UIManager)->SetBarrelAngle(180 - _fireAngle);
		GET_SINGLE(UIManager)->SetPlayerAngle(180);
	}
}
