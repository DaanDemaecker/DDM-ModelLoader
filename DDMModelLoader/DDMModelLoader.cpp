// DDMModelLoader.cpp

// Header include
#include "DDMModelLoader.h"

// File includes
#include "ObjLoader.h"
#include "FbxLoader.h"

// Standard library includes
#include <iostream>

DDM::ModelLoader::ModelLoader()
{
	std::cout << "ModelLoader created \n";

	m_pObjLoader = std::make_unique<ObjLoader>();

	m_pFbxLoader = std::make_unique<FbxLoader>();
}

DDM::ModelLoader::~ModelLoader()
{
	std::cout << "ModelLoader destroyed \n";
}

void DDM::ModelLoader::LoadModel(const std::string& path, std::vector<Vertex>& vertices, std::vector<uint32_t>& indices)
{
	auto extension = GetExtension(path);

	try
	{
		if (extension == "obj")
		{
			m_pObjLoader->LoadModel(path, vertices, indices);
		}
		else if (extension == "fbx")
		{
			m_pFbxLoader->LoadModel(path, vertices, indices);
		}
		else
		{
			throw std::runtime_error(extension + " is not a supported model format");
		}
	}
	catch(const std::exception & e)
	{
		std::cerr << "Exception caught: " << e.what() << std::endl;
	}
}

std::string DDM::ModelLoader::GetExtension(const std::string& filename)
{
	// Get the index of the final period in the name, all characters after it indicate the extension
	auto index = filename.find_last_of(".");

	return  filename.substr(index + 1, filename.size());
}
