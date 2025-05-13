// GltfLoader.h

// This clad will be used to load in .gltf files

#ifndef _GLTF_LOADER_
#define _GLTF_LOADER_

// Parent include
#include "ModelLoader.h"

// File includes
#include "../Vertex.h"

// Standard library includes
#include <string>
#include <vector>

namespace tinygltf
{
	class Model;
	struct Primitive;
	struct Mesh;
}

namespace DDMML
{
	class Mesh;

	class GltfLoader final : public ModelLoader
	{
	public:
		// Default constructor
		GltfLoader();

		// Destructor
		~GltfLoader();

		// Delete copy and move operations
		GltfLoader(GltfLoader& other) = delete;
		GltfLoader(GltfLoader&& other) = delete;

		GltfLoader& operator=(GltfLoader& other) = delete;
		GltfLoader& operator=(GltfLoader&& other) = delete;

		/// <summary>
		/// Loads in a model given a file path
		/// <params>
		///	- filename: The name of the scene file
		/// - mesh: A pointer to a mesh struct, this mesh will be filled with the vertices and indices for a single model
		/// </summary>
		virtual void LoadModel(const std::string& fileName, Mesh* mesh) override;


		/// <summary>
		/// Loads in a scene given a file path
		/// <params>
		///	- filename: The name of the scene file
		/// - meshes: A vector of meshes, each mesh will be filled with the vertices and indices for a single model
		/// </summary>
		virtual void LoadScene(const std::string& fileName, std::vector<std::unique_ptr<Mesh>>& meshes) override;
	public:
		/// <summary>
		/// Load a single GLTF model into a DDMML Mesh
		/// </summary>
		/// <param name="model: ">The GLTF model to extract from</param>
		/// <param name="primitive: ">The primitive within the GLTF model to extract from</param>
		/// <param name="fileName: ">The filepath to the main scene/model</param>
		/// <param name="mesh: ">The DDMML mesh to load the model into</param>
		void LoadModel(const tinygltf::Model& model, const tinygltf::Mesh& tinyGltfMesh, const tinygltf::Primitive& ptimitive, const std::string& fileName, Mesh* mesh);

		/// <summary>
		/// Extract the vertices from the GLTF model
		/// </summary>
		/// <param name="model: ">The GLTF model to extract from</param>
		/// <param name="primitive: ">The primitive within the GLTF model to extract from</param>
		/// <param name="mesh: ">The DDMML mesh to load the model into</param>
		void ExtractVertices(const tinygltf::Model& model, const tinygltf::Primitive& primitive, std::vector<Vertex>& vertices);

		/// <summary>
		/// Extract the indices from the GLTF model
		/// </summary>
		/// <param name="model: ">The GLTF model to extract from</param>
		/// <param name="primitive: ">The primitive within the GLTF model to extract from</param>
		/// <param name="mesh: ">The DDMML mesh to load the model into</param>
		void ExtractIndices(const tinygltf::Model& model, const tinygltf::Primitive& primitive, std::vector<uint32_t>& indices);
	
		/// <summary>
		/// Extract the diffuse texture names from the GLTF model
		/// </summary>
		/// <param name="model: ">The GLTF model to extract from</param>
		/// <param name="primitive: ">The primitive within the GLTF model to extract from</param>
		/// <param name="fileName: ">The filepath to the main scene/model</param>
		/// <param name="mesh: ">The DDMML mesh to load the model into</param>
		void ExtractDiffuseTextures(const tinygltf::Model& model, const tinygltf::Primitive& primitive, const std::string&& path, Mesh* mesh);

		/// <summary>
		/// Extract the normal texture names from the GLTF model
		/// </summary>
		/// <param name="model: ">The GLTF model to extract from</param>
		/// <param name="primitive: ">The primitive within the GLTF model to extract from</param>
		/// <param name="fileName: ">The filepath to the main scene/model</param>
		/// <param name="mesh: ">The DDMML mesh to load the model into</param>
		void ExtractNormalTextures(const tinygltf::Model& model, const tinygltf::Primitive& primitive, const std::string&& path, Mesh* mesh);

		/// <summary>
		/// Extract the name from the GLTF model
		/// </summary>
		/// <param name="model: ">The GLTF model to extract from</param>
		/// <param name="primitive: ">The primitive within the GLTF model to extract from</param>
		/// <param name="mesh: ">The DDMML mesh to load the model into</param>
		void ExtractName(const tinygltf::Model& model, const tinygltf::Mesh& tinyGltfMesh, const tinygltf::Primitive& primitive,  Mesh* mesh);

		/// <summary>
		/// Get the relative path to the folder holding the scene/model
		/// </summary>
		/// <param name="filename: ">full path to the scene/model</param>
		/// <returns></returns>
		std::string GetPath(const std::string& filename);
	};
}


#endif // !_GLTF_LOADER_