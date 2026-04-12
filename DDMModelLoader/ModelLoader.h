// ModelLoader.h

// This will serve the core object that handles and loads the models

#ifndef _MODEL_LOADER_
#define _MODEL_LOADER_

// File includes
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Vertex.h"

// Standard library includes
#include <string>
#include <memory>
#include <vector>

namespace DDMML
{
	class Mesh;

	class ModelLoader final
	{
	public:
		// Default constructor
		ModelLoader();

		// Delete copy and move operations
		ModelLoader(ModelLoader&) = delete;
		ModelLoader(ModelLoader&&) = delete;

		ModelLoader& operator=(ModelLoader&) = delete;
		ModelLoader& operator=(ModelLoader&&) = delete;

		// Destructor
		~ModelLoader();

		/// <summary>
		/// Load in an entire 3D file into one mesh
		/// </summary>
		/// <param name="fileName: ">path to the file of the 3D model</param>
		/// <param name="name: ">name to give to the object</param>
		/// <returns>Unique pointer to the created mesh</returns>
		std::unique_ptr<Mesh> LoadModel(const std::string& fileName, const std::string& name);

		/// <summary>
		/// Loads in a scene given a file path
		/// </summary>
		/// <param name="fileName: ">path to the file</param>
		/// <param name="meshes: ">A vector of meshes, each mesh will be filled with the vertices and indices for a single model</param>
		void LoadScene(const std::string& fileName, std::vector<std::unique_ptr<Mesh>>& meshes);

	private:
		std::unique_ptr<Assimp::Importer> m_pImporter{};

		/// <summary>
		/// Process a single node of an assimp scene
		/// </summary>
		/// <param name="meshes: ">list of meshes to append to</param>
		/// <param name="pNode: ">node to process</param>
		/// <param name="pScene: ">scene that the node belons to</param>
		/// <param name="fileName: ">filename of the scene</param>
		void ProcessNode(std::vector<std::unique_ptr<Mesh>>& meshes, aiNode* pNode, const aiScene* pScene, const std::string& fileName);

		/// <summary>
		/// Process an assimp mesh and convert it to a DDMML mesh
		/// </summary>
		/// <param name="mesh: ">input mesh</param>
		/// <param name="pScene: ">pointer to the overall scene</param>
		/// <returns>unique pointer to output mesh</returns>
		std::unique_ptr<Mesh> ProcessMesh(aiMesh* mesh, const aiScene* pScene);

		/// <summary>
		/// Extract all vertices and add them to the list
		/// </summary>
		/// <param name="pNewMesh: ">pointer to the mesh being created</param>
		/// <param name="mesh: ">mesh to extract from</param>
		void ExtractVertices(Mesh* pNewMesh, aiMesh* pMesh);

		/// <summary>
		/// Extract all indices and add them to the list
		/// </summary>
		/// <param name="indices: ">list of indices to append to</param>
		/// <param name="mesh: ">mesh to extract from</param>
		void ExtractIndices(std::vector<uint32_t>& indices, aiMesh* pMesh);

		/// <summary>
		/// Extract the textures fom the aiMesh to the newly created mesh
		/// </summary>
		/// <param name="pNewMesh: ">pointer to the mesh being created</param>
		/// <param name="mesh: ">mesh to extract from</param>
		/// <param name="pScene: ">pointer to the overall scene</param>
		void ExtractTextures(Mesh* pNewMesh, aiMesh* pMesh, const aiScene* pScene);
		
		/// <summary>
		/// Convert a list of meshes into a single mesh
		/// </summary>
		/// <param name="sceneMeshes: ">list of meshes to convert</param>
		/// <param name="name: ">name to give to the object</param>
		/// <returns>Combined mesh</returns>
		std::unique_ptr<Mesh> ConvertSceneToMesh(std::vector<std::unique_ptr<Mesh>>& sceneMeshes, const std::string& name);
	};


}

#endif // !_MODEL_LOADER_
