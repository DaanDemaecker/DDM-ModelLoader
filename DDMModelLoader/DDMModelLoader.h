// DDMModelLoader.h

// This class will be the main object that will allow the user to load in models

#ifndef DDMModelLoaderIncluded
#define DDMModelLoaderIncluded

// File includes
#include "glm/glm.hpp"
#include "Vertex.h"
#include "Mesh.h"
#include "Export.h"

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

	class DDMML_API DDMModelLoader final
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

	private:
		std::map<std::string, std::unique_ptr<ModelLoader>> m_ModelLoaders{};

		/// <summary>
		/// Gets the extension from a given filepath
		/// </summary>
		/// <param name="filename"></param>
		/// <returns></returns>
		std::string GetExtension(const std::string& filename);

		void SetupTangents(std::vector<Vertex>& vertices, std::vector<uint32_t>& indices);
	};
}


#endif // !DDMModelLoaderIncluded
