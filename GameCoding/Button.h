#pragma once
#include "UI.h"

// 버튼을 매번 상속해서 쓰는 것은 좋지 않다. UI는 Player와 다르게 개수가 정말 많기 때문! -> 콜백함수

class Sprite;

enum ButtonState
{
	BS_Default,
	//BS_Hovered,	// 마우스를 올려놓은 상태
	BS_Pressed,
	BS_Clicked,
	// ...
	BS_MaxCount
};

class Button : public UI
{
	using Super = UI;
public:
	Button();
	virtual ~Button() override;

	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

	void	SetSize(Vec2Int size) { _size = size; }
	Sprite* GetSprite(ButtonState state) { return _sprites[state]; }

	void SetCurrentSprite(Sprite* sprite) { _currentSprite = sprite; }
	void SetSprite(Sprite* sprite, ButtonState state) { _sprites[state] = sprite; }
	void SetButtonState(ButtonState state);

	void OnClickButton() { }
protected:
	Sprite* _currentSprite = nullptr;
	Sprite* _sprites[BS_MaxCount] = {};		// 상태에 따라 스프라이트를 다르게 그리기 위해 
	ButtonState _state = BS_Default;		// 현재 버튼 상태
	// ...
	float _sumTime = 0.f;

public:
	// 여기부터는 어려우니까 이해 안 가면 넘어가도 됨... 어떤 식으로든 함수를 매핑하면 됨. 다른 방법 써도 됨!
	template<typename T>
	void AddOnClickDelegate(T* owner, void(T::* func)())
	{
		_onClick = [owner, func]()		// 캡처
		{
			(owner->*func)();
		};
	}

	// 함수 포인터 + 함수 객체를 한 번에 받아줄 수 있는 std::function 
	std::function<void(void)> _onClick = nullptr;
};
