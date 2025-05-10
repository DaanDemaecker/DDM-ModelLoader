// ObjLoader.cpp

// Header include
#include "ObjLoader.h"

// File includes
#include "tiny_obj_loader.h"
#include "glm/glm.hpp"
#include "../Mesh.h"

// Standard library includes
#include <stdexcept>
#include <unordered_map>

DDMML::ObjLoader::ObjLoader()
	:ModelLoader("obj")
{
}

DDMML::ObjLoader::~ObjLoader()
{
}

void DDMML::ObjLoader::LoadModel(const std::string& fileName, Mesh* mesh)
{
	// Create needed objects to read in .obj file
	tinyobj::attrib_t attrib{};
	std::vector<tinyobj::shape_t> shapes{};
	std::vector<tinyobj::material_t> materials{};

	auto& vertices = mesh->GetVertices();
	auto& indices = mesh->GetIndices();

	// Create objects for error throwing
	std::string err;

	// Read file, returned false, throw error
	if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &err, fileName.c_str()))
	{
		throw err;
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
}