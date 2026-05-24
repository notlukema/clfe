#ifndef CLFE_OBJECT_I_H
#define CLFE_OBJECT_I_H

#include "Material.h"

#include "clm/VectorImpl.h"
#include "clm/Quaternion.h"

#include <cstdint>

namespace clfe
{

	inline constexpr uint8_t UVChannelCount = 8;

	// Object

	class Object
	{
	protected:
		bool active;

		Vector<3, float> pos;
		Quaternion rot;

		uint32_t vCount;
		uint32_t iCount;

		Vector<3, float>* vertices;
		Vector<2, float>* uvs[UVChannelCount];
		uint32_t* indices;

		//Material material;

		Object(uint32_t vertexCount, uint32_t indexCount, Vector<3, float>* vertices, Vector<2, float>** uvs, uint32_t* indices, Vector<3, float> pos = Vector<3, float>(), Quaternion rot = Quaternion(), bool active = true);

	public:
		~Object();

		inline bool isActive() const
		{
			return active;
		}

		inline void deactivate()
		{
			active = false;
		}

		inline void activate()
		{
			active = true;
		}

		inline void setActive(bool active)
		{
			this->active = active;
		}

		inline uint32_t getVertexCount() const
		{
			return vCount;
		}

		inline uint32_t getIndexCount() const
		{
			return iCount;
		}

		inline const Vector<3, float>* getVertices() const
		{
			return vertices;
		}

		inline const Vector<2, float>* getUV(uint8_t i) const
		{
			return uvs[i];
		}

		inline const uint32_t* getIndices() const
		{
			return indices;
		}

	};

}

#endif