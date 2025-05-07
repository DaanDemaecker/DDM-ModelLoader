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
	struct Primitive;
}

namespace DDMML
{
	class Mesh;

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

		// Load in a .gltf scene given a file path
		// Parameters:
		//		- path: The path to the scene file
		//		- verticesLists: A list of vectors of vertices, each vector will be filled with the vertices for a single model
		//		- indicesLists: A list of vectors of indicees, each vector will be filled with the indices for a single model
		void LoadScene(const std::string& path, std::vector<std::vector<Vertex>>& verticesLists, std::vector<std::vector<uint32_t>>& indicesLists);

		/// <summary>
		/// Loads in a scene given a file path
		/// <params>
		///	- filename: The name of the scene file
		/// -path: The path to the folder holding the scene file
		/// - meshes: A vector of meshes, each mesh will be filled with the vertices and indices for a single model
		/// </summary>
		void LoadScene(const std::string& fileName, const std::string& path, std::vector<Mesh>& meshes);

	public:
		void ExtractVertices(const tinygltf::Model& model, const tinygltf::Primitive& primitive, std::vector<Vertex>& vertices);


		void ExtractIndices(const tinygltf::Model& model, const tinygltf::Primitive& primitive, std::vector<uint32_t>& indices);
	
		void LoadModel(const tinygltf::Model& model, const tinygltf::Primitive& ptimitive, const std::string& path, Mesh& mesh);

		void ExtractDiffuseTextures(const tinygltf::Model& model, const tinygltf::Primitive& primitive, const std::string& path, Mesh& mesh);
	};
}


#endif // !_GLTF_LOADER_