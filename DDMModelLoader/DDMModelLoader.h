// DDMModelLoader.h

// This class will be the main object that will allow the user to load in models

#ifndef DDMModelLoaderIncluded
#define DDMModelLoaderIncluded

// File includes
#include "glm/glm.hpp"
#include "Vertex.h"

// Standard library includes
#include <string>
#include <vector>
#include <memory>

namespace DDM
{
	class ObjLoader;
	class FbxLoader;

	class ModelLoader final
	{
	public:
		// Default constructor
		ModelLoader();
		
		// Destructor
		~ModelLoader();

		// Delete copy- and move operations
		ModelLoader(ModelLoader& other) = delete;
		ModelLoader(ModelLoader&& other) = delete;

		ModelLoader& operator=(ModelLoader& other) = delete;
		ModelLoader& operator=(ModelLoader&& other) = delete;

		// Load in a 3D model given a file path
		// Parameters:
		//     - path: The path to the model file
		//     - vertices: The vector that will be used to store the vertices
		//     - indices: The vector that will be used to store the indices
		void LoadModel(const std::string& path, std::vector<Vertex>& vertices, std::vector<uint32_t>& indices);


	private:
		std::unique_ptr<ObjLoader> m_pObjLoader{};
		std::unique_ptr<FbxLoader> m_pFbxLoader{};

		std::string GetExtension(const std::string& filename);

		void SetupTangents(std::vector<Vertex>& vertices, std::vector<uint32_t>& indices);
	};
}


#endif // !DDMModelLoaderIncluded
