#include "pch.h"
#include "ResourceManager.h"
#include "LineMesh.h"

ResourceManager::~ResourceManager()
{
	Clear();
}

void ResourceManager::Init()
{
	// 포트리스 메뉴
	{
		LineMesh* mesh = new LineMesh();
		mesh->Load(L"Menu.txt");
		_lineMeshes[L"Menu"] = mesh;
	}

	// 포트리스 UI
	{
		LineMesh* mesh = new LineMesh();
		mesh->Load(L"UI.txt");
		_lineMeshes[L"UI"] = mesh;
	}

	// 미사일 탱크
	{
		LineMesh* mesh = new LineMesh();
		mesh->Load(L"MissileTank.txt");
		_lineMeshes[L"MissileTank"] = mesh;
	}

	// 캐논 탱크
	{
		LineMesh* mesh = new LineMesh();
		mesh->Load(L"CanonTank.txt");
		_lineMeshes[L"CanonTank"] = mesh;
	}
}

void ResourceManager::Clear()
{
	for (auto mesh : _lineMeshes)
		SAFE_DELETE(mesh.second);

	_lineMeshes.clear();
}

const LineMesh* ResourceManager::GetLineMesh(wstring key)
{
	auto findIt = _lineMeshes.find(key);
	if (findIt == _lineMeshes.end())
		return nullptr;

	return findIt->second;
}
