#include "pch.h"
#include "Button.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "Sprite.h"

Button::Button()
{

}

Button::~Button()
{

}

void Button::BeginPlay()
{
	Super::BeginPlay();

	SetButtonState(BS_Default);
}

void Button::Tick()
{
	POINT mousePos = GET_SINGLE(InputManager)->GetMousePos();
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	if (_state == BS_Clicked)
	{
		_sumTime += deltaTime;
		if (_sumTime >= 0.2f)
		{
			_sumTime = 0.f;
			SetButtonState(BS_Default);
		}
	}

	if (IsMouseInRect())
	{
		if (GET_SINGLE(InputManager)->GetButton(KeyType::LeftMouse))		// 마우스를 누르고 있는 상태
		{
			SetButtonState(BS_Pressed);
			// OnPressed 호출할 일 있으면 여기서 호출
		}
		else
		{
			if (_state == BS_Pressed)		// 원래는 누르고 있었는데 뗐음
			{
				SetButtonState(BS_Clicked);
				// OnClicked
				/*if (_onClick)
					_onClick();*/
			}
		}
	}
	else
	{
		SetButtonState(BS_Default);
	}
}

void Button::Render(HDC hdc)
{
	if (_currentSprite)		// 스프라이트가 있으면 스프라이트로 그리고
	{
		::TransparentBlt(hdc,
			(int32)_pos.x - _size.x / 2,
			(int32)_pos.y - _size.y / 2,
			_size.x,
			_size.y,
			_currentSprite->GetDC(),
			_currentSprite->GetPos().x,
			_currentSprite->GetPos().y,
			_currentSprite->GetSize().x,
			_currentSprite->GetSize().y,
			_currentSprite->GetTransparent());
	}
	else				// 스프라이트가 없으면 사각형 그림
	{
		Utils::DrawRect(hdc, _pos, _size.x, _size.y);
	}
}

void Button::SetButtonState(ButtonState state)
{
	_state = state;

	if (_sprites[state])
		SetCurrentSprite(_sprites[state]);
}
