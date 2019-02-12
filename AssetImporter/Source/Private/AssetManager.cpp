#include "../Public/AssetManager.h"
#include "shlwapi.h"
#include <filesystem>
#include <fstream>

Util::AssetImporter::AssetManager::AssetManager()
{
	DWORD bufferLength = MAX_PATH;
	char currentDirectory[MAX_PATH + 1];
	DWORD dirPathLength = GetCurrentDirectory(bufferLength, currentDirectory);
	std::string workingDir = currentDirectory;
	std::string contentDir = workingDir + "\\Content\\";
	std::string texturesDir = contentDir + "\\Textures\\";
	std::string objectsDir = contentDir + "\\Objects\\";
	std::string materialsDir = contentDir + "\\Materials\\";
	std::string shadersDir = contentDir + "\\Shaders\\";
	m_dirs = {workingDir, contentDir, shadersDir, texturesDir, objectsDir, materialsDir};
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

void Util::AssetImporter::AssetManager::ImportAsset(const std::string & fileName)
{
	
}

Util::AssetImporter::Directories Util::AssetImporter::AssetManager::GetDirectories() const
{
	return m_dirs;
}

std::vector<std::string> Util::AssetImporter::AssetManager::GetShaders() const
{
	return m_shaders;
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
			LoadShader(filePath);
		}
		if (extension == ".obj")
		{
			LoadObj(filePath);
		}
		
	}
}

void Util::AssetImporter::AssetManager::LoadShader(const std::string & shaderPath)
{
	std::fstream shader{ shaderPath, std::ios::in | std::ios::ate };
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

