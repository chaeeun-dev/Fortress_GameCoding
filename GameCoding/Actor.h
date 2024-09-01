#pragma once

class Component;

class Actor
{
public:
	Actor();
	virtual ~Actor();

	virtual void BeginPlay();
	virtual void Tick();
	virtual void Render(HDC hdc);

	void SetPos(Vec2 pos) { _pos = pos; }
	Vec2 GetPos() { return _pos; }

	void AddComponent(Component* component);
	void RemoveComponent(Component* component);

protected:
	Vec2 _pos = { 0, 0 };

	vector<Component*> _components;
};

