// ObjLoader.cpp

// Header include
#include "ObjLoader.h"

// File includes
#include "tiny_obj_loader.h"
#include "glm/glm.hpp"

// Standard library includes
#include <stdexcept>
#include <unordered_map>

DDM::ObjLoader::ObjLoader()
{
}

DDM::ObjLoader::~ObjLoader()
{
}

void DDM::ObjLoader::LoadModel(const std::string& path, std::vector<Vertex>& vertices, std::vector<uint32_t>& indices)
{
	// Create needed objects to read in .obj file
	tinyobj::attrib_t attrib{};
	std::vector<tinyobj::shape_t> shapes{};
	std::vector<tinyobj::material_t> materials{};

	// Create objects for error throwing
	std::string err;

	// Read file, returned false, throw error
	if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &err, path.c_str()))
	{
		throw std::runtime_error(path + " is not a valid file path");
	}

	// Create map to store vertices
	std::unordered_map<Vertex, uint32_t> uniqueVertices{};

	// Loop through every shape that was read from the file
	for (const auto& shape : shapes)
	{
		// Loop through all indices in current shape
		for (const auto& index : shape.mesh.indices)
		{
			// Create empty vertex
			Vertex vertex{};

			// Add position to vertex
			vertex.pos = {
				attrib.vertices[3 * index.vertex_index],
				attrib.vertices[3 * index.vertex_index + 1],
				attrib.vertices[3 * index.vertex_index + 2]
			};

			if (index.texcoord_index >= 0 && static_cast<size_t>(index.texcoord_index * 2 + 1) < attrib.texcoords.size())
			{
				// Add UV coords to vertex
				vertex.texCoord = {
					attrib.texcoords[2 * index.texcoord_index],
					1.0f - attrib.texcoords[2 * index.texcoord_index + 1]
				};
			}

			if (index.normal_index >= 0 && static_cast<size_t>(index.normal_index * 3 + 2) < attrib.normals.size())
			{
				// Add normal to vertex
				vertex.normal = {
					attrib.normals[3 * index.normal_index],
					attrib.normals[3 * index.normal_index + 1],
					attrib.normals[3 * index.normal_index + 2]
				};
			}
			else
			{
				// Default normal if not provided
				vertex.normal = { 0.0f, 0.0f, 0.0f };
			}

			// Add color to vertex
			vertex.color = { 1.0f, 1.0f, 1.0f };

			// If vertex isn't in uniqueVertices vector, add it
			if (uniqueVertices.count(vertex) == 0)
			{
				uniqueVertices[vertex] = static_cast<uint32_t>(vertices.size());
				vertices.push_back(vertex);
			}

			// Add index to indices vector
			indices.push_back(uniqueVertices[vertex]);
		}
	}

	SetupTangents(vertices, indices);
}

void DDM::ObjLoader::SetupTangents(std::vector<Vertex>& vertices, std::vector<uint32_t>& indices)
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
