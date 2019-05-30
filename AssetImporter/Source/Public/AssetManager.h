#pragma once

#pragma region Includes
#include <string>
#include <vector>
#include "UtilStructs.h"
#include "Defines.h"

#pragma endregion //Includes


namespace Util
{
	namespace AssetImporter
	{
		class ASSET_IMPORTER_API AssetManager
		{
		public:
			static void Create();
			static AssetManager* GetHandle();
			static void Shutdown();

			void Init();
			std::vector<std::wstring> GetShaderPaths() const;
			std::vector<::Util::Util::SMesh> GetMeshes() const;
			~AssetManager();
		private:
			AssetManager();
			void LoadAssetsFromDir();
			void LoadObject(const std::string& filePath);
			void LoadMtl(const std::string& filePath);
			std::string m_workingDir;
			std::string m_contentDir;
			std::string m_shadersDir;
			std::string m_texturesDir;
			std::string m_objectsDir;
			std::string m_materialsDir;
			std::vector<std::wstring> m_shaderPaths;
			std::vector<::Util::Util::SMesh> m_loadedMeshes;
			static AssetManager* s_assetManagerHandle;
		};
	}
}
namespace UtAI = ::Util::AssetImporter;