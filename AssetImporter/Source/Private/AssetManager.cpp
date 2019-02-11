#include "../Public/AssetManager.h"
#include "shlwapi.h"
#include <filesystem>
#include <fstream>

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
	LoadAssetsFromDir();
}

void Util::AssetImporter::AssetManager::ImportAsset(const std::string & fileName)
{
	
}

Util::AssetImporter::AssetManager::~AssetManager()
{
}

void Util::AssetImporter::AssetManager::LoadAssetsFromDir()
{
	for (const auto& file : std::filesystem::directory_iterator(m_shadersDir))
	{
		std::string filePath = file.path().string();
		std::string extension = PathFindExtension(filePath.c_str());		
		if (extension == ".hlsl")
		{
			std::fstream shader{ filePath, std::ios::in |std::ios::ate};
			if (shader.is_open())
			{
				std::string shaderStr;
				std::streampos size = shader.tellg();
				shaderStr.resize(size);
				shader.seekg(0, std::ios::beg);
				shader.read(shaderStr.data(), size);
				shader.close();
				m_shaders.push_back(shaderStr);
			}
		}
		
	}
}

void Util::AssetImporter::AssetManager::LoadObject()
{
}
