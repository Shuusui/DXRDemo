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
		class UTIL_LIB_API MLObjReader
		{
		public:
			static SMesh ReadObjFile(const Core::Util::MLString& filePath);
			static Core::Util::MLArray<SMaterial> ReadMtlFile(const Core::Util::MLString& filePath);
		private: 
			static SVertex FillVertexStruct(const Core::Util::MLString& vertexString);
			static SVertexNormal FillNormalStruct(const Core::Util::MLString& normalString);
			static STextureCoord FillTexCoordStruct(const Core::Util::MLString& texCoordString);
			static SFace FillFaceStruct(const Core::Util::MLString& faceString);
			static SSpaceVertex FillSpaceVertexStruct(const Core::Util::MLString& spaceVertexString);
			static SColorRGB FillColorStruct(const Core::Util::MLString& colorString);
			static SColorTextureOptions FillColorTextureMapStruct(const Core::Util::MLString& colorMapString);
			static SBumpTextureOptions FillBumpTextureMapStruct(const Core::Util::MLString& bumpMapString);
			static SReflectionMap FillReflectionMapStruct(const Core::Util::MLString& reflMapString); 
		};
	}
}