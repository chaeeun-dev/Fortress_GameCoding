#pragma once
#include "UI.h"

// ��ư�� �Ź� ����ؼ� ���� ���� ���� �ʴ�. UI�� Player�� �ٸ��� ������ ���� ���� ����! -> �ݹ��Լ�

class Sprite;

enum ButtonState
{
	BS_Default,
	//BS_Hovered,	// ���콺�� �÷����� ����
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
	Sprite* _sprites[BS_MaxCount] = {};		// ���¿� ���� ��������Ʈ�� �ٸ��� �׸��� ���� 
	ButtonState _state = BS_Default;		// ���� ��ư ����
	// ...
	float _sumTime = 0.f;

public:
	// ������ʹ� �����ϱ� ���� �� ���� �Ѿ�� ��... � �����ε� �Լ��� �����ϸ� ��. �ٸ� ��� �ᵵ ��!
	template<typename T>
	void AddOnClickDelegate(T* owner, void(T::* func)())
	{
		_onClick = [owner, func]()		// ĸó
		{
			(owner->*func)();
		};
	}

	// �Լ� ������ + �Լ� ��ü�� �� ���� �޾��� �� �ִ� std::function 
	std::function<void(void)> _onClick = nullptr;
};
