#include "../Public/AssetManager.h"
#include "shlwapi.h"
#include <filesystem>
#include <fstream>
#include "ObjReader.h"

Util::AssetManager::AssetManager* Util::AssetManager::AssetManager::s_assetManagerHandle = nullptr;

Util::AssetManager::AssetManager::AssetManager()
{
	const DWORD bufferLength = MAX_PATH;
	char currentDirectory[MAX_PATH + 1];
	DWORD dirPathLength = GetCurrentDirectory(bufferLength, currentDirectory);
	m_workingDir = currentDirectory;
	m_contentDir = m_workingDir + "\\Content";
	m_texturesDir = m_contentDir + "\\Textures\\";
	m_objectsDir = m_contentDir + "\\Objects\\";
	m_materialsDir = m_contentDir + "\\Materials\\";
	m_shadersDir = m_contentDir + "\\Shaders\\";
}

void Util::AssetManager::AssetManager::Init()
{
	LoadAssetsFromDir();
}

std::vector<std::wstring> Util::AssetManager::AssetManager::GetShaderPaths() const
{
	return m_shaderPaths;
}

std::vector<::Util::Util::SMesh> Util::AssetManager::AssetManager::GetMeshes() const
{
	return m_loadedMeshes;
}

void Util::AssetManager::AssetManager::Create()
{
	if (!s_assetManagerHandle)
	{
 		s_assetManagerHandle = new AssetManager();
	}
}

Util::AssetManager::AssetManager* Util::AssetManager::AssetManager::GetHandle()
{
	return s_assetManagerHandle;
}

void Util::AssetManager::AssetManager::Shutdown()
{
	delete s_assetManagerHandle;
	s_assetManagerHandle = nullptr;
}

Util::AssetManager::AssetManager::~AssetManager()
{

}

void Util::AssetManager::AssetManager::LoadAssetsFromDir()
{
	for (const auto& file : std::filesystem::directory_iterator(m_shadersDir))
	{
		std::string filePath = file.path().string();
		std::string extension = PathFindExtension(filePath.c_str());
		if (extension == ".hlsl")
		{
			m_shaderPaths.push_back(file.path().wstring());
		}
	}
	for (const auto& file : std::filesystem::directory_iterator(m_objectsDir))
	{
		std::string filePath = file.path().string();
		std::string extension = PathFindExtension(filePath.c_str());
		if (extension == ".obj")
		{
			LoadObject(filePath);
		}
		
	}
	for (const auto& file : std::filesystem::directory_iterator(m_materialsDir))
	{
		std::string filePath = file.path().string();
		std::string extension = PathFindExtension(filePath.c_str());
		if (extension == ".mtl")
		{
			LoadMtl(filePath);
		}
	}
}

void Util::AssetManager::AssetManager::LoadObject(const std::string& filePath)
{
	m_loadedMeshes.push_back(::Util::Util::ObjReader::ReadObjFile(filePath));
}

void Util::AssetManager::AssetManager::LoadMtl(const std::string& filePath)
{
	std::vector<::Util::Util::SMaterial> materials =  ::Util::Util::ObjReader::ReadMtlFile(filePath);
}
