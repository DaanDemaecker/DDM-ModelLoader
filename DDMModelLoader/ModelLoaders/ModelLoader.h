// ModelLoader.h

// This will serve as the base class of all other modelloaders

#ifndef _MODEL_LOADER_
#define _MODEL_LOADER_

// Standard library includes
#include <string>
#include <memory>
#include <vector>

namespace DDMML
{
	class Mesh;

	class ModelLoader
	{
	public:
		// Delete default constructor
		ModelLoader() = delete;

		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="extension: ">Extension of file this loader will handle</param>
		ModelLoader(const std::string& extension);

		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="extension: ">Extension of file this loader will handle</param>
		ModelLoader(const std::string&& extension);

		// Default destructor
		virtual ~ModelLoader() = default;

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
		const std::string m_Extension;

	};


}

#endif // !_MODEL_LOADER_
