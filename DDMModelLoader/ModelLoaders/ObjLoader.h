// ObjLoader.h

// This class will take care of loading .obj files

#ifndef _OBJ_LOADER_
#define _OBJ_LOADER_

// Parent include
#include "ModelLoader.h"


// Standard library includes
#include <string>
#include <vector>

namespace DDMML
{
	class Mesh;

	class ObjLoader final : public ModelLoader
	{
	public:
		ObjLoader();
		~ObjLoader();

		ObjLoader(ObjLoader& other) = delete;
		ObjLoader(ObjLoader&& other) = delete;

		ObjLoader& operator=(ObjLoader& other) = delete;
		ObjLoader& operator=(ObjLoader&& other) = delete;

		/// <summary>
		/// Loads in a model given a file path
		/// <params>
		///	- filename: The name of the scene file
		/// - mesh: A pointer to a mesh struct, this mesh will be filled with the vertices and indices for a single model
		/// </summary>
		virtual void LoadModel(const std::string& fileName, Mesh* mesh) override;
	};
}


#endif // !_OBJ_LOADER_
