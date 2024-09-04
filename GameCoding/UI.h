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

	RECT GetRect();		// UI�� �簢���̶�� �����ϰ� ����, �簢���� �ƴ϶�� �߰��ؾ���
	bool IsMouseInRect();
	
protected:
	Vec2	_pos = {400, 300};
	Vec2Int _size = {150, 150};

};
