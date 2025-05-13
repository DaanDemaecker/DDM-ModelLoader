// FbxLoader.h
// This class will handle the loading of fbx files

#ifndef FbxLoaderIncluded
#define FbxLoaderIncluded

// Parent include
#include "ModelLoader.h"

// File includes
#include "fbxsdk.h"

// Standard library includes
#include <vector>
#include <unordered_map>
#include <memory>

namespace DDMML
{
	class Mesh;
	struct Vertex;

	class FbxLoader final : public ModelLoader
	{
	public:
		FbxLoader();

		~FbxLoader();

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
	private:

		FbxManager* m_pFbxManager{};

		struct fbxTexturedInfo
		{
			bool textured{ false };
			int uvIndex{};
			FbxStringList uvSets{};
			int uvSetsCount{};
		};

		void ConvertMesh(FbxMesh* pMesh,
			std::unordered_map<DDMML::Vertex, uint32_t>& uniqueVertices, std::vector<DDMML::Vertex>& vertices,
			std::vector<uint32_t>& indices, int& baseUvIndex);

		void ConvertMesh(FbxMesh* pMesh, const std::string& path, Mesh* meshes, int& baseUvIndex);

		void HandleFbxVertex(FbxMesh* pMesh, FbxVector4* controlPoints, int polygonIndex, int inPolygonPosition,
			std::unordered_map<DDMML::Vertex, uint32_t>& uniqueVerticesint,
			fbxTexturedInfo& textureInfo,
			std::vector<DDMML::Vertex>& vertices, std::vector<uint32_t>& indices);

		FbxScene* LoadScene(const std::string& path);

		void HandleChild(FbxNode* child, const std::string& path, std::vector<std::unique_ptr<DDMML::Mesh>>& meshes);

		std::string ExtractDiffuseTexture(FbxMesh* fbxMesh);
	};
}


#endif // !FbxLoaderIncluded
