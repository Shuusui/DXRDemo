#pragma once

#include "MLArray.h"
#include "MLString.h"
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
			Core::Util::MLArray<SVertex> Vertices = {};
			Core::Util::MLArray<STextureCoord> TextureCoords = {};
			Core::Util::MLArray<SVertexNormal> Normals = {};
			Core::Util::MLArray<SSpaceVertex> SpaceVertices = {};
			Core::Util::MLArray<Core::Util::MLString> MtlLibs = {};
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
			Core::Util::MLArray<SFace> Faces = {};
			Core::Util::MLString Name = {};
			Core::Util::MLString Material = {};
			int32_t SmoothingGroup = 0;
		};
		struct UTIL_LIB_API SMesh
		{
			SVerticesInformation Vertices = {};
			Core::Util::MLArray<SObject> Objects = {};
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
			Core::Util::MLString TextureName = {};
			SMMOption MM = {};
			STexResOption TexRes = {};
			bool BlendU = true;
			bool BlendV = true;
			bool Clamp = false;
		};
		namespace TextureChannel
		{
			const uint8_t R_CHANNEL = 0b0000'0001;
			const uint8_t G_CHANNEL = 0b0000'0010;
			const uint8_t B_CHANNEL = 0b0000'0100;
			const uint8_t M_CHANNEL = 0b0000'1000;
			const uint8_t L_CHANNEL = 0b0001'0000;
			const uint8_t Z_CHANNEL = 0b0010'0000;
		}
		struct UTIL_LIB_API SColorTextureOptions : public STextureOptionBase
		{
			bool Cc = false; 
		};
		struct UTIL_LIB_API SScalarTextureOptions : public STextureOptionBase
		{
			uint8_t ImfChannel = TextureChannel::L_CHANNEL;
		};
		struct UTIL_LIB_API SBumpTextureOptions : public STextureOptionBase
		{
			float BmMult = 1.0f;
			uint8_t ImfChannel = TextureChannel::L_CHANNEL;
		};
		struct UTIL_LIB_API SReflectionMapOptions : public SColorTextureOptions
		{
			EReflectionType ReflectionType = EReflectionType::Sphere;
		};
		struct UTIL_LIB_API SReflectionMap
		{
			Core::Util::MLArray<SReflectionMapOptions> CubeReflectionTextures;
		};
		struct UTIL_LIB_API SDissolveOption
		{
			float Value = 0.0f; 
			bool Halo = false; 
		};
		struct UTIL_LIB_API SMaterial
		{
			Core::Util::MLString Name = {};
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