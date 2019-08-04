#include "../Public/ObjReader.h"
#include <fstream>
#include <thread>

Util::Util::SMesh Util::Util::ObjReader::ReadObjFile(const std::string& filePath)
{
	std::ifstream objFile{ filePath };
	SVerticesInformation infos = {};
	std::vector<SObject> objects = {};
	if (objFile.is_open())
	{
		std::string line = {};
		SObject object = {};
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
					object.SmoothingGroup = atoi(line.substr(2, line.size() - 2).c_str());
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
	return SMesh{ infos, objects };

}

std::vector<Util::Util::SMaterial> Util::Util::ObjReader::ReadMtlFile(const std::string& filePath)
{
	std::ifstream mtlFile{ filePath };
	std::vector<::Util::Util::SMaterial> materials = {};
	if (mtlFile.is_open())
	{
		std::string line = {};
		::Util::Util::SMaterial material = {};
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
				material.Name = line.substr(7, line.size() - 7);
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
					material.OpticalDensity = static_cast<float>(atof(line.substr(3, line.size() - 3).c_str()));
					break;
				case 's':
					material.Specular.Exponent = static_cast<float>(atof(line.substr(3, line.size() - 3).c_str()));
					break;
				}
				break;
			case 'd':
				if (line[3] == '-')
				{
					material.Dissolve.Halo = true;
					material.Dissolve.Value = static_cast<float>(atof(line.substr(8, line.size() - 8).c_str()));
					break;
				}
				material.Dissolve.Value = static_cast<float>(atof(line.substr(2, line.size() - 2).c_str()));
				break;
			case 'i':
				material.Illum = static_cast<uint8_t>(atoi(line.substr(6, line.size() - 6).c_str()));
				break;
			case 'm':
				switch (line[4])
				{
				case 'K':
					switch (line[5])
					{
					case 'd':
						material.DiffuseMapTexture = FillColorTextureMapStruct(line.substr(6, line.size() - 6));
						break;
					case 'a':
						material.AmbientMapTexture = FillColorTextureMapStruct(line.substr(6, line.size() - 6));
						break;
					case 's':
						material.SpecularMapTexture = FillColorTextureMapStruct(line.substr(6, line.size() - 6));
						break;
					}
					break;
				case 'B':
					material.BumpMapTexture = FillBumpTextureMapStruct(line.substr(5, line.size() - 5));
					break;
				}
				break;
			case 'r':
				material.ReflectionMap = FillReflectionMapStruct(line.substr(5, line.size() - 5));
				break;
			}
		}
		if (!material.Name.empty())
		{
			materials.push_back(material);
		}
		mtlFile.close();
	}
	return materials;
}

Util::Util::SVertex Util::Util::ObjReader::FillVertexStruct(const std::string& vertexString)
{
	SVertex vertex = {};
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
			vertex.X = static_cast<float>(atof(tempStr.c_str()));
			break;
		case 1:
			vertex.Y = static_cast<float>(atof(tempStr.c_str()));
			break;
		case 2:
			vertex.Z = static_cast<float>(atof(tempStr.c_str()));
			break;
		case 3:
			vertex.W = static_cast<float>(atof(tempStr.c_str()));
			break;
		}
		vertexIn++;
		tempStr.clear();
	}
	return vertex;
}

Util::Util::SVertexNormal Util::Util::ObjReader::FillNormalStruct(const std::string& normalString)
{
	SVertexNormal normal = {};
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
			normal.X = static_cast<float>(atof(tempStr.c_str()));
			break;
		case 1:
			normal.Y = static_cast<float>(atof(tempStr.c_str()));
			break;
		case 2:
			normal.Z = static_cast<float>(atof(tempStr.c_str()));
			break;
		}
		normalIn++;
		tempStr.clear();
	}
	return normal;
}

Util::Util::STextureCoord Util::Util::ObjReader::FillTexCoordStruct(const std::string& texCoordString)
{
	STextureCoord texCoord = {};
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
			texCoord.U = static_cast<float>(atof(tempStr.c_str()));
			break;
		case 1:
			texCoord.V = static_cast<float>(atof(tempStr.c_str()));
			break;
		case 2:
			texCoord.W = static_cast<float>(atof(tempStr.c_str()));
			break;
		}
		texCoordIn++;
		tempStr.clear();
	}

	return texCoord;
}

Util::Util::SFace Util::Util::ObjReader::FillFaceStruct(const std::string& faceString)
{
	SFace face = {};
	SVertexInformation info = {};
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

Util::Util::SSpaceVertex Util::Util::ObjReader::FillSpaceVertexStruct(const std::string& spaceVertexString)
{
	SSpaceVertex spaceVertex = {};
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
			spaceVertex.U = static_cast<float>(atof(tempStr.c_str()));
			break;
		case 1: 
			spaceVertex.V = static_cast<float>(atof(tempStr.c_str()));
			break;
		case 2:
			spaceVertex.W = static_cast<float>(atof(tempStr.c_str()));
			break;
		}
		stringIndex++;
		tempStr.clear();
	}
	return spaceVertex;
}

Util::Util::SColorRGB Util::Util::ObjReader::FillColorStruct(const std::string& colorString)
{
	SColorRGB color = {};
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
			color.R = static_cast<float>(atof(tempStr.c_str()));
			break;
		case 1:
			color.G = static_cast<float>(atof(tempStr.c_str()));
		}
		tempStr.clear();
		stringIndex++;
	}
	color.B = static_cast<float>(atof(tempStr.c_str()));
	return color;
}

Util::Util::SColorTextureOptions Util::Util::ObjReader::FillColorTextureMapStruct(const std::string& colorMapString)
{
	SColorTextureOptions colorOption = {};
	for (uint8_t i = 0; i < colorMapString.size(); i++)
	{
		if (colorMapString[i] == '-')
		{
			std::string tempStr = {};
			switch (colorMapString[(size_t)i + 1])
			{
			case 's':
			{
				tempStr = colorMapString.substr((size_t)i + 2, colorMapString.size() - ((size_t)i + 2));
				std::string scaleStr = {};
				uint8_t scaleIndex = 0;
				uint8_t scaleStrSize = 0;
				for (const char& c : tempStr)
				{
					if (!isdigit(c) && !isspace(c)) 
					{
						break;
					}
					if (!isspace(c))
					{
						scaleStr.push_back(c);
						continue;
					}
					switch (scaleIndex)
					{
					case 0:
						colorOption.ScaleApply.S = static_cast<float>(atof(scaleStr.c_str()));
						break;
					case 1:
						colorOption.ScaleApply.U = static_cast<float>(atof(scaleStr.c_str()));
						break;
					case 2: 
						colorOption.ScaleApply.V = static_cast<float>(atof(scaleStr.c_str()));
						break;
					}
					scaleStrSize += static_cast<uint8_t>(scaleStr.size());
					scaleIndex++;
					scaleStr.clear();
				}
				switch (scaleIndex)
				{
				case 2:
					colorOption.ScaleApply.V = static_cast<float>(atof(scaleStr.c_str()));
					i += static_cast<uint8_t>(scaleStrSize + scaleStr.size() + 3);
					break;
				case 3:
					colorOption.ScaleApply.W = static_cast<float>(atof(scaleStr.c_str()));
					i += static_cast<uint8_t>(scaleStrSize + scaleStr.size() + 4);
					break;
				}
			}
				break;
			case 'o':
			{
				tempStr = colorMapString.substr((size_t)i + 2, colorMapString.size() - ((size_t)i + 2));
				std::string offsetStr = {};
				uint8_t offsetStrSize = 0;
				uint8_t offsetIndex = 0;
				for (const char& c : tempStr)
				{
					if (!isspace(c))
					{
						offsetStr.push_back(c);
						continue;
					}
					switch (offsetIndex)
					{
					case 0:
						colorOption.Offset.O = static_cast<float>(atof(offsetStr.c_str()));
						break;
					case 1:
						colorOption.Offset.U = static_cast<float>(atof(offsetStr.c_str()));
						break;
					case 2:
						colorOption.Offset.V = static_cast<float>(atof(offsetStr.c_str()));
						break;
					}
					offsetStrSize += static_cast<uint8_t>(offsetStr.size());
					offsetIndex++;
					offsetStr.clear();
				}
				switch (offsetIndex)
				{
				case 2:
					colorOption.Offset.V = static_cast<float>(atof(offsetStr.c_str()));
					i += static_cast<uint8_t>(offsetStrSize + offsetStr.size() + 3);
					break;
				case 3:
					colorOption.Offset.W = static_cast<float>(atof(offsetStr.c_str()));
					i += static_cast<uint8_t>(offsetStrSize + offsetStr.size() + 4);
					break;
				}
			}
			}
			continue;
		}
		colorOption.TextureName = colorMapString.substr(i, colorMapString.size() - i);
		break;
	}
	return colorOption;
}

Util::Util::SBumpTextureOptions Util::Util::ObjReader::FillBumpTextureMapStruct(const std::string& bumpMapString)
{
	SBumpTextureOptions bumpOption = {};


	return bumpOption; 
}

Util::Util::SReflectionMap Util::Util::ObjReader::FillReflectionMapStruct(const std::string& reflMapString)
{
	SReflectionMap reflMap = {};
	for (size_t i = 0; i < reflMapString.size(); i++)
	{
	switch (reflMapString[i])
	{
	case '-':
		switch (reflMapString[i+1])
		{
		case 't':
			switch (reflMapString[i + 2])
			{
			case 's':
			{
				SReflectionMapOptions reflMapOpt = {};
				reflMapOpt.ReflectionType = EReflectionType::Sphere;
			}
				break;
			case 'c':
				switch (reflMapString[5])
				{
				case 't':
					break;
				case 'b':
					switch (reflMapString[6])
					{
					case 'o':
						break;
					case'a':
						break;
					}
					break;
				case 'f':
					break;
				case 'l':
					break;
				case'r':
					break;
				}
				break;
			}
			break;
		}
		break;
	
	}

	}
	return reflMap; 
}
