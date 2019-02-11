#include "../Public/AssetManager.h"
#include "shlwapi.h"

Util::AssetImporter::AssetManager::AssetManager(const std::string & contentDirPath)
	:m_contentDirPath(contentDirPath)
{
}

void Util::AssetImporter::AssetManager::ImportAsset(const std::string & fileName)
{
	const char* extension = PathFindExtension(fileName.c_str());
}

Util::AssetImporter::AssetManager::~AssetManager()
{
}
