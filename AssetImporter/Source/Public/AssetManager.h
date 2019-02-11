#pragma once

#pragma region Includes
#include <string>
#include <vector>
#pragma endregion //Includes

#define ASSET_IMPORTER_API __declspec(dllexport)



namespace Util
{
	namespace AssetImporter
	{
		class ASSET_IMPORTER_API AssetManager
		{
		public:
			AssetManager(); 
			void Init();
			void ImportAsset(const std::string& fileName);
			~AssetManager();
		private: 
			void LoadAssetsFromDir();
			void LoadObject();
			std::string m_workingDir;
			std::string m_contentDir; 
			std::string m_shadersDir; 
			std::string m_texturesDir;
			std::string m_objectsDir;
			std::string m_materialsDir;
			std::vector<std::string> m_shaders;
		};
	}
}
namespace UtAI = ::Util::AssetImporter;