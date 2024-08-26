#include "pch.h"
#include "Bullet.h"
#include "TimeManager.h"
#include "ObjectManager.h"
#include "Player.h"
#include "SceneManager.h"
#include "FortressScene.h"
#include "UIManager.h"

Bullet::Bullet() : Object(ObjectType::Projectile)
{

}

Bullet::~Bullet()
{

}

void Bullet::Init()
{
	_radius = 20.f;
}

void Bullet::Update()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	// distance = v * t
	_pos += _speed * deltaTime;

	// Wind
	float windPercent = GET_SINGLE(UIManager)->GetWindPercent();
	_speed.x += 10 * deltaTime * windPercent;

	// Gravity
	_speed.y += 1000 * deltaTime;

	// 충돌
	const vector<Object*>& objects = GET_SINGLE(ObjectManager)->GetObjects();
	for (Object* object : objects)
	{
		if (object->GetObjectType() != ObjectType::Player)
			continue;
		if (object == _owner)
			continue;

		Vector dir = _pos - object->GetPos();
		if (dir.Length() < _radius + object->GetRadius())
		{
			// dynamic_cast - 캐스팅이 되면 내가 원하는 씬이라는 것 -> 이제 사용할 수 있음
			auto* scene = dynamic_cast<FortressScene*>(GET_SINGLE(SceneManager)->GetCurrentScene());
			if (scene)
				scene->ChangePlayerTurn();

			GET_SINGLE(ObjectManager)->Remove(this);
			return;
		}
	}

	// 소멸
	if (_pos.y > GWinSizeY * 1.5)
	{
		auto* scene = dynamic_cast<FortressScene*>(GET_SINGLE(SceneManager)->GetCurrentScene());
		if (scene)
			scene->ChangePlayerTurn();

		GET_SINGLE(ObjectManager)->Remove(this);
		return;
	}
}

void Bullet::Render(HDC hdc)
{
	Utils::DrawCircle(hdc, _pos, static_cast<int32>(_radius));
}
