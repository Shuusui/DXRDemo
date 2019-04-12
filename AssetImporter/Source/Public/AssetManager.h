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
			static void Create(); 
			static AssetManager* GetHandle(); 
			static void Shutdown();

			void Init();
			std::vector<std::wstring> GetShaderPaths() const; 
			~AssetManager();
		private: 
			AssetManager();
			void LoadAssetsFromDir();
			void LoadObject();
			std::string m_workingDir;
			std::string m_contentDir; 
			std::string m_shadersDir; 
			std::string m_texturesDir;
			std::string m_objectsDir;
			std::string m_materialsDir;
			std::vector<std::wstring> m_shaderPaths;
			static AssetManager* s_assetManagerHandle;
		};
	}
}
namespace UtAI = ::Util::AssetImporter;