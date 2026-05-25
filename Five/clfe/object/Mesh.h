#ifndef CLFE_MESH_H
#define CLFE_MESH_H

#include "Material_i.h"

#include "clm/VectorImpl.h"

#include <cstdint>

namespace clfe
{

	inline constexpr uint8_t UVChannelCount = 8;

	class Scene;
	class Model;

	class Mesh
	{
	private:
		uint32_t vCount;
		uint32_t iCount;

		Vector<3, float>* vertices_;
		Vector<2, float>* uvs_[UVChannelCount];
		uint32_t* indices_;

		Material* material_;

		friend class Scene;
		friend class Model;
		Mesh(Material* material, uint32_t vertexCount, uint32_t indexCount, Vector<3, float>* vertices, Vector<2, float>** uvs, uint32_t* indices);

	public:
		~Mesh();

		inline uint32_t vertexCount() const
		{
			return vCount;
		}

		inline uint32_t indexCount() const
		{
			return iCount;
		}

		inline const Vector<3, float>* vertices() const
		{
			return vertices_;
		}

		inline const Vector<2, float>* uv(uint8_t i) const
		{
			return uvs_[i];
		}

		inline const uint32_t* indices() const
		{
			return indices_;
		}

	};

}

#endif