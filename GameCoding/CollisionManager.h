#pragma once

class Collider;

class CollisionManager
{
	DECLARE_SINGLE(CollisionManager);

public:
	void Init();
	void Update();

	void AddCollider(Collider* collider);		// �̷��� �����ͷ� ����ϴ� �� ������ �� �ִ�!!! ����Ʈ �����Ͱ� ���� �ǰ��� ����..^_^
	void RemoveCollider(Collider* collider);

private:
	vector<Collider*> _colliders;		
};