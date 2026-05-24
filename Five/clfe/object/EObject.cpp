#include "EObject.h"

namespace clfe
{

	// ObjectData

	EObjectData::EObjectData() : vCount(0), iCount(0), vertices(), uvs{}, indices()
	{}

	void EObjectData::addIndex(uint32_t index)
	{
		iCount++;
		indices.push_back(index);
	}

	void EObjectData::removeVertex(uint32_t i)
	{
		vCount--;
		vertices.erase(vertices.begin() + i);
		for (uint8_t j = 0; j < UVChannelCount; j++)
		{
			uvs[j].erase(uvs[j].begin() + i);
		}
	}

	void EObjectData::removeIndex(uint32_t i)
	{
		iCount--;
		indices.erase(indices.begin() + i);
	}

	// Object
	/*
	EObject::EObject(const EObjectData& data, ObjectType type, bool active) : EObject(data, Vector<3, float>(), type, active)
	{}
	*/

	template <typename T>
	T* toCArr(uint32_t size, VectorList<T> list)
	{
		T* arr = (T*)malloc(size * sizeof(T));
		for (uint32_t i = 0; i < size; i++)
		{
			arr[i] = list.at(i);
		}
		return arr;
	}
	/*
	EObject::EObject(const EObjectData& data, Vector<3, float> pos, ObjectType type, bool active) : Object(active), type(type), pos(pos), update(true), uvs{ nullptr }
	{
		vCount = data.getVertexCount();
		iCount = data.getIndexCount();

		const VectorList<Vector<3, float>> verticesList = data.getVertices();
		const VectorList<Vector<2, float>>* uvsList = data.getUVs();
		const VectorList<uint32_t> indicesList = data.getIndices();

		vertices = toCArr(vCount, verticesList);
		for (uint8_t i = 0; i < UVChannelCount; i++)
		{
			uvs[i] = toCArr(vCount, uvsList[i]);
		}
		indices = toCArr(iCount, indicesList);
	}
	*/

}