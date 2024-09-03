#pragma once
#include "Component.h"
// 충돌 여부 판별 

class BoxCollider;
class SphereCollider;

class Collider : public Component
{
public:
	Collider(ColliderType colliderType);
	virtual ~Collider() override;

	virtual void BeginPlay() override;
	virtual void TickComponent() override;
	virtual void Render(HDC hdc) override;

	virtual bool CheckCollision(Collider* other);		// 충돌하고 있는가?

	ColliderType GetColliderType() { return _colliderType; }
	void SetShowDebug(bool show) { _showDebug = show; }		// 디버그 모드에서 충돌 영역 보여주기

public:
	static bool CheckCollisionBox2Box(BoxCollider* b1, BoxCollider* b2);
	static bool CheckCollisionSphere2Box(SphereCollider* s1, BoxCollider* b2);
	static bool CheckCollisionSphere2Sphere(SphereCollider* s1, SphereCollider* s2);

protected:
	ColliderType _colliderType;
	bool _showDebug = true;

public:
	unordered_set<Collider*> _collisionMap;		// 이미 충돌한 객체들을 계속 검사하지 않기 위해.. 충돌했다는 정보 저장, Begin & End를 한 번만 호출할 수 있게 함 - 꼼꼼하게 처리해줘야 한다!(삭제 등)
	
	uint32 _flag = 0;	// 어떤 객체는 어떠한 객체랑만 충돌해야하고... 이런 것들 관리 - 비트 연산(하나의 정수에 불리언 32개 관리 ex. 0011 각 자리수가 하나의 객체로 충돌하는지 체크)
};