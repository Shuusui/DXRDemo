#pragma once
#include <string>
#include <vector>
#include "AssetEnums.h"


namespace Util
{
	namespace Util
	{
		struct Vertex
		{
			float X = 0.0f;
			float Y = 0.0f;
			float Z = 0.0f;
			float W = 1.0f;
		};
		struct TextureCoord
		{
			float U = 0.0f;
			float V = 0.0f;
			float W = 0.0f;
		};
		struct VertexNormal
		{
			float X = 0.0f;
			float Y = 0.0f;
			float Z = 0.0f;
		};
		struct SpaceVertex
		{
			float U = 0.0f; 
			float V = 0.0f; 
			float W = 0.0f;
		};
		struct VerticesInformation
		{
			std::vector<Vertex> Vertices = {};
			std::vector<TextureCoord> TextureCoords = {};
			std::vector<VertexNormal> Normals = {};
			std::vector<SpaceVertex> SpaceVertices = {};
			std::vector<std::string> MtlLibs = {};
		};
		struct VertexInformation
		{
			int32_t VertexIndex = 0; 
			int32_t NormalIndex = 0;
			int32_t TexCoordIndex = 0;
		};
		struct Face
		{
			std::vector<VertexInformation> Vertices = {};
		};
		struct Object
		{
			std::vector<Face> Faces = {};
			std::string Name = {};
			std::string Material = {};
			int32_t SmootingGroup = 0;
		};
		struct Mesh
		{
			VerticesInformation Vertices = {};
			std::vector<Object> Objects = {};
		};
		struct ColorRGB
		{
			float R = 0.0f; 
			float G = 0.0f; 
			float B = 0.0f; 
		};
		struct Specular 
		{
			ColorRGB Color = {};
			float Exponent = 0.0f;
		};
		struct OriginOffset
		{
			float O = 0.0f;
			float U = 0.0f;
			float V = 0.0f;
			float W = 0.0f;
		};
		struct Scale
		{
			float S = 1.0f;
			float U = 1.0f;
			float V = 1.0f;
			float W = 0.0f;
		};
		struct Turbulance
		{
			float T = 0.0f;
			float U = 0.0f;
			float V = 0.0f;
			float W = 0.0f;
		};
		struct MMOption
		{
			int32_t Base = 0;
			int32_t Gain = 1;
		};
		struct TexResOption
		{
			float X = 0.0f; 
			float Y = 0.0f;
		};
		struct TextureOptionBase
		{
			OriginOffset Offset = {};
			Scale ScaleApply = {};
			Turbulance TurbulanceApply = {};
			std::string TextureName = {};
			MMOption MM = {};
			TexResOption TexRes = {};
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
		struct ColorTextureOptions : public TextureOptionBase
		{
			bool Cc = false; 
		};
		struct ScalarTextureOptions : public TextureOptionBase
		{
			uint8_t ImfChannel = TextureChannel::LChannel;
		};
		struct BumbTextureOptions : public TextureOptionBase
		{
			float BmMult = 1.0f;
			uint8_t ImfChannel = TextureChannel::LChannel;
		};
		struct ReflectionMapOptions : public ColorTextureOptions
		{
			EReflectionType ReflectionType = EReflectionType::Sphere;
		};
		struct ReflectionMap
		{
			std::vector<ReflectionMapOptions> CubeReflectionTextures;
		};
		struct DissolveOption
		{
			float Value = 0.0f; 
			bool Halo = false; 
		};
		struct Material
		{
			std::string Name = {};
			BumbTextureOptions BumpMapTexture = {};
			ReflectionMap ReflectionMap = {};
			ScalarTextureOptions SpecularExponentMapTexture = {};
			ScalarTextureOptions DissolveMaptexture = {};
			ScalarTextureOptions DecalMapTexture = {};
			ScalarTextureOptions DispMapTexture = {};
			ColorTextureOptions AmbientMapTexture = {};
			ColorTextureOptions DiffuseMapTexture = {};
			ColorTextureOptions SpecularMapTexture = {};
			Specular Specular = {};
			ColorRGB Ambient = {};
			ColorRGB Diffuse = {}; 
			ColorRGB TransmissionFilter = {};
			DissolveOption Dissolve = {};
			float Sharpness = 60;
			float OpticalDensity = 1.0f;
			uint8_t Illum = 0;
		};
	}
}