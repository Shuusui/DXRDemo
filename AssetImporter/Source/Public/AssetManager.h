#pragma once

#pragma region Includes
#include <string>
#pragma endregion //Includes

namespace Util
{
	namespace AssetImporter
	{
		class AssetManager
		{
		public:
			AssetManager(const std::string& contentDirPath); 
			void ImportAsset(const std::string& fileName);
			~AssetManager();
		private: 
			std::string m_contentDirPath;
		};
	}
}