#include "pch.h"
#include "MenuScene.h"
#include "LineMesh.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "SceneManager.h"

MenuScene::MenuScene()
{

}

MenuScene::~MenuScene()
{

}

void MenuScene::Init()
{

}

void MenuScene::Update()
{
	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::E))
	{
		GET_SINGLE(SceneManager)->ChangeScene(SceneType::FortressScene);
	}
}

void MenuScene::Render(HDC hdc)
{
	::Rectangle(hdc, 0, 0, GWinSizeX, GWinSizeY);

	const LineMesh* mesh = GET_SINGLE(ResourceManager)->GetLineMesh(L"Menu");
	if (mesh)
		mesh->Render(hdc, Pos{0, 0});

	HFONT myFont = ::CreateFont(
		30						// 높이
		, 0						// 폭 0이면 높이와 비례
		, 0						// 글자 전체 기울기
		, 0						// 기준선이 정해진 기울기
		, 0						// 폰트의 두께
		, 0						// 이탤릭
		, 0						// 밑줄
		, 0						// 취소선
		, DEFAULT_CHARSET		// 케릭터 셋
		, 0						// 정밀도
		, 0						// 정밀도
		, 0						// 정밀도
		, 0						// 정밀도
		, L"궁서체"				// 글꼴이름
	);

	HFONT oldFont = (HFONT)::SelectObject(hdc, myFont);

	wstring message = L"PRESS 'E' TO START.";
	::TextOut(hdc, 250, 550, message.c_str(), static_cast<int32>(message.size()));

	::SelectObject(hdc, oldFont);
	::DeleteObject(myFont);
}
