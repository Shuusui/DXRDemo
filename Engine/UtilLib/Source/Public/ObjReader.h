#pragma once

#pragma region Includes
#include <string>
#include "UtilStructs.h"
#include "Defines.h"

#pragma endregion



namespace Util
{
	namespace Util
	{
		class UTIL_LIB_API ObjReader
		{
		public:
			static SMesh ReadObjFile(const std::string& filePath);
			static std::vector<SMaterial> ReadMtlFile(const std::string& filePath);
		private: 
			static SVertex FillVertexStruct(const std::string& vertexString);
			static SVertexNormal FillNormalStruct(const std::string& normalString);
			static STextureCoord FillTexCoordStruct(const std::string& texCoordString);
			static SFace FillFaceStruct(const std::string& faceString);
			static SSpaceVertex FillSpaceVertexStruct(const std::string& spaceVertexString);
			static SColorRGB FillColorStruct(const std::string& colorString);
			static SColorTextureOptions FillColorTextureMapStruct(const std::string& colorMapString);
			static SBumpTextureOptions FillBumpTextureMapStruct(const std::string& bumpMapString);
			static SReflectionMap FillReflectionMapStruct(const std::string& reflMapString); 
		};
	}
}