// ModelLoader.cpp

// Header include
#include "ModelLoader.h"

// Standard library includes
#include <stdexcept>

DDMML::ModelLoader::ModelLoader(const std::string& extension)
	:m_Extension{extension}
{
}

DDMML::ModelLoader::ModelLoader(const std::string&& extension)
	:ModelLoader(extension)
{
}

void DDMML::ModelLoader::LoadModel(const std::string& fileName, Mesh* mesh)
{
	throw std::runtime_error("Model loading is not implemented for ." + m_Extension + " files");
}

void DDMML::ModelLoader::LoadScene(const std::string& fileName, std::vector<std::unique_ptr<Mesh>>& meshes)
{
	throw std::runtime_error("Scene loading is not implemented for ." + m_Extension + " files");
}
