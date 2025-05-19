#ifndef _VERTEX_
#define _VERTEX_

#include "Includes/GLMIncludes.h"

#include <functional>
#include <optional>
#include <array>
#include <string>

namespace DDMML
{
	struct Vertex
	{
		glm::vec3 pos;
		glm::vec3 color{1, 1, 1};
		glm::vec2 texCoord;
		glm::vec3 normal;
		glm::vec3 tangent;

		// Function for == operator
			// Parameter:
			//     other: Vertex to be compared to
		bool operator==(const Vertex& other) const
		{
			// Compare every attribute seperately
			return pos == other.pos && color == other.color && texCoord == other.texCoord && tangent == other.tangent && normal == other.normal;
		}
	};
}

namespace std
{
	template<> struct hash<DDMML::Vertex>
	{
		size_t operator()(const DDMML::Vertex& vertex) const
		{
			size_t seed = 0;
			seed ^= hash<glm::vec3>()(vertex.pos) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
			seed ^= hash<glm::vec3>()(vertex.color) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
			seed ^= hash<glm::vec2>()(vertex.texCoord) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
			seed ^= hash<glm::vec3>()(vertex.normal) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
			seed ^= hash<glm::vec3>()(vertex.tangent) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
			return seed;
		}
	};
}

#endif // !_VERTEX_