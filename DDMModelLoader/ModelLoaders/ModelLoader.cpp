// ModelLoader.cpp

// Header include
#include "ModelLoader.h"

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
	throw "Model loading is not implemented for ." + m_Extension + " files";
}

void DDMML::ModelLoader::LoadScene(const std::string& fileName, std::vector<std::unique_ptr<Mesh>>& meshes)
{
	throw "Scene loading is not implemented for ." + m_Extension + " files";
}
