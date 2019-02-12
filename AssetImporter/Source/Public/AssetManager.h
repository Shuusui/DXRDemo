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

		struct ASSET_IMPORTER_API Directories
		{
			std::string WorkingDir;
			std::string ContentDir;
			std::string ShadersDir;
			std::string TexturesDir;
			std::string ObjectsDir;
			std::string MaterialsDir;
		};
		class ASSET_IMPORTER_API AssetManager
		{
		public:
			AssetManager();
			void Init();
			void ImportAsset(const std::string& fileName);
			Directories GetDirectories() const; 
			std::vector<std::string> GetShaders() const; 
			~AssetManager();
		private:
			void LoadAssetsFromDir(const std::string& dirPath);
			void LoadShader(const std::string& shaderPath);
			void LoadObj(const std::string& objPath);
			void CheckOrCreateDir(const std::string& dirPath);
			void CheckOrCreateDirs(const std::vector<std::string>& dirPaths);
			Directories m_dirs; 
			std::vector<std::string> m_shaders;
		};
	}
}
namespace UtAI = ::Util::AssetImporter;