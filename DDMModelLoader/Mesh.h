// Mesh.h

// This class will represent a single mesh
// It will hold the vertices and indices of the mesh
// It will also hold texture information

#ifndef _MESH_
#define _MESH_

// File includes
#include "Vertex.h"

// Standard library includes
#include <vector>
#include <string>

namespace DDMML
{
	class Mesh
	{
	public:
		// Default constructor and destructor
		Mesh() = default;
		~Mesh() = default;

		// Delete copy operations
		Mesh(const Mesh&) = delete;
		Mesh& operator=(const Mesh&) = delete;


		// Default move operations
		Mesh(Mesh&&) = default;
		Mesh& operator=(Mesh&&) = default;

		/// <summary>
		/// Get a reference to the vertices vector
		/// </summary>
		/// <returns>Reference to vertices vector</returns>
		std::vector<Vertex>& GetVertices()
		{
			return m_Vertices;
		}

		/// <summary>
		/// Get a reference to the indices vector
		/// </summary>
		/// <returns>Reference to indices vector</returns>
		std::vector<uint32_t>& GetIndices()
		{
			return m_Indices;
		}

		/// <summary>
		/// Get a reference to the diffuse texture vector
		/// </summary>
		/// <returns>Reference to diffuse texture vector</returns>
		std::vector<std::string>& GetDiffuseTextureNames()
		{
			return m_DifuseTextureNames;
		}

		/// <summary>
		/// Get a reference to the PBR texture vector
		/// </summary>
		/// <returns>Reference to PBR texture vector</returns>
		std::vector<std::string>& GetPBRTextureNames()
		{
			return m_PBRTextureNames;
		}

		/// <summary>
		/// Get a reference to the normal texture vector
		/// </summary>
		/// <returns>Reference to normal texture vector</returns>
		std::vector<std::string>& GetNormalTextureNames()
		{
			return m_NormalTextureNames;
		}

	private:
		// The vertices and of the mesh
		std::vector<Vertex> m_Vertices{};
		std::vector<uint32_t> m_Indices{};

		// The texture names of the mesh
		std::vector<std::string> m_DifuseTextureNames{};
		std::vector<std::string> m_PBRTextureNames{};
		std::vector<std::string> m_NormalTextureNames{};

	};
}

#endif // !_MESH_
