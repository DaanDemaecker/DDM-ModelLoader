// ObjLoader.h

// This class will take care of loading .obj files

#ifndef _OBJ_LOADER_
#define _OBJ_LOADER_

// File includes
#include "Vertex.h"

// Standard library includes
#include <string>
#include <vector>

namespace DDM
{
	class ObjLoader final
	{
	public:
		ObjLoader();
		~ObjLoader();

		ObjLoader(ObjLoader& other) = delete;
		ObjLoader(ObjLoader&& other) = delete;

		ObjLoader& operator=(ObjLoader& other) = delete;
		ObjLoader& operator=(ObjLoader&& other) = delete;

		// Load in a .obj model given a file path
		// Parameters:
		//     - path: The path to the model file
		//     - vertices: The vector that will be used to store the vertices
		//     - indices: The vector that will be used to store the indices
		void LoadModel(const std::string& path, std::vector<Vertex>& vertices, std::vector<uint32_t>& indices);

	private:
		void SetupTangents(std::vector<Vertex>& vertices, std::vector<uint32_t>& indices);
	};
}


#endif // !_OBJ_LOADER_
