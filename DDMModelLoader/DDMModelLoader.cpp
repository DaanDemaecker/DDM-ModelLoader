// DDMModelLoader.cpp

// Header include
#include "DDMModelLoader.h"

// File includes
#include "ModelLoader.h"

// Standard library includes
#include <iostream>
#include <cctype>
#include <algorithm>


DDMML::DDMModelLoader::DDMModelLoader()
{
	m_pModelLoader = std::make_unique<ModelLoader>();
}


DDMML::DDMModelLoader::~DDMModelLoader()
{

}

void DDMML::DDMModelLoader::LoadScene(const std::string& fileName, std::vector<std::unique_ptr<Mesh>>& meshes)
{
	m_pModelLoader->LoadScene(fileName, meshes);

	for (auto& mesh : meshes)
	{
		SetupTangents(mesh->GetVertices(), mesh->GetIndices());
	}
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
