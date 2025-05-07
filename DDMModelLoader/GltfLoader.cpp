// GltfLoader.cpp

// Header include
#include "GltfLoader.h"

// File includes
//#define TINYGLTF_NO_STB_IMAGE
//#define TINYGLTF_NO_STB_IMAGE_WRITE
#include "tiny_gltf.h"
#include "Mesh.h"

// Standard library includes
#include <iostream>

DDMML::GltfLoader::GltfLoader()
{
}

DDMML::GltfLoader::~GltfLoader()
{
}

void DDMML::GltfLoader::LoadModel(const std::string& path, std::vector<Vertex>& vertices, std::vector<uint32_t>& indices)
{
	tinygltf::TinyGLTF loader;
	std::string error;
	std::string warn;
	tinygltf::Model model;

	bool result = loader.LoadASCIIFromFile(&model, &error, &warn, path);

	if (!warn.empty())
	{
        std::cout << "Warning: " << warn << std::endl;
	}

	if (!error.empty())
	{
        std::cout << "Error: " << error << std::endl;
	}

	if (!result)
	{
		throw("Unable to load model");
	}


	for (auto& mesh : model.meshes)
	{
		for (auto& primitive : mesh.primitives)
		{
			ExtractVertices(model, primitive, vertices);
			ExtractIndices(model, primitive, indices);
		}

	}
}

void DDMML::GltfLoader::LoadScene(const std::string& path, std::vector<std::vector<Vertex>>& verticesLists, std::vector<std::vector<uint32_t>>& indicesLists)
{
    tinygltf::TinyGLTF loader;
    std::string error;
    std::string warn;
    tinygltf::Model model;

    bool result = loader.LoadASCIIFromFile(&model, &error, &warn, path);

    if (!warn.empty())
    {
        std::cout << "Warning: " << warn << std::endl;
    }

    if (!error.empty())
    {
        std::cout << "Error: " << error << std::endl;
    }

    if (!result)
    {
        throw("Unable to load model");
    }

    int modelAmount{};

    for (auto& mesh : model.meshes)
    {
        modelAmount += static_cast<int>(mesh.primitives.size());
    }

    verticesLists.resize(modelAmount);
    indicesLists.resize(modelAmount);

    int currentModel{};

    for (auto& mesh : model.meshes)
    {
        for (auto& primitive : mesh.primitives)
        {
            ExtractVertices(model, primitive, verticesLists[currentModel]);
            ExtractIndices(model, primitive, indicesLists[currentModel]);
            ++currentModel;
        }
    }
}

void DDMML::GltfLoader::LoadScene(const std::string& path, std::vector<Mesh>& meshes)
{
    tinygltf::TinyGLTF loader;
    std::string error;
    std::string warn;
    tinygltf::Model model;

    bool result = loader.LoadASCIIFromFile(&model, &error, &warn, path);

    if (!warn.empty())
    {
        std::cout << "Warning: " << warn << std::endl;
    }

    if (!error.empty())
    {
        std::cout << "Error: " << error << std::endl;
    }

    if (!result)
    {
        throw("Unable to load model");
    }

    int modelAmount{};

    for (auto& mesh : model.meshes)
    {
        modelAmount += static_cast<int>(mesh.primitives.size());
    }

    
    meshes.resize(modelAmount);

    int currentModel{};

    for (auto& mesh : model.meshes)
    {
        for (auto& primitive : mesh.primitives)
        {
            LoadModel(model, primitive, meshes[currentModel]);
            ++currentModel;
        }
    }
}

void DDMML::GltfLoader::ExtractVertices(const tinygltf::Model& model, const tinygltf::Primitive& primitive, std::vector<Vertex>& vertices)
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
        const tinygltf::Accessor& accessor = model.accessors[posIt->second];
        const tinygltf::BufferView& bufferView = model.bufferViews[accessor.bufferView];
        const tinygltf::Buffer& buffer = model.buffers[bufferView.buffer];

        posData = reinterpret_cast<const float*>(&buffer.data[bufferView.byteOffset + accessor.byteOffset]);
        vertexCount = accessor.count;  // Vertex count
    }

    // Extract NORMAL data
    if (normIt != primitive.attributes.end()) {
        const tinygltf::Accessor& accessor = model.accessors[normIt->second];
        const tinygltf::BufferView& bufferView = model.bufferViews[accessor.bufferView];
        const tinygltf::Buffer& buffer = model.buffers[bufferView.buffer];

        normData = reinterpret_cast<const float*>(&buffer.data[bufferView.byteOffset + accessor.byteOffset]);
    }

    // Extract COLOR data
    if (colIt != primitive.attributes.end()) {
        const tinygltf::Accessor& accessor = model.accessors[colIt->second];
        const tinygltf::BufferView& bufferView = model.bufferViews[accessor.bufferView];
        const tinygltf::Buffer& buffer = model.buffers[bufferView.buffer];

        colData = reinterpret_cast<const float*>(&buffer.data[bufferView.byteOffset + accessor.byteOffset]);
    }

    // Extract TEXCOORD_0 data
    if (texIt != primitive.attributes.end()) {
        const tinygltf::Accessor& accessor = model.accessors[texIt->second];
        const tinygltf::BufferView& bufferView = model.bufferViews[accessor.bufferView];
        const tinygltf::Buffer& buffer = model.buffers[bufferView.buffer];

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

void DDMML::GltfLoader::ExtractIndices(const tinygltf::Model& model, const tinygltf::Primitive& primitive, std::vector<uint32_t>& indices)
{
    if (primitive.indices < 0) return; // No indices

    const tinygltf::Accessor& accessor = model.accessors[primitive.indices];
    const tinygltf::BufferView& bufferView = model.bufferViews[accessor.bufferView];
    const tinygltf::Buffer& buffer = model.buffers[bufferView.buffer];

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

void DDMML::GltfLoader::LoadModel(const tinygltf::Model& model, const tinygltf::Primitive& ptimitive, DDMML::Mesh& mesh)
{
    // Get the vertices and indices attributes and extract them from the gltf model
	auto& vertices = mesh.GetVertices();
	auto& indices = mesh.GetIndices();

	ExtractVertices(model, ptimitive, vertices);
	ExtractIndices(model, ptimitive, indices);

	// Extract diffuse textures
	ExtractDiffuseTextures(model, ptimitive, mesh);


}

void DDMML::GltfLoader::ExtractDiffuseTextures(const tinygltf::Model& model, const tinygltf::Primitive& primitive, Mesh& mesh)
{
	auto& materialIndex = primitive.material;

	if (materialIndex < 0) return; // No material

	auto& mat = model.materials[materialIndex];

    int texIdx = mat.pbrMetallicRoughness.baseColorTexture.index;

	if (texIdx < 0) return; // No texture

	const tinygltf::Texture& text = model.textures[texIdx];
	const tinygltf::Image& img = model.images[text.source];	

	mesh.GetDiffuseTextureNames().push_back(img.uri);
}
