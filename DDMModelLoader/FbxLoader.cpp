// FbxLoader.cpp

// File includes
#include "FbxLoader.h"
#include "Mesh.h"

// Standard library includes
#include <iostream>

DDMML::FbxLoader::FbxLoader()
{
	// Initialize the FBX SDK
	m_pFbxManager = FbxManager::Create();
	auto ios = FbxIOSettings::Create(m_pFbxManager, IOSROOT);
	m_pFbxManager->SetIOSettings(ios);
}

DDMML::FbxLoader::~FbxLoader()
{
	m_pFbxManager->Destroy();
}

void DDMML::FbxLoader::LoadModel(const std::string& path, std::vector<DDMML::Vertex>& vertices, std::vector<uint32_t>& indices)
{
	FbxScene* scene = LoadScene(path);

	if (!scene)
	{
		throw std::runtime_error(path + " is not a valid file path");
	}


	int baseUvIndex{};


	// Create map to store vertices
	std::unordered_map<DDMML::Vertex, uint32_t> uniqueVertices{};

	// Traverse the scene to find nodes containing the car model
	FbxNode* root = scene->GetRootNode();
	if (root)
	{
		for (int i = 0; i < root->GetChildCount(); i++)
		{
			FbxNode* child = root->GetChild(i);
			// Check if the node contains mesh data
			if (child->GetNodeAttribute() && child->GetNodeAttribute()->GetAttributeType() == FbxNodeAttribute::eMesh)
			{
				// Extract mesh data
				FbxMesh* mesh = child->GetMesh();

				ConvertMesh(mesh, uniqueVertices, vertices, indices, baseUvIndex);
			}
		}
	}

	// Destroy the scene and manager
	scene->Destroy();
}

void DDMML::FbxLoader::LoadScene(const std::string& fileName, const std::string& path, std::vector<DDMML::Mesh>& meshes)
{
	FbxScene* scene = LoadScene(fileName);

	if (!scene)
	{
		throw std::runtime_error(fileName + " is not a valid file path");
	}	


	int baseUvIndex{};

	// Traverse the scene to find nodes containing the car model
	FbxNode* root = scene->GetRootNode();
	if (root)
	{
		meshes.reserve(root->GetChildCount());

		for (int i = 0; i < root->GetChildCount(); i++)
		{
			FbxNode* child = root->GetChild(i);
			
			HandleChild(child, path, meshes);
		}
	}

	// Destroy the scene and manager
	scene->Destroy();
}

void DDMML::FbxLoader::ConvertMesh(FbxMesh* pMesh,
	std::unordered_map<DDMML::Vertex, uint32_t>& uniqueVertices, std::vector<DDMML::Vertex>& vertices,
	std::vector<uint32_t>& indices, int& baseUvIndex)
{
	int numPolygons = pMesh->GetPolygonCount();

	if (numPolygons == 0)return;

	FbxVector4* controlPoints = pMesh->GetControlPoints();
	pMesh->GenerateNormals();
	pMesh->GenerateTangentsData();

	fbxSkinnedInfo skinnedInfo{};
	skinnedInfo.isSkinned = static_cast<bool>(pMesh->GetDeformerCount());

	if (skinnedInfo.isSkinned)
	{
		skinnedInfo.pSkin = static_cast<FbxSkin*>(pMesh->GetDeformer(0, FbxDeformer::eSkin));
		SetupSkin(skinnedInfo, pMesh->GetControlPointsCount());
	}

	int nextBaseUvIndex{ baseUvIndex };

	fbxTexturedInfo texturedInfo{};
	texturedInfo.textured = static_cast<bool>(pMesh->GetElementMaterialCount());
	pMesh->GetUVSetNames(texturedInfo.uvSets);
	texturedInfo.uvSetsCount = texturedInfo.uvSets.GetCount();

	for (int polygonIndex = 0; polygonIndex < numPolygons; ++polygonIndex)
	{
		auto polygonSize = pMesh->GetPolygonSize(polygonIndex);

		for (int i = 1; i <= polygonSize - 2; i++)
		{
			if (texturedInfo.textured)
			{
				texturedInfo.uvIndex = pMesh->GetElementMaterial()->GetIndexArray().GetAt(polygonIndex) + baseUvIndex;
			}

			if (texturedInfo.uvIndex >= nextBaseUvIndex)
			{
				nextBaseUvIndex = texturedInfo.uvIndex + 1;
			}

			HandleFbxVertex(pMesh, controlPoints, polygonIndex, 0, uniqueVertices, texturedInfo, skinnedInfo, vertices, indices);
			HandleFbxVertex(pMesh, controlPoints, polygonIndex, i, uniqueVertices, texturedInfo, skinnedInfo, vertices, indices);
			HandleFbxVertex(pMesh, controlPoints, polygonIndex, i + 1, uniqueVertices, texturedInfo, skinnedInfo, vertices, indices);
		}
	}

	baseUvIndex = nextBaseUvIndex;
}

void DDMML::FbxLoader::ConvertMesh(FbxMesh* pFbxMesh, const std::string& path, Mesh& mesh, int& baseUvIndex)
{
	int numPolygons = pFbxMesh->GetPolygonCount();

	if (numPolygons == 0)return;

	FbxVector4* controlPoints = pFbxMesh->GetControlPoints();
	pFbxMesh->GenerateNormals();
	pFbxMesh->GenerateTangentsData();

	fbxSkinnedInfo skinnedInfo{};
	skinnedInfo.isSkinned = static_cast<bool>(pFbxMesh->GetDeformerCount());

	if (skinnedInfo.isSkinned)
	{
		skinnedInfo.pSkin = static_cast<FbxSkin*>(pFbxMesh->GetDeformer(0, FbxDeformer::eSkin));
		SetupSkin(skinnedInfo, pFbxMesh->GetControlPointsCount());
	}


	int nextBaseUvIndex{ baseUvIndex };

	fbxTexturedInfo texturedInfo{};
	texturedInfo.textured = static_cast<bool>(pFbxMesh->GetElementMaterialCount());
	pFbxMesh->GetUVSetNames(texturedInfo.uvSets);
	texturedInfo.uvSetsCount = texturedInfo.uvSets.GetCount();

	auto texture = pFbxMesh->GetElementMaterial()->eTextureDiffuse;
	

	// Create map to store vertices
	std::unordered_map<DDMML::Vertex, uint32_t> uniqueVertices{};

	for (int polygonIndex = 0; polygonIndex < numPolygons; ++polygonIndex)
	{
		auto polygonSize = pFbxMesh->GetPolygonSize(polygonIndex);

		for (int i = 1; i <= polygonSize - 2; i++)
		{
			if (texturedInfo.textured)
			{
				texturedInfo.uvIndex = pFbxMesh->GetElementMaterial()->GetIndexArray().GetAt(polygonIndex) + baseUvIndex;
			}

			if (texturedInfo.uvIndex >= nextBaseUvIndex)
			{
				nextBaseUvIndex = texturedInfo.uvIndex + 1;
			}

			HandleFbxVertex(pFbxMesh, controlPoints, polygonIndex, 0, uniqueVertices, texturedInfo, skinnedInfo, mesh.GetVertices(), mesh.GetIndices());
			HandleFbxVertex(pFbxMesh, controlPoints, polygonIndex, i, uniqueVertices, texturedInfo, skinnedInfo, mesh.GetVertices(), mesh.GetIndices());
			HandleFbxVertex(pFbxMesh, controlPoints, polygonIndex, i + 1, uniqueVertices, texturedInfo, skinnedInfo, mesh.GetVertices(), mesh.GetIndices());
		}
	}

	mesh.GetDiffuseTextureNames().push_back(ExtractDiffuseTexture(pFbxMesh));
}

void DDMML::FbxLoader::HandleFbxVertex(FbxMesh* pMesh, FbxVector4* controlPoints, int polygonIndex, int inPolygonPosition,
	std::unordered_map<DDMML::Vertex, uint32_t>& uniqueVertices,
	fbxTexturedInfo& textureInfo, fbxSkinnedInfo& skinnedInfo,
	std::vector<DDMML::Vertex>& vertices, std::vector<uint32_t>& indices)
{
	int vertexIndex = pMesh->GetPolygonVertex(polygonIndex, inPolygonPosition);

	auto controlPoint = controlPoints[vertexIndex];

	FbxVector4 normal{};
	FbxVector4 tangent{};

	pMesh->GetPolygonVertexNormal(polygonIndex, inPolygonPosition, normal);

	DDMML::Vertex vertex{};

	if (textureInfo.textured)
	{
		FbxVector2 uv{};
		bool unmapped{};
		for (int i{}; i < textureInfo.uvSetsCount; i++)
		{
			if (pMesh->GetPolygonVertexUV(polygonIndex, inPolygonPosition, textureInfo.uvSets[i], uv, unmapped))
			{
				vertex.texCoord = glm::vec2{ uv[0], 1 - uv[1] };
				//vertex.uvSetIndex = static_cast<float>(textureInfo.uvIndex);
			}
		}
	}

	/*if (skinnedInfo.isSkinned)
	{
		vertex.boneIndices = skinnedInfo.boneInfos[vertexIndex].boneIndices;
		vertex.boneWeights = skinnedInfo.boneInfos[vertexIndex].boneWeights;
	}*/


	vertex.pos = glm::vec3{ controlPoint[0], controlPoint[1], controlPoint[2] };
	vertex.normal = glm::vec3{ normal[0], normal[1], normal[2] };
	vertex.color = glm::vec3{ 1, 1, 1 };

	// If vertex isn't in uniqueVertices vector, add it
	if (!uniqueVertices.contains(vertex))
	{
		uniqueVertices[vertex] = static_cast<uint32_t>(vertices.size());
		vertices.push_back(vertex);
	}

	// Add index to indices vector
	indices.push_back(uniqueVertices[vertex]);
}


void DDMML::FbxLoader::SetupSkin(fbxSkinnedInfo& skinnedInfo, int controlPointAmount)
{
	skinnedInfo.boneInfos.resize(controlPointAmount);


	for (int boneIndex{}; boneIndex < skinnedInfo.pSkin->GetClusterCount(); boneIndex++)
	{
		auto cluster = skinnedInfo.pSkin->GetCluster(boneIndex);

		for (int j{}; j < cluster->GetControlPointIndicesCount(); j++)
		{
			int controlPointIndex = cluster->GetControlPointIndices()[j];
			float boneWeight = static_cast<float>(cluster->GetControlPointWeights()[j]);

			skinnedInfo.boneInfos[controlPointIndex].AddBone(static_cast<float>(boneIndex), boneWeight);
		}
	}
}

FbxScene* DDMML::FbxLoader::LoadScene(const std::string& path)
{
	auto pFbxImporter = FbxImporter::Create(m_pFbxManager, "importer");
	// Import the FBX file
	const char* filename = path.c_str();
	if (!pFbxImporter->Initialize(filename, -1, m_pFbxManager->GetIOSettings())) {
		throw std::runtime_error(path + " is not a valid file path");
	}

	// Create a scene and import it
	FbxScene* scene = FbxScene::Create(m_pFbxManager, "Scene");
	pFbxImporter->Import(scene);

	pFbxImporter->Destroy();

	return scene;
}

void DDMML::FbxLoader::HandleChild(FbxNode* child, const std::string& path, std::vector<DDMML::Mesh>& meshes)
{
	for (int i{}; i < child->GetChildCount(); ++i)
	{
		HandleChild(child->GetChild(i), path, meshes);
	}

	int baseUvIndex{};

	// Check if the node contains mesh data
	if (child->GetNodeAttribute() && child->GetNodeAttribute()->GetAttributeType() == FbxNodeAttribute::eMesh)
	{
		// Extract mesh data
		FbxMesh* mesh = child->GetMesh();

		DDMML::Mesh currentMesh{};

		ConvertMesh(mesh, path, currentMesh, baseUvIndex);

		meshes.emplace_back(std::move(currentMesh));
	}
}

std::string DDMML::FbxLoader::ExtractDiffuseTexture(FbxMesh* pFbxMesh)
{
	int materialIndex = pFbxMesh->GetElementMaterial()->GetIndexArray().GetAt(0); // or polygonIndex
	FbxNode* node = pFbxMesh->GetNode();

	if (node && materialIndex < node->GetMaterialCount()) {
		FbxSurfaceMaterial* material = node->GetMaterial(materialIndex);
		if (material) {
			FbxProperty diffuseProperty = material->FindProperty(FbxSurfaceMaterial::sDiffuse);
			if (diffuseProperty.IsValid()) {
				int textureCount = diffuseProperty.GetSrcObjectCount<FbxFileTexture>();
				for (int i = 0; i < textureCount; ++i) {
					FbxFileTexture* texture = diffuseProperty.GetSrcObject<FbxFileTexture>(i);
					if (texture) {
						const char* fileName = texture->GetFileName(); // Full path
						const char* relativeName = texture->GetRelativeFileName(); // Relative path
						std::cout << "Diffuse Texture File: " << relativeName << std::endl;

						return relativeName;
					}
				}
			}
		}
	}

	return "";
}

