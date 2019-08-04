#pragma once
#include <string>
#include <vector>
#include "Defines.h"
#include "UtilEnums.h"



namespace Util
{
	namespace Util
	{
		struct UTIL_LIB_API SVertex
		{
			float X = 0.0f;
			float Y = 0.0f;
			float Z = 0.0f;
			float W = 1.0f;
		};
		struct UTIL_LIB_API STextureCoord
		{
			float U = 0.0f;
			float V = 0.0f;
			float W = 0.0f;
		};
		struct UTIL_LIB_API SVertexNormal
		{
			float X = 0.0f;
			float Y = 0.0f;
			float Z = 0.0f;
		};
		struct UTIL_LIB_API SSpaceVertex
		{
			float U = 0.0f; 
			float V = 0.0f; 
			float W = 0.0f;
		};
		struct UTIL_LIB_API SVerticesInformation
		{
			std::vector<SVertex> Vertices = {};
			std::vector<STextureCoord> TextureCoords = {};
			std::vector<SVertexNormal> Normals = {};
			std::vector<SSpaceVertex> SpaceVertices = {};
			std::vector<std::string> MtlLibs = {};
		};
		struct UTIL_LIB_API SVertexInformation
		{
			int32_t VertexIndex = 0; 
			int32_t NormalIndex = 0;
			int32_t TexCoordIndex = 0;
		};
		struct UTIL_LIB_API SFace
		{
			std::vector<SVertexInformation> Vertices = {};
		};
		struct UTIL_LIB_API SObject
		{
			std::vector<SFace> Faces = {};
			std::string Name = {};
			std::string Material = {};
			int32_t SmoothingGroup = 0;
		};
		struct UTIL_LIB_API SMesh
		{
			SVerticesInformation Vertices = {};
			std::vector<SObject> Objects = {};
		};
		struct UTIL_LIB_API SColorRGB
		{
			float R = 0.0f; 
			float G = 0.0f; 
			float B = 0.0f; 
		};
		struct UTIL_LIB_API SSpecular
		{
			SColorRGB Color = {};
			float Exponent = 0.0f;
		};
		struct UTIL_LIB_API SOriginOffset
		{
			float O = 0.0f;
			float U = 0.0f;
			float V = 0.0f;
			float W = 0.0f;
		};
		struct UTIL_LIB_API SScale
		{
			float S = 1.0f;
			float U = 1.0f;
			float V = 1.0f;
			float W = 0.0f;
		};
		struct UTIL_LIB_API STurbulance
		{
			float T = 0.0f;
			float U = 0.0f;
			float V = 0.0f;
			float W = 0.0f;
		};
		struct UTIL_LIB_API SMMOption
		{
			int32_t Base = 0;
			int32_t Gain = 1;
		};
		struct UTIL_LIB_API STexResOption
		{
			float X = 0.0f; 
			float Y = 0.0f;
		};
		struct UTIL_LIB_API STextureOptionBase
		{
			SOriginOffset Offset = {};
			SScale ScaleApply = {};
			STurbulance TurbulanceApply = {};
			std::string TextureName = {};
			SMMOption MM = {};
			STexResOption TexRes = {};
			bool BlendU = true;
			bool BlendV = true;
			bool Clamp = false;
		};
		namespace TextureChannel
		{
			const uint8_t RChannel = 0b0000'0001;
			const uint8_t GChannel = 0b0000'0010;
			const uint8_t BChannel = 0b0000'0100;
			const uint8_t MChannel = 0b0000'1000;
			const uint8_t LChannel = 0b0001'0000;
			const uint8_t ZChannel = 0b0010'0000;
		}
		struct UTIL_LIB_API SColorTextureOptions : public STextureOptionBase
		{
			bool Cc = false; 
		};
		struct UTIL_LIB_API SScalarTextureOptions : public STextureOptionBase
		{
			uint8_t ImfChannel = TextureChannel::LChannel;
		};
		struct UTIL_LIB_API SBumpTextureOptions : public STextureOptionBase
		{
			float BmMult = 1.0f;
			uint8_t ImfChannel = TextureChannel::LChannel;
		};
		struct UTIL_LIB_API SReflectionMapOptions : public SColorTextureOptions
		{
			EReflectionType ReflectionType = EReflectionType::Sphere;
		};
		struct UTIL_LIB_API SReflectionMap
		{
			std::vector<SReflectionMapOptions> CubeReflectionTextures;
		};
		struct UTIL_LIB_API SDissolveOption
		{
			float Value = 0.0f; 
			bool Halo = false; 
		};
		struct UTIL_LIB_API SMaterial
		{
			std::string Name = {};
			SBumpTextureOptions BumpMapTexture = {};
			SReflectionMap ReflectionMap = {};
			SScalarTextureOptions SpecularExponentMapTexture = {};
			SScalarTextureOptions DissolveMaptexture = {};
			SScalarTextureOptions DecalMapTexture = {};
			SScalarTextureOptions DispMapTexture = {};
			SColorTextureOptions AmbientMapTexture = {};
			SColorTextureOptions DiffuseMapTexture = {};
			SColorTextureOptions SpecularMapTexture = {};
			SSpecular Specular = {};
			SColorRGB Ambient = {};
			SColorRGB Diffuse = {}; 
			SColorRGB TransmissionFilter = {};
			SDissolveOption Dissolve = {};
			float Sharpness = 60;
			float OpticalDensity = 1.0f;
			uint8_t Illum = 0;
		};
	}
}