#pragma once
#include "Component.h"
// �浹 ���� �Ǻ� 

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

	virtual bool CheckCollision(Collider* other);		// �浹�ϰ� �ִ°�?

	ColliderType GetColliderType() { return _colliderType; }
	void SetShowDebug(bool show) { _showDebug = show; }		// ����� ��忡�� �浹 ���� �����ֱ�

public:
	static bool CheckCollisionBox2Box(BoxCollider* b1, BoxCollider* b2);
	static bool CheckCollisionSphere2Box(SphereCollider* s1, BoxCollider* b2);
	static bool CheckCollisionSphere2Sphere(SphereCollider* s1, SphereCollider* s2);

protected:
	ColliderType _colliderType;
	bool _showDebug = true;

public:
	unordered_set<Collider*> _collisionMap;		// �̹� �浹�� ��ü���� ��� �˻����� �ʱ� ����.. �浹�ߴٴ� ���� ����, Begin & End�� �� ���� ȣ���� �� �ְ� �� - �Ĳ��ϰ� ó������� �Ѵ�!(���� ��)
	
	uint32 _flag = 0;	// � ��ü�� ��� ��ü���� �浹�ؾ��ϰ�... �̷� �͵� ���� - ��Ʈ ����(�ϳ��� ������ �Ҹ��� 32�� ���� ex. 0011 �� �ڸ����� �ϳ��� ��ü�� �浹�ϴ��� üũ)
};