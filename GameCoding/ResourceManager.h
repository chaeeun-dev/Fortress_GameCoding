#pragma once

class ResourceBase;
class Texture;

class ResourceManager
{
public:
	DECLARE_SINGLE(ResourceManager);

	~ResourceManager();

public:
	void Init(HWND hwnd, fs::path resourcePath);
	void Clear();

	const fs::path& GetResourcePath() { return _resourcePath; }

	Texture* GetTexture(const wstring& key) { return _textures[key]; }
	Texture* LoadTexture(const wstring& key, const wstring& path, uint32 transparent = RGB(255, 0, 255));
private:
	HWND _hwnd;
	fs::path _resourcePath;		// std::filesystem::path _resourcePath;

	unordered_map<wstring, Texture*> _textures;
};

