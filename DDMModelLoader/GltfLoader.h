// GltfLoader.h

// This clad will be used to load in .gltf files

#ifndef _GLTF_LOADER_
#define _GLTF_LOADER_

// File includes
#include "Vertex.h"

// Standard library includes
#include <string>
#include <vector>

namespace tinygltf
{
	class Model;
	class Primitive;
}

namespace DDM
{
	class GltfLoader final
	{
	public:
		GltfLoader();
		~GltfLoader();

		GltfLoader(GltfLoader& other) = delete;
		GltfLoader(GltfLoader&& other) = delete;

		GltfLoader& operator=(GltfLoader& other) = delete;
		GltfLoader& operator=(GltfLoader&& other) = delete;

		// Load in a .gltf model given a file path
		// Parameters:
		//     - path: The path to the model file
		//     - vertices: The vector that will be used to store the vertices
		//     - indices: The vector that will be used to store the indices
		void LoadModel(const std::string& path, std::vector<Vertex>& vertices, std::vector<uint32_t>& indices);

	public:
		void ExtractVertices(const tinygltf::Model& model, const tinygltf::Primitive& primitive, std::vector<Vertex>& vertices);


		void ExtractIndices(const tinygltf::Model& model, const tinygltf::Primitive& primitive, std::vector<uint32_t>& indices);
	};
}


#endif // !_GLTF_LOADER_