// DDMModelLoader.h

// This class will be the main object that will allow the user to load in models

#ifndef DDMModelLoaderIncluded
#define DDMModelLoaderIncluded

// File includes
#include "glm/glm.hpp"
#include "Vertex.h"
#include "Mesh.h"

// Standard library includes
#include <string>
#include <vector>
#include <memory>
#include <map>

namespace DDMML
{
	class ObjLoader;
	class FbxLoader;
	class GltfLoader;
	class ModelLoader;

	class DDMModelLoader final
	{
	public:
		// Default constructor
		DDMModelLoader();
		
		// Destructor
		~DDMModelLoader();

		// Delete copy- and move operations
		DDMModelLoader(DDMModelLoader& other) = delete;
		DDMModelLoader(DDMModelLoader&& other) = delete;

		DDMModelLoader& operator=(DDMModelLoader& other) = delete;
		DDMModelLoader& operator=(DDMModelLoader&& other) = delete;

		/// <summary>
		/// Loads in a model given a file path
		/// <params>
		///	- filename: The name of the scene file
		/// - mesh: A pointer to a mesh struct, this mesh will be filled with the vertices and indices for a single model
		/// </summary>
		virtual void LoadModel(const std::string& fileName, Mesh* mesh);

		/// <summary>
		/// Loads in a scene given a file path
		/// <params>
		///	- filename: The name of the scene file
		/// - meshes: A vector of meshes, each mesh will be filled with the vertices and indices for a single model
		/// </summary>
		virtual void LoadScene(const std::string& fileName, std::vector<std::unique_ptr<Mesh>>& meshes);



		// Load in a 3D model given a file path
		// Parameters:
		//     - path: The path to the model file
		//     - vertices: The vector that will be used to store the vertices
		//     - indices: The vector that will be used to store the indices
		void LoadModel(const std::string& path, std::vector<Vertex>& vertices, std::vector<uint32_t>& indices);

		// Load in a 3D scene given a file path
		// Parameters:
		//		- path: The path to the scene file
		//		- verticesLists: A list of vectors of vertices, each vector will be filled with the vertices for a single model
		//		- indicesLists: A list of vectors of indicees, each vector will be filled with the indices for a single model
		void LoadScene(const std::string& path, std::vector<std::vector<Vertex>>& verticesLists, std::vector<std::vector<uint32_t>>& indicesLists);

		/// <summary>
		/// Loads in a scene given a file path
		/// <params>
		///	- path: The path to the scene file
		/// - meshes: A vector of meshes, each mesh will be filled with the vertices and indices for a single model
		/// </summary>
		void LoadScene(const std::string& path, std::vector<Mesh>& meshes);

	private:
		std::unique_ptr<FbxLoader> m_pFbxLoader{};
		std::unique_ptr<GltfLoader> m_pGltfLoader{};
		std::map<std::string, std::unique_ptr<ModelLoader>> m_ModelLoaders{};

		std::string GetExtension(const std::string& filename);

		std::string GetPath(const std::string& filename);

		void SetupTangents(std::vector<Vertex>& vertices, std::vector<uint32_t>& indices);
	};
}


#endif // !DDMModelLoaderIncluded
