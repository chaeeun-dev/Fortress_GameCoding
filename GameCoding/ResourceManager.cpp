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
	// _resourcePath.relative_path();		// ��� ��� ������
	// fs::absolute(_resourcePath);		// ���� ��� ������
}

void ResourceManager::Clear()
{

}

