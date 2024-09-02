#include "pch.h"
#include "SphereCollider.h"
#include "SceneManager.h"
#include "Actor.h"
#include "BoxCollider.h"

SphereCollider::SphereCollider() : Collider(ColliderType::Sphere)
{

}

SphereCollider::~SphereCollider()
{

}

void SphereCollider::BeginPlay()
{
	Super::BeginPlay();


}

void SphereCollider::TickComponent()
{
	Super::TickComponent();


}

void SphereCollider::Render(HDC hdc)
{
	Super::Render(hdc);

	if (_showDebug == false)
		return;

	Vec2 cameraPos = GET_SINGLE(SceneManager)->GetCameraPos();
	Vec2 pos = GetOwner()->GetPos();
	pos.x -= (cameraPos.x - GWinSizeX / 2);		// 카메라를 중앙점에 설정
	pos.y -= (cameraPos.y - GWinSizeY / 2);

	// sphere 안쪽 영역을 투명으로... 중요한 코드 아님
	HBRUSH myBrush = (HBRUSH)::GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)::SelectObject(hdc, myBrush);
	Utils::DrawCircle(hdc, pos, _radius);
	::SelectObject(hdc, oldBrush);
	::DeleteObject(myBrush);
}

bool SphereCollider::CheckCollision(Collider* other)
{
	switch (other->GetColliderType())
	{
		case ColliderType::Box:
			return CheckCollisionSphere2Box(this, static_cast<BoxCollider*>(other));	// Collider이기 때문에 캐스팅
		case ColliderType::Sphere:
			return CheckCollisionSphere2Sphere(this, static_cast<SphereCollider*>(other));
	}

	return false;
}
