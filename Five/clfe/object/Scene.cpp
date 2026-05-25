#include "Scene.h"

namespace clfe
{

	Scene::Scene(uint32_t targetSize) : objects(targetSize)
	{}

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

	EObject* Scene::createObject(Model* obj, Vector<3, float> pos, Quaternion rot)
	{
		return nullptr;
	}

}