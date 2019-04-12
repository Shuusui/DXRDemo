#include "../Public/AssetManager.h"
#include "shlwapi.h"
#include <filesystem>
#include <fstream>

Util::AssetImporter::AssetManager* Util::AssetImporter::AssetManager::s_assetManagerHandle = nullptr;

Util::AssetImporter::AssetManager::AssetManager()
{
	DWORD bufferLength = MAX_PATH;
	char currentDirectory[MAX_PATH + 1];
	DWORD dirPathLength = GetCurrentDirectory(bufferLength, currentDirectory);
	m_workingDir = currentDirectory;
	m_contentDir = m_workingDir + "\\Content\\";
	m_texturesDir = m_contentDir + "\\Textures\\";
	m_objectsDir = m_contentDir + "\\Objects\\";
	m_materialsDir = m_contentDir + "\\Materials\\";
	m_shadersDir = m_contentDir + "\\Shaders\\";
}

void Util::AssetImporter::AssetManager::Init()
{
	std::vector<std::string> tempDirPaths = { m_dirs.MaterialsDir, m_dirs.ObjectsDir, m_dirs.ShadersDir, m_dirs.TexturesDir};
	CheckOrCreateDirs(tempDirPaths);
	for (std::string& tempDir : tempDirPaths)
	{
		LoadAssetsFromDir(tempDir);
	}
}

std::vector<std::wstring> Util::AssetImporter::AssetManager::GetShaderPaths() const
{
	return m_shaderPaths;
}

void Util::AssetImporter::AssetManager::Create()
{
	if (!s_assetManagerHandle)
	{
		s_assetManagerHandle = new Util::AssetImporter::AssetManager();
	}
}

Util::AssetImporter::AssetManager * Util::AssetImporter::AssetManager::GetHandle()
{
	return s_assetManagerHandle;
}

void Util::AssetImporter::AssetManager::Shutdown()
{
	delete s_assetManagerHandle; 
	s_assetManagerHandle = nullptr;
}

Util::AssetImporter::AssetManager::~AssetManager()
{
}

void Util::AssetImporter::AssetManager::LoadAssetsFromDir(const std::string& dirPath)
{
	for (const auto& file : std::filesystem::directory_iterator(dirPath))
	{
		std::string filePath = file.path().string();
		std::string extension = PathFindExtension(filePath.c_str());		
		if (extension == ".hlsl")
		{
			m_shaderPaths.push_back(file.path().wstring());
		}
	}
}

void Util::AssetImporter::AssetManager::LoadShader(const std::string & shaderPath)
{

}

void Util::AssetImporter::AssetManager::LoadObj(const std::string & objPath)
{
	std::fstream obj{ objPath, std::ios::in | std::ios::ate };
	if (obj.is_open())
	{

	}
}

void Util::AssetImporter::AssetManager::CheckOrCreateDir(const std::string & dirPath)
{
	if (!std::filesystem::exists(dirPath))
	{
		std::filesystem::create_directory(dirPath);
	}
}

void Util::AssetImporter::AssetManager::CheckOrCreateDirs(const std::vector<std::string>& dirPaths)
{
	for (const std::string& path : dirPaths)
	{
		CheckOrCreateDir(path);
	}
}

