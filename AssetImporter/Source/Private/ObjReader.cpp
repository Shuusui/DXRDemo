#include "../Public/ObjReader.h"
#include <fstream>
#include "../Public/AssetStructs.h"
#include <thread>

Util::Util::Mesh Util::Util::ObjReader::ReadObjFile(const std::string& filePath)
{
	std::ifstream objFile{ filePath };
	VerticesInformation infos = {};
	std::vector<Object> objects = {};
	if (objFile.is_open())
	{
		std::string line = {};
		Object object = {};
		while (std::getline(objFile, line))
		{
			switch (line[0])
			{
			case 'v':
				if (!isspace(line[1]))
				{
					switch (line[1])
					{
					case 't':
						infos.TextureCoords.push_back(FillTexCoordStruct(line.substr(3, line.size() - 3)));
						break;
					case 'n':
						infos.Normals.push_back(FillNormalStruct(line.substr(3, line.size() - 3)));
						break;
					case 'p':
						infos.SpaceVertices.push_back(FillSpaceVertexStruct(line.substr(3, line.size() - 3)));
						break;
					}
					break;
				}
				infos.Vertices.push_back(FillVertexStruct(line.substr(2, line.size() - 2)));
				break;
			case 'u':
				object.Material = line.substr(7, line.size() - 7);
				break;
			case 'o':
				if (!object.Material.empty())
				{
					objects.push_back(object);
				}
				object = {};
				object.Name = line.substr(2, line.size() - 2);
				break;
			case 's':
				if (line[3] != 'o')
				{
					object.SmootingGroup = atoi(line.substr(2, line.size() - 2).c_str());
				}
				break;
			case 'f' :
				object.Faces.push_back(FillFaceStruct(line.substr(2, line.size() - 2)));
				break;
			case '#':
				continue;
			case 'm':
				infos.MtlLibs.push_back(line.substr(7, line.size() - 7));
				break;
			}
		}
		if (!object.Material.empty())
		{
			objects.push_back(object);
		}
		objFile.close();
	}
	return Mesh{ infos, objects };

}

void Util::Util::ObjReader::ReadMtlFile(const std::string& filePath)
{
	std::ifstream mtlFile{ filePath };
	std::vector<Material> materials = {};
	if (mtlFile.is_open())
	{
		std::string line = {};
		Material material = {};
		while (std::getline(mtlFile, line))
		{
			switch (line[0])
			{
			case 'n':
				if (material.Name.empty())
				{
					material.Name = line.substr(7, line.size() - 7);
					break;
				}
				materials.push_back(material);
				material = {};
				break;
			case 'K':
				switch (line[1])
				{
				case 'a':
					material.Ambient = FillColorStruct(line.substr(3, line.size() - 3));
					break;
				case 'd':
					material.Diffuse = FillColorStruct(line.substr(3, line.size() - 3));
					break;
				case 's':
					material.Specular.Color = FillColorStruct(line.substr(3, line.size() - 3));
					break;
				}
				break;
			case 'N':
				switch (line[1])
				{
				case 'i':
					material.OpticalDensity = atof(line.substr(3, line.size() - 3).c_str());
					break;
				case 's':
					material.Specular.Exponent = atof(line.substr(3, line.size() - 3).c_str());
					break;
				}
				break;
			case 'd':
				if (line[3] == '-')
				{
					material.Dissolve.Halo = true;
					material.Dissolve.Value = atof(line.substr(8, line.size() - 8).c_str());
					break;
				}
				material.Dissolve.Value = atof(line.substr(3, line.size() - 3).c_str());
				break;
			case 'i':
				material.Illum = atoi(line.substr(6, line.size() - 6).c_str());
				break;
			}
		}
		mtlFile.close();
	}
}

Util::Util::Vertex Util::Util::ObjReader::FillVertexStruct(const std::string& vertexString)
{
	Vertex vertex = {};
	std::string tempStr = {};
	uint8_t vertexIn = 0;
	for (int i = 0; i < vertexString.size(); i++)
	{
		if (!isspace(vertexString[i]))
		{
			tempStr.push_back(vertexString[i]);
			if (i < vertexString.size()-1)
			{
				continue;
			}
		}
		switch (vertexIn)
		{
		case 0:
			vertex.X = atof(tempStr.c_str());
			break;
		case 1:
			vertex.Y = atof(tempStr.c_str());
			break;
		case 2:
			vertex.Z = atof(tempStr.c_str());
			break;
		case 3:
			vertex.W = atof(tempStr.c_str());
			break;
		}
		vertexIn++;
		tempStr.clear();
	}
	return vertex;
}

Util::Util::VertexNormal Util::Util::ObjReader::FillNormalStruct(const std::string& normalString)
{
	VertexNormal normal = {};
	std::string tempStr = {};
	uint8_t normalIn = 0;
	for (int i = 0; i < normalString.size(); i++)
	{
		if (!isspace(normalString[i]))
		{
			tempStr.push_back(normalString[i]);
			if (i < normalString.size() - 1)
			{
				continue;
			}
		}
		switch (normalIn)
		{
		case 0:
			normal.X = atof(tempStr.c_str());
			break;
		case 1:
			normal.Y = atof(tempStr.c_str());
			break;
		case 2:
			normal.Z = atof(tempStr.c_str());
			break;
		}
		normalIn++;
		tempStr.clear();
	}
	return normal;
}

Util::Util::TextureCoord Util::Util::ObjReader::FillTexCoordStruct(const std::string& texCoordString)
{
	TextureCoord texCoord = {};
	std::string tempStr = {};
	uint8_t texCoordIn = 0;
	for (int i = 0; i < texCoordString.size(); i++)
	{
		if (!isspace(texCoordString[i]))
		{
			tempStr.push_back(texCoordString[i]);
			if (i < texCoordString.size() - 1)
			{
				continue;
			}
		}
		switch (texCoordIn)
		{
		case 0:
			texCoord.U = atof(tempStr.c_str());
			break;
		case 1:
			texCoord.V = atof(tempStr.c_str());
			break;
		case 2:
			texCoord.W = atof(tempStr.c_str());
			break;
		}
		texCoordIn++;
		tempStr.clear();
	}

	return texCoord;
}

Util::Util::Face Util::Util::ObjReader::FillFaceStruct(const std::string& faceString)
{
	Face face = {};
	VertexInformation info = {};
	std::string tempStr = {};
	uint8_t infoIndex = 0;
	for (const char& c : faceString)
	{
		if (!isspace(c) && c != '/')
		{
			tempStr.push_back(c);
			continue;
		}
		if (c == '/')
		{
			switch (infoIndex)
			{
			case 0:
				
				info.VertexIndex = atoi(tempStr.c_str());
				break;
			case 1:
				info.TexCoordIndex = atoi(tempStr.c_str());
				break;
			}
			tempStr.clear();
			infoIndex++;
			continue;
		}
		if (isspace(c))
		{
			info.NormalIndex = atoi(tempStr.c_str());
			tempStr.clear();
			infoIndex = 0;
			face.Vertices.push_back(info);
			info = {};
		}
	}
	info.NormalIndex = atoi(tempStr.c_str());
	face.Vertices.push_back(info);
	return face;
}

Util::Util::SpaceVertex Util::Util::ObjReader::FillSpaceVertexStruct(const std::string& spaceVertexString)
{
	SpaceVertex spaceVertex = {};
	std::string tempStr = {};
	uint8_t stringIndex = 0;
	for (int32_t i = 0; i < spaceVertexString.size(); i++)
	{
		if (!isspace(spaceVertexString[i]))
		{
			tempStr.push_back(spaceVertexString[i]);
			if (i < spaceVertexString.size() - 1)
			{
				continue;
			}
		}
		switch (stringIndex)
		{
		case 0:
			spaceVertex.U = atof(tempStr.c_str());
			break;
		case 1: 
			spaceVertex.V = atof(tempStr.c_str());
			break;
		case 2:
			spaceVertex.W = atof(tempStr.c_str());
			break;
		}
		stringIndex++;
		tempStr.clear();
	}
	return spaceVertex;
}

Util::Util::ColorRGB Util::Util::ObjReader::FillColorStruct(const std::string& colorString)
{
	ColorRGB color = {};
	std::string tempStr = {};
	uint8_t stringIndex = 0;
	for (const char& c : colorString)
	{
		if (!isspace(c))
		{
			tempStr.push_back(c);
			continue;
		}
		switch (stringIndex)
		{
		case 0:
			color.R = atof(tempStr.c_str());
			break;
		case 1:
			color.G = atof(tempStr.c_str());
		}
		tempStr.clear();
		stringIndex++;
	}
	color.B = atof(tempStr.c_str());
	return color;
}
