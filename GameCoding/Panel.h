#pragma once
#include "UI.h"

class Sprite;

class Panel : public UI		// UI를 묶어서 관리하는 용도 - 많은 UI를 들고 있을 수 있음!
{
	using Super = UI;
public:
	Panel();
	virtual ~Panel();

	virtual void BeginPlay();
	virtual void Tick();
	virtual void Render(HDC hdc);

	void		AddChild(UI* ui);
	bool		RemoveChild(UI* ui);

private:
	vector<UI*> _children;
};
