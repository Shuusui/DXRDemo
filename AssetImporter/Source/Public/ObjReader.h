#pragma once

#pragma region Includes
#include "Defines.h"
#include <string>
#pragma endregion



namespace Util
{
	namespace Util
	{
		class ASSET_IMPORTER_API ObjReader
		{
		public:
			static struct Mesh ReadObjFile(const std::string& filePath);
			static void ReadMtlFile(const std::string& filePath);
		private: 
			static struct Vertex FillVertexStruct(const std::string& vertexString);
			static struct VertexNormal FillNormalStruct(const std::string& normalString);
			static struct TextureCoord FillTexCoordStruct(const std::string& texCoordString);
			static struct Face FillFaceStruct(const std::string& faceString);
			static struct SpaceVertex FillSpaceVertexStruct(const std::string& spaceVertexString);
			static struct ColorRGB FillColorStruct(const std::string& colorString);
			static struct ColorTextureOptions FillColorTextureMapStruct(const std::string& colorMapString);
		};
	}
}