#include "pch.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "Sprite.h"
#include "Flipbook.h"
#include "Tilemap.h"

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

	for (auto& item : _sprites)
		SAFE_DELETE(item.second);

	_sprites.clear();

	for (auto& item : _flipbooks)
		SAFE_DELETE(item.second);

	_flipbooks.clear();

	for (auto& item : _tilemaps)
		SAFE_DELETE(item.second);

	_tilemaps.clear();
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

Sprite* ResourceManager::CreateSprite(const wstring& key, Texture* texture, int32 x, int32 y, int32 cx, int32 cy)
{
	if (_sprites.find(key) != _sprites.end())
		return _sprites[key];

	if (cx == 0)
		cx = texture->GetSize().x;

	if (cy == 0)
		cy = texture->GetSize().y;

	Sprite* sprite = new Sprite(texture, x, y, cx, cy);
	_sprites[key] = sprite;
	
	return sprite;
}

Flipbook* ResourceManager::CreateFlipbook(const wstring& key)
{
	if (_flipbooks.find(key) != _flipbooks.end())
		return _flipbooks[key];			// 이미 있으면 그걸 리턴

	Flipbook* fb = new Flipbook();
	_flipbooks[key] = fb;

	return fb;
}

Tilemap* ResourceManager::CreateTilemap(const wstring& key)
{
	if (_tilemaps.find(key) != _tilemaps.end())		// 원래 있는 애라면 만들지 말고 꺼내줌
		return _tilemaps[key];

	Tilemap* tm = new Tilemap();
	_tilemaps[key] = tm;

	return tm;
}

void ResourceManager::SaveTilemap(const wstring& key, const wstring& path)
{
	Tilemap* tm = GetTilemap(key);

	fs::path fullPath = _resourcePath / path;			// 전체 경로
	tm->SaveFile(fullPath);
}

Tilemap* ResourceManager::LoadTilemap(const wstring& key, const wstring& path)
{
	Tilemap* tm = nullptr;

	if (_tilemaps.find(key) == _tilemaps.end())		// _tilemaps가 비었으면 
		_tilemaps[key] = new Tilemap();		// 새로 만들어주기

	fs::path fullPath = _resourcePath / path;			// 전체 경로
	tm->LoadFile(fullPath);

	return tm;
}

