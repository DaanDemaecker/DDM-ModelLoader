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
		// Delete default constructor
		Mesh() = delete;


		Mesh(const std::string& name)
			:m_Name{name}
		{

		}

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

		/// <summary>
		/// Get the name of the mesh
		/// </summary>
		/// <returns>Name</returns>
		const std::string& GetName() const { return m_Name; }

		/// <summary>
		/// Set a new value for IsTransparant
		/// </summary>
		/// <param name="isTransparant: ">new value</param>
		void SetIsTransparent(bool isTransparant) { m_IsTransparant = isTransparant; }

		/// <summary>
		/// Query wether the material uses transparancy
		/// </summary>
		/// <returns>Does model use transparancy</returns>
		bool GetIsTransparant() const { return m_IsTransparant; }

	private:
		// The name of the object
		const std::string m_Name;

		// List of vertices
		std::vector<Vertex> m_Vertices{};

		// List of indices
		std::vector<uint32_t> m_Indices{};

		// Extra

		// List of diffuse textures
		std::vector<std::string> m_DifuseTextureNames{};

		// List of pbr textures
		std::vector<std::string> m_PBRTextureNames{};

		// List of normal textures
		std::vector<std::string> m_NormalTextureNames{};

		// Indicates if mesh uses transparency
		bool m_IsTransparant{};
	};
}

#endif // !_MESH_
