#pragma once

class ResourceBase;
class LineMesh;

class ResourceManager
{
public:
	DECLARE_SINGLE(ResourceManager);

	~ResourceManager();

public:
	void Init();
	void Clear();

private:
};

