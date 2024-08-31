#pragma once
#include "ResourceBase.h"

class Texture;

struct FlipbookInfo
{
	Texture* texture = nullptr;
	wstring name;
	Vec2Int size = {};		// ���ҽ� �� ĭ ũ�� 
	int32 start = 0;		// �� �ִϸ��̼Ǹ��� �̹��� ������ �ٸ��� ������
	int32 end = 0;
	int32 line = 0;
	float duration = 1.f;	// �ð�
	bool loop = true;		// �� �� Ʋ�� ������, ��� Ʋ��
};

class Flipbook : public ResourceBase
{
public:
	Flipbook();
	virtual ~Flipbook();

	void SetInfo(const FlipbookInfo& info) { _info = info; }
	const FlipbookInfo& GetInfo() { return _info; }

private:
	FlipbookInfo _info;
};

