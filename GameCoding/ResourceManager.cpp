#include "pch.h"
#include "ResourceManager.h"
#include "Texture.h"

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
	for (auto& item : _textures)
		SAFE_DELETE(item.second);

	_textures.clear();
}

Texture* ResourceManager::LoadTexture(const wstring& key, const wstring& path, uint32 transparent)
{
	if (_textures.find(key) != _textures.end())		// 키가 이미 있으면
		return _textures[key];

	fs::path fullPath = _resourcePath / path;			// 전체 경로 구하기

	Texture* texture = new Texture();
	texture->LoadBmp(_hwnd, fullPath.c_str());
	texture->SetTransparent(transparent);
	_textures[key] = texture;

	return texture;
}

