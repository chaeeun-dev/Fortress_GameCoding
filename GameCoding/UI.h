#pragma once


class UI
{
public:
	UI();
	virtual ~UI();

	virtual void BeginPlay();
	virtual void Tick();
	virtual void Render(HDC hdc);

	void SetPos(Vec2 pos) { _pos = pos; }
	Vec2 GetPos() { return _pos; }

	RECT GetRect();		// UI가 사각형이라고 가정하고 만듦, 사각형이 아니라면 추가해야함
	bool IsMouseInRect();
	
protected:
	Vec2	_pos = {400, 300};
	Vec2Int _size = {150, 150};

};
