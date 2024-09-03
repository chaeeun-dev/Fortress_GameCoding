#pragma once

class Collider;

class CollisionManager
{
	DECLARE_SINGLE(CollisionManager);

public:
	void Init();
	void Update();

	void AddCollider(Collider* collider);		// 이렇게 포인터로 사용하는 건 위험할 수 있다!!! 스마트 포인터가 정신 건강에 좋음..^_^
	void RemoveCollider(Collider* collider);

private:
	vector<Collider*> _colliders;		
};