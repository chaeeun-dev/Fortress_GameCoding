#include "pch.h"
#include "ResourceManager.h"
#include "LineMesh.h"

ResourceManager::~ResourceManager()
{
	Clear();
}

void ResourceManager::Init(HWND hwnd, fs::path resourcePath)
{
	_hwnd = hwnd;
	_resourcePath = resourcePath;

	// fs::current_path();
	// _resourcePath.relative_path();		// 상대 경로 얻어오기
	// fs::absolute(_resourcePath);		// 절대 경로 얻어오기
}

void ResourceManager::Clear()
{

}

