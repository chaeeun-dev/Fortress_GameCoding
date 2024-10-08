#include "pch.h"
#include "CollisionManager.h"
#include "Collider.h"
#include "Actor.h"

void CollisionManager::Init()
{

}

void CollisionManager::Update()
{
	vector<Collider*>& colliders = _colliders;		// 혹시 collider가 삭제되면... 고민해보기

	for (int32 i = 0; i < colliders.size(); i++)
	{
		for (int32 j = i + 1; j < colliders.size(); j++)	// 짝이 지어져서 한 번씩은 실행이 됐기 때문에 0일 필요 없음
		{
			Collider* src = colliders[i];
			Collider* dest = colliders[j];

			if (src->CheckCollision(dest))		// 충돌이 일어났으면
			{
				if (src->_collisionMap.contains(dest) == false)		// 아직까지 충돌한 기록이 없으면(_collisionMap에 저장된 값이 없다)
				{
					// 충돌 기록 넣어주기
					src->GetOwner()->OnComponentBeginOverlap(src, dest);
					dest->GetOwner()->OnComponentBeginOverlap(dest, src);
					src->_collisionMap.insert(dest);
					dest->_collisionMap.insert(src);
				}
			}
			else    // 충돌이 있었는데 충돌이 사라짐
			{
				if (src->_collisionMap.contains(dest))
				{
					// 지워주기 
					src->GetOwner()->OnComponentEndOverlap(src, dest);
					dest->GetOwner()->OnComponentEndOverlap(dest, src);
					src->_collisionMap.erase(dest);
					dest->_collisionMap.erase(src);
				}
			}
		}
	}

}

void CollisionManager::AddCollider(Collider* collider)
{
	_colliders.push_back(collider);
}

void CollisionManager::RemoveCollider(Collider* collider)
{
	auto it = std::remove(_colliders.begin(), _colliders.end(), collider);
	_colliders.erase(it, _colliders.end());
}
