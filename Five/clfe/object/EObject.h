#ifndef CLFE_OBJECT_ENGINE_H
#define CLFE_OBJECT_ENGINE_H

#include "Object_i.h"
#include "clfe/Allocation.h"

#include "clm/VectorImpl.h"

#include "TypeTraits.h"
#include "VectorList.h"

namespace clfe
{

	// Object types

	enum class ObjectType
	{

		Static = 1,
		Dynamic = 2

	};

	// Object data medium

	struct EObjectData
	{
	private:
		uint32_t vCount;
		uint32_t iCount;

		VectorList<Vector<3, float>> vertices;
		VectorList<Vector<2, float>> uvs[UVChannelCount];
		VectorList<uint32_t> indices;

	public:
		EObjectData();

		inline uint32_t getVertexCount() const
		{
			return vCount;
		}

		inline uint32_t getIndexCount() const
		{
			return iCount;
		}

		inline const VectorList<Vector<3, float>> getVertices() const
		{
			return vertices;
		}

		inline const VectorList<Vector<2, float>>* getUVs() const
		{
			return uvs;
		}

		inline const VectorList<uint32_t> getIndices() const
		{
			return indices;
		}

		template <typename... Args>
		void addVertex(Vector<3, float> vertex, Args... args) requires (sizeof...(Args) <= UVChannelCount) && (sizeof...(Args) >= 1) && (IsSame<Args, Vector<2, float>> && ...)
		{
			vCount++;
			vertices.push_back(vertex);

			uint8_t i = 0;
			((uvs[i++].push_back(args)), ...);
			while (i < UVChannelCount)
			{
				uvs[i].push_back(Vector<2, float>());
				i++;
			}
		}

		void addIndex(uint32_t index);

		void removeVertex(uint32_t i);
		void removeIndex(uint32_t i);

	};

	// Object

	class EObject : public Object
	{
	private:
		const ObjectType type;

		bool update;

	public:


		inline ObjectType getType() const
		{
			return type;
		}

	public:
		// operator overloads for new and delete or smth
		// discourage using new and delete for objects since it allocates on random memory

	};

}

#endif