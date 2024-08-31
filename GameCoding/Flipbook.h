#pragma once
#include "ResourceBase.h"

class Texture;

struct FlipbookInfo
{
	Texture* texture = nullptr;
	wstring name;
	Vec2Int size = {};		// 리소스 한 칸 크기 
	int32 start = 0;		// 각 애니메이션마다 이미지 개수가 다르기 때문에
	int32 end = 0;
	int32 line = 0;
	float duration = 1.f;	// 시간
	bool loop = true;		// 한 번 틀고 끝낼지, 계속 틀지
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

