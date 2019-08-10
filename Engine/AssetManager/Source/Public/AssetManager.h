#pragma once

#pragma region Includes
#include <string>
#include <vector>
#include "UtilStructs.h"
#include "Defines.h"

#pragma endregion //Includes


namespace Util
{
	namespace AssetManager
	{
		class ASSET_MANAGER_API MLAssetManager
		{
		public:
			static void Create();
			static MLAssetManager* GetHandle();
			static void Shutdown();

			void Init();
			[[nodiscard]] std::vector<std::wstring> GetShaderPaths() const;
			[[nodiscard]] std::vector<Util::SMesh> GetMeshes() const;
			~MLAssetManager();
		private:
			MLAssetManager();
			void LoadAssetsFromDir();
			void LoadObject(const std::string& filePath);
			static void LoadMtl(const std::string& filePath);
			std::string m_workingDir;
			std::string m_contentDir;
			std::string m_shadersDir;
			std::string m_texturesDir;
			std::string m_objectsDir;
			std::string m_materialsDir;
			std::vector<std::wstring> m_shaderPaths;
			std::vector<Util::SMesh> m_loadedMeshes;
			static MLAssetManager* s_assetManagerHandle;
		};
	}
}
namespace UtAI = ::Util::AssetManager;
