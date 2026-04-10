// ModelLoader.cpp

// Header include
#include "ModelLoader.h"
#include "Mesh.h"

// Standard library includes
#include <stdexcept>

DDMML::ModelLoader::ModelLoader()
{
	m_pImporter = std::make_unique<Assimp::Importer>();
}

DDMML::ModelLoader::~ModelLoader()
{
}

void DDMML::ModelLoader::LoadScene(const std::string& fileName, std::vector<std::unique_ptr<Mesh>>& meshes)
{
   const aiScene* scene = m_pImporter->ReadFile(fileName,
       aiProcess_Triangulate |
       aiProcess_FlipUVs |
       aiProcess_CalcTangentSpace |
       aiProcess_GenNormals
   );

    if (scene == nullptr || scene->mRootNode == nullptr)
    {
        return;
    }

    ProcessNode(meshes, scene->mRootNode, scene, fileName);
}

void DDMML::ModelLoader::ProcessNode(std::vector<std::unique_ptr<Mesh>>& meshes, aiNode* pNode, const aiScene* pScene, const std::string& fileName)
{
    for (int i{}; i < pNode->mNumMeshes; ++i)
    {
        unsigned int index = pNode->mMeshes[i];

        if (index < pScene->mNumMeshes)
        {
            auto mesh = pScene->mMeshes[index];

            meshes.push_back(ProcessMesh(mesh));
        }
    }


    for (int i{}; i < pNode->mNumChildren; ++i)
    {
        aiNode* newNode = pNode->mChildren[i];

        ProcessNode(meshes, newNode, pScene, fileName);
    }
}

std::unique_ptr<DDMML::Mesh> DDMML::ModelLoader::ProcessMesh(aiMesh* mesh)
{
    const std::string name = mesh->mName.C_Str();

    std::unique_ptr<DDMML::Mesh> newMesh = std::make_unique<DDMML::Mesh>(name);

    ExtractVertices(newMesh.get(), mesh);


    auto& indices = newMesh->GetIndices();
    indices.reserve(indices.size() + mesh->mNumFaces);
    
    ExtractIndices(indices, mesh);
    
    return newMesh;
}

void DDMML::ModelLoader::ExtractVertices(Mesh* pNewMesh, aiMesh* mesh)
{

    auto& vertices = pNewMesh->GetVertices();
    vertices.reserve(vertices.size() + mesh->mNumVertices);

    for (int i{}; i < mesh->mNumVertices; ++i)
    {
        auto newVertex = DDMML::Vertex{};

        // Position
        auto vertex = mesh->mVertices[i];

        newVertex.pos.x = vertex.x;
        newVertex.pos.y = vertex.y;
        newVertex.pos.z = vertex.z;

        // Normal
        auto normal = mesh->mNormals[i];

        newVertex.normal.x = normal.x;
        newVertex.normal.y = normal.y;
        newVertex.normal.z = normal.z;

        // Tangent
        auto tangent = mesh->mTangents[i];
        newVertex.tangent.x = tangent.x;
        newVertex.tangent.y = tangent.y;
        newVertex.tangent.z = tangent.z;

        // Color
        if (mesh->HasVertexColors(0))
        {
            auto color = mesh->mColors[0][i];

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
        if (mesh->HasTextureCoords(0))
        {
            auto uvSet = mesh->mTextureCoords[0][i];

            newVertex.texCoord.x = uvSet.x;
            newVertex.texCoord.y = uvSet.y;
        }

        vertices.push_back(newVertex);
    }
}



void DDMML::ModelLoader::ExtractIndices(std::vector<uint32_t>& indices, aiMesh* mesh)
{
    for (int i{}; i < mesh->mNumFaces; ++i)
    {
        auto face = mesh->mFaces[i];

        for (int j{}; j < face.mNumIndices; ++j)
        {
            indices.push_back(face.mIndices[j]);
        }
    }
}


