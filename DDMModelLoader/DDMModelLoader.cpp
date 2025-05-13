// DDMModelLoader.cpp

// Header include
#include "DDMModelLoader.h"

// File includes
#include "ModelLoaders/ObjLoader.h"
#include "ModelLoaders/GltfLoader.h"
#include "ModelLoaders/FbxLoader.h"

// Standard library includes
#include <iostream>
#include <cctype>
#include <algorithm>


DDMML::DDMModelLoader::DDMModelLoader()
{
	m_ModelLoaders["obj"] = std::make_unique<DDMML::ObjLoader>();

	m_ModelLoaders["gltf"] = std::make_unique<DDMML::GltfLoader>();

	m_ModelLoaders["fbx"] = std::make_unique<DDMML::FbxLoader>();
}


DDMML::DDMModelLoader::~DDMModelLoader()
{

}

void DDMML::DDMModelLoader::LoadModel(const std::string& fileName, Mesh* mesh)
{
	auto extension = GetExtension(fileName);

	std::transform(extension.begin(), extension.end(), extension.begin(),
		[](unsigned char c) { return std::tolower(c); });

	try
	{
		if (m_ModelLoaders.find(extension) != m_ModelLoaders.end())
		{
			m_ModelLoaders[extension]->LoadModel(fileName, mesh);
			SetupTangents(mesh->GetVertices(), mesh->GetIndices());
		}
		else
		{
			throw std::runtime_error(extension + " is not supported by DDMModelLoader ");
		}
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}


void DDMML::DDMModelLoader::LoadScene(const std::string& fileName, std::vector<std::unique_ptr<Mesh>>& meshes)
{
	auto extension = GetExtension(fileName);

	std::transform(extension.begin(), extension.end(), extension.begin(),
		[](unsigned char c) { return std::tolower(c); });

	try
	{
		if (m_ModelLoaders.find(extension) != m_ModelLoaders.end())
		{
			m_ModelLoaders[extension]->LoadScene(fileName, meshes);
		}
		else
		{
			throw std::runtime_error(extension + " is not supported by DDMModelLoader ");
		}
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}

std::string DDMML::DDMModelLoader::GetExtension(const std::string& filename)
{
	// Get the index of the final period in the name, all characters after it indicate the extension
	auto index = filename.find_last_of(".");

	return  filename.substr(index + 1, filename.size());
}

void DDMML::DDMModelLoader::SetupTangents(std::vector<Vertex>& vertices, std::vector<uint32_t>& indices)
{
	// After all vertices are added loop through them to calculate the tangents
	for (size_t i = 0; i < indices.size(); i += 3)
	{
		// Get the indices of the current triangle
		uint32_t index0 = indices[i];
		uint32_t index1 = indices[i + 1];
		uint32_t index2 = indices[i + 2];

		// Get the vertices associated with this triangle
		Vertex& v0 = vertices[index0];
		Vertex& v1 = vertices[index1];
		Vertex& v2 = vertices[index2];

		// Get 2 edges of this triangle
		glm::vec3 edge1 = v1.pos - v0.pos;
		glm::vec3 edge2 = v2.pos - v0.pos;

		// Get the difference in UV over these edges
		glm::vec2 deltaUV1 = v1.texCoord - v0.texCoord;
		glm::vec2 deltaUV2 = v2.texCoord - v0.texCoord;

		// Calculate the scaling factor for normalizing the vector
		float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);

		// Calculate the tangent
		glm::vec3 tangent = (edge1 * deltaUV2.y - edge2 * deltaUV1.y) * r;

		// Add the tangent to the 3 vertices
		v0.tangent += tangent;
		v1.tangent += tangent;
		v2.tangent += tangent;
	}

	// Normalize the tangents
	for (auto& vertex : vertices)
	{
		vertex.tangent = glm::normalize(vertex.tangent);
	}
}
