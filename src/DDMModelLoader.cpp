// DDMModelLoader.cpp

// Header include
#include "DDMModelLoader.h"

// Standard library includes
#include <iostream>

DDM::ModelLoader::ModelLoader()
{
	std::cout << "ModelLoader created \n";
}

DDM::ModelLoader::~ModelLoader()
{
	std::cout << "ModelLoader destroyed \n";
}

void DDM::ModelLoader::LoadModel(const std::string& path, std::vector<Vertex>& vertices, std::vector<uint32_t>& indices)
{
	auto extension = GetExtension(path);

	std::cout << "File extension: " << extension << " is not supported\n";

}

std::string DDM::ModelLoader::GetExtension(const std::string& filename)
{
	// Get the index of the final period in the name, all characters after it indicate the extension
	auto index = filename.find_last_of(".");

	return  filename.substr(index + 1, filename.size());
}
