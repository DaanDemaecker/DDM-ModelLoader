// GltfLoader.cpp

// Header include
#include "GltfLoader.h"

// File includes
//#define TINYGLTF_NO_STB_IMAGE
//#define TINYGLTF_NO_STB_IMAGE_WRITE
#include "tiny_gltf.h"
#include "../Mesh.h"

// Standard library includes
#include <iostream>
#include <memory>

DDMML::GltfLoader::GltfLoader()
    :ModelLoader("gltf")
{
}

DDMML::GltfLoader::~GltfLoader()
{
}

void DDMML::GltfLoader::LoadModel(const std::string& fileName, Mesh* mesh)
{
    // Initialize necessary variables
    tinygltf::TinyGLTF loader{};
    tinygltf::Model gltfModel{};
    std::string error{};
    std::string warn{};

    // Load the model from the file
    bool result = loader.LoadASCIIFromFile(&gltfModel, &error, &warn, fileName);

    // If warning, throw
    if (!warn.empty())
    {
        throw std::runtime_error("Warning: " + warn);
    }

    // If error, throw
    if (!error.empty())
    {
        throw std::runtime_error("Error: " + error);
    }

    // If no result, throw
    if (!result)
    {
        throw std::runtime_error("Unable to load model");
    }

    // Get vertex and index list from mesh
    auto& vertices = mesh->GetVertices();
    auto& indices = mesh->GetIndices();

    // Loop trough gltfmodel meshes
    for (auto& currentMesh : gltfModel.meshes)
    {
        // Loop trough primitives in mesh
        for (auto& primitive : currentMesh.primitives)
        {
            // Extract vertices, indices and texture names
            ExtractVertices(gltfModel, primitive, vertices);
            ExtractIndices(gltfModel, primitive, indices);
            ExtractDiffuseTextures(gltfModel, primitive, GetPath(fileName), mesh);
        }
    }
}

void DDMML::GltfLoader::LoadScene(const std::string& fileName, std::vector<std::unique_ptr<Mesh>>& meshes)
{
    // Initialize necessary variables
    tinygltf::TinyGLTF loader{};
    tinygltf::Model gltfModel{};
    std::string error{};
    std::string warn{};

    // Load the model from the file
    bool result = loader.LoadASCIIFromFile(&gltfModel, &error, &warn, fileName);

    // If warning, throw
    if (!warn.empty())
    {
        throw std::runtime_error("Warning: " + warn);
    }

    // If error, throw
    if (!error.empty())
    {
        throw std::runtime_error("Error: " + error);
    }

    // If no result, throw
    if (!result)
    {
        throw std::runtime_error("Unable to load model");
    }


    // Calculate total amount of models to load and reserve in vector
    int modelAmount{};
    for (auto& mesh : gltfModel.meshes)
    {
        modelAmount += static_cast<int>(mesh.primitives.size());
    }
    meshes.reserve(modelAmount);

    // Loop trough all meshes in GLTF model
    for (auto& mesh : gltfModel.meshes)
    {
        // Loop trough primitives in mesh
        for (auto& primitive : mesh.primitives)
        {
            // Load single Primitive into DDMML Mesh
            std::unique_ptr<DDMML::Mesh> currentModel{ std::make_unique<DDMML::Mesh>() };
            LoadModel(gltfModel, primitive, fileName, currentModel.get());
        }
    }
}

void DDMML::GltfLoader::LoadModel(const tinygltf::Model& gltfModel, const tinygltf::Primitive& ptimitive, const std::string& fileName, DDMML::Mesh* mesh)
{
    // Get the vertices and indices attributes and extract them from the gltf model
    auto& vertices = mesh->GetVertices();
    auto& indices = mesh->GetIndices();

    ExtractVertices(gltfModel, ptimitive, vertices);
    ExtractIndices(gltfModel, ptimitive, indices);

    // Extract diffuse textures
    ExtractDiffuseTextures(gltfModel, ptimitive, GetPath(fileName), mesh);


}

void DDMML::GltfLoader::ExtractVertices(const tinygltf::Model& gltfModel, const tinygltf::Primitive& primitive, std::vector<Vertex>& vertices)
{
    // Find attributes in the primitive
    auto posIt = primitive.attributes.find("POSITION");
    auto normIt = primitive.attributes.find("NORMAL");
    auto colIt = primitive.attributes.find("COLOR_0");
    auto texIt = primitive.attributes.find("TEXCOORD_0");

    const float* posData = nullptr, * normData = nullptr, * texData = nullptr, * colData = nullptr;
    size_t vertexCount = 0;

    // Extract POSITION data
    if (posIt != primitive.attributes.end()) {
        const tinygltf::Accessor& accessor = gltfModel.accessors[posIt->second];
        const tinygltf::BufferView& bufferView = gltfModel.bufferViews[accessor.bufferView];
        const tinygltf::Buffer& buffer = gltfModel.buffers[bufferView.buffer];

        posData = reinterpret_cast<const float*>(&buffer.data[bufferView.byteOffset + accessor.byteOffset]);
        vertexCount = accessor.count;  // Vertex count
    }

    // Extract NORMAL data
    if (normIt != primitive.attributes.end()) {
        const tinygltf::Accessor& accessor = gltfModel.accessors[normIt->second];
        const tinygltf::BufferView& bufferView = gltfModel.bufferViews[accessor.bufferView];
        const tinygltf::Buffer& buffer = gltfModel.buffers[bufferView.buffer];

        normData = reinterpret_cast<const float*>(&buffer.data[bufferView.byteOffset + accessor.byteOffset]);
    }

    // Extract COLOR data
    if (colIt != primitive.attributes.end()) {
        const tinygltf::Accessor& accessor = gltfModel.accessors[colIt->second];
        const tinygltf::BufferView& bufferView = gltfModel.bufferViews[accessor.bufferView];
        const tinygltf::Buffer& buffer = gltfModel.buffers[bufferView.buffer];

        colData = reinterpret_cast<const float*>(&buffer.data[bufferView.byteOffset + accessor.byteOffset]);
    }

    // Extract TEXCOORD_0 data
    if (texIt != primitive.attributes.end()) {
        const tinygltf::Accessor& accessor = gltfModel.accessors[texIt->second];
        const tinygltf::BufferView& bufferView = gltfModel.bufferViews[accessor.bufferView];
        const tinygltf::Buffer& buffer = gltfModel.buffers[bufferView.buffer];

        texData = reinterpret_cast<const float*>(&buffer.data[bufferView.byteOffset + accessor.byteOffset]);
    }

    // Fill Vertex Data
    for (size_t i = 0; i < vertexCount; i++) {
        Vertex v = {};

        if (posData) v.pos = glm::vec3(posData[i * 3 + 0], posData[i * 3 + 1], posData[i * 3 + 2]);
        if (normData) v.normal = glm::vec3(normData[i * 3 + 0], normData[i * 3 + 1], normData[i * 3 + 2]);
        if (colData) v.color = glm::vec4(colData[i * 4 + 0], colData[i * 4 + 1], colData[i * 4 + 2], colData[i * 4 + 3]);
        if (texData) v.texCoord = glm::vec2(texData[i * 2 + 0], texData[i * 2 + 1]);

        vertices.push_back(v);
    }
}

void DDMML::GltfLoader::ExtractIndices(const tinygltf::Model& gltfModel, const tinygltf::Primitive& primitive, std::vector<uint32_t>& indices)
{
    if (primitive.indices < 0) return; // No indices

    const tinygltf::Accessor& accessor = gltfModel.accessors[primitive.indices];
    const tinygltf::BufferView& bufferView = gltfModel.bufferViews[accessor.bufferView];
    const tinygltf::Buffer& buffer = gltfModel.buffers[bufferView.buffer];

    const void* dataPtr = &buffer.data[bufferView.byteOffset + accessor.byteOffset];
    size_t count = accessor.count;

    if (accessor.componentType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT) {
        const uint16_t* data = static_cast<const uint16_t*>(dataPtr);
        for (size_t i = 0; i < count; i++) {
            indices.push_back(static_cast<uint32_t>(data[i]));  // Convert uint16_t to uint32_t
        }
    }
    else if (accessor.componentType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT) {
        const uint32_t* data = static_cast<const uint32_t*>(dataPtr);
        for (size_t i = 0; i < count; i++) {
            indices.push_back(data[i]);  // No conversion needed
        }
    }
    else if (accessor.componentType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE) {
        const uint8_t* data = static_cast<const uint8_t*>(dataPtr);
        for (size_t i = 0; i < count; i++) {
            indices.push_back(static_cast<uint32_t>(data[i]));  // Convert uint8_t to uint32_t
        }
    }
}

void DDMML::GltfLoader::ExtractDiffuseTextures(const tinygltf::Model& model, const tinygltf::Primitive& primitive, const std::string&& path, Mesh* mesh)
{
	auto& materialIndex = primitive.material;

	if (materialIndex < 0) return; // No material

	auto& mat = model.materials[materialIndex];

    int texIdx = mat.pbrMetallicRoughness.baseColorTexture.index;

	if (texIdx < 0) return; // No texture

	const tinygltf::Texture& text = model.textures[texIdx];
	const tinygltf::Image& img = model.images[text.source];	

	mesh->GetDiffuseTextureNames().push_back(path + img.uri);
}

std::string DDMML::GltfLoader::GetPath(const std::string& filename)
{
    auto index = filename.find_last_of("/");

    if (index <= filename.length() - 1)
        return "";

    return filename.substr(0, index + 1);
}
