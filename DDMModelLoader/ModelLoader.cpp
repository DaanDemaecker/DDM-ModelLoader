// ModelLoader.cpp

// Header include
#include "ModelLoader.h"
#include "Mesh.h"

// Standard library includes
#include <stdexcept>
#include <algorithm>
#include <iostream>

DDMML::ModelLoader::ModelLoader()
{
	m_pImporter = std::make_unique<Assimp::Importer>();
}

DDMML::ModelLoader::~ModelLoader()
{
}

std::unique_ptr<DDMML::Mesh> DDMML::ModelLoader::LoadModel(const std::string& fileName, const std::string& name)
{
    std::vector<std::unique_ptr<DDMML::Mesh>> meshes{};

    LoadScene(fileName, meshes);

    return ConvertSceneToMesh(meshes, name);
}

void DDMML::ModelLoader::LoadScene(const std::string& fileName, std::vector<std::unique_ptr<Mesh>>& meshes)
{
    const aiScene* scene = m_pImporter->ReadFile(fileName,
        aiProcess_Triangulate |
        aiProcess_FlipUVs |
        aiProcess_GenNormals
    );

    if (scene == nullptr || scene->mRootNode == nullptr)
    {
        return;
    }

    auto directory = GetDirectory(fileName);

    ProcessNode(meshes, scene->mRootNode, scene, directory);
}

void DDMML::ModelLoader::ProcessNode(std::vector<std::unique_ptr<Mesh>>& meshes, aiNode* pNode, const aiScene* pScene, const std::string& directory)
{
    for (int i{}; i < pNode->mNumMeshes; ++i)
    {
        unsigned int index = pNode->mMeshes[i];

        if (index < pScene->mNumMeshes)
        {
            auto mesh = pScene->mMeshes[index];

            meshes.push_back(ProcessMesh(mesh, pScene, directory));
        }
    }


    for (int i{}; i < pNode->mNumChildren; ++i)
    {
        aiNode* newNode = pNode->mChildren[i];

        ProcessNode(meshes, newNode, pScene, directory);
    }
}

std::unique_ptr<DDMML::Mesh> DDMML::ModelLoader::ProcessMesh(aiMesh* mesh, const aiScene* pScene, const std::string& directory)
{
    const std::string name = mesh->mName.C_Str();

    std::unique_ptr<DDMML::Mesh> newMesh = std::make_unique<DDMML::Mesh>(name);

    ExtractVertices(newMesh.get(), mesh);


    auto& indices = newMesh->GetIndices();
    indices.reserve(indices.size() + mesh->mNumFaces * 3);
    
    ExtractIndices(indices, mesh);

    ExtractTextures(newMesh.get(), mesh, pScene, directory);
    
    return newMesh;
}

void DDMML::ModelLoader::ExtractVertices(Mesh* pNewMesh, aiMesh* pMesh)
{

    auto& vertices = pNewMesh->GetVertices();
    vertices.reserve(vertices.size() + pMesh->mNumVertices);

    for (int i{}; i < pMesh->mNumVertices; ++i)
    {
        auto newVertex = DDMML::Vertex{};

        // Position
        auto vertex = pMesh->mVertices[i];

        newVertex.pos.x = vertex.x;
        newVertex.pos.y = vertex.y;
        newVertex.pos.z = vertex.z;

        // Normal
        auto normal = pMesh->mNormals[i];

        newVertex.normal.x = normal.x;
        newVertex.normal.y = normal.y;
        newVertex.normal.z = normal.z;        

        // Color
        if (pMesh->HasVertexColors(0))
        {
            auto color = pMesh->mColors[0][i];

            newVertex.color.x = color.r;
            newVertex.color.y = color.g;
            newVertex.color.z = color.b;
            newVertex.color.w = color.a;

            if (color.a < 1)
            {
                pNewMesh->SetIsTransparent(true);
            }
        }

        // UVs
        if (pMesh->HasTextureCoords(0))
        {
            auto uvSet = pMesh->mTextureCoords[0][i];

            newVertex.texCoord.x = uvSet.x;
            newVertex.texCoord.y = uvSet.y;
        }

        vertices.push_back(newVertex);
    }
}

void DDMML::ModelLoader::ExtractIndices(std::vector<uint32_t>& indices, aiMesh* pMesh)
{
    for (int i{}; i < pMesh->mNumFaces; ++i)
    {
        auto face = pMesh->mFaces[i];

        for (int j{}; j < face.mNumIndices; ++j)
        {
            indices.push_back(face.mIndices[j]);
        }
    }
}

void DDMML::ModelLoader::ExtractTextures(Mesh* pNewMesh, aiMesh* pMesh, const aiScene* pScene, const std::string& directory)
{
    unsigned int materialIndex = pMesh->mMaterialIndex;

    if (materialIndex < 0)
    {
        return;
    }

    auto material = pScene->mMaterials[materialIndex];
    

    // Diffuse
    ExtractTextureType(pNewMesh->GetDiffuseTextureNames(), material, aiTextureType_BASE_COLOR, directory);


    // Normal
    ExtractTextureType(pNewMesh->GetNormalTextureNames(), material, aiTextureType_NORMALS, directory);
}

void DDMML::ModelLoader::ExtractTextureType(std::vector<std::string>& textureNames, aiMaterial* pMaterial, aiTextureType type, const std::string& directory)
{
    textureNames.reserve(pMaterial->GetTextureCount(type));

    for (int i{}; i < pMaterial->GetTextureCount(type); ++i)
    {
        aiString fileName{};

        pMaterial->GetTexture(type, i, &fileName);

        std::string fullPath = directory + fileName.C_Str();

        textureNames.push_back(fullPath);
    }
}

std::string DDMML::ModelLoader::GetDirectory(const std::string& path)
{
    int index = path.find_last_of("/");

    if (index < 0)
    {
        return "";
    }

    return path.substr(index + 1);
}

std::unique_ptr<DDMML::Mesh> DDMML::ModelLoader::ConvertSceneToMesh(std::vector<std::unique_ptr<Mesh>>& sceneMeshes, const std::string& name)
{
    std::unique_ptr<Mesh> newMesh = std::make_unique<Mesh>(name);

    auto& vertices = newMesh->GetVertices();
    auto& indices = newMesh->GetIndices();

    for (auto& currentMesh : sceneMeshes)
    {
        uint32_t vertexAmount = vertices.size();
        uint32_t indexAmount = indices.size();

        auto newVertices = currentMesh->GetVertices();
        auto newIndices = currentMesh->GetIndices();

        vertices.resize(newVertices.size() + vertexAmount);
        indices.resize(newIndices.size() + indexAmount);
        
        std::copy(newVertices.begin(), newVertices.end(), vertices.begin() + vertexAmount);

        std::transform(newIndices.begin(), newIndices.end(), newIndices.begin(),
            [vertexAmount](uint32_t index)
            {
                return index + vertexAmount;
            });


        std::copy(newIndices.begin(), newIndices.end(), indices.begin() + indexAmount);
    }


    return newMesh;
}


