#include "Scene.h"

#include "ObjectConst.h"
#include "Material_i.h"

#include "clfe/Allocation.h"

namespace clfe
{

	Scene::Scene(uint32_t targetSize) : objects(targetSize), materials(targetSize), textures(), variables()
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

	EMaterial* Scene::addMaterial(Material* material)
	{
		uint32_t textureCount = material->getTextureCount();
		uint32_t variableCount = material->getVariableCount();

		TextureBase** textures = new TextureBase*[textureCount];
		for (uint32_t i = 0; i < textureCount; i++)
		{
			// search for copies
			textures[i] = material->getTextures()[i]->copy(false);
			this->textures.push_back(textures[i]);
		}

		MVariableBase** variables = new MVariableBase*[variableCount];
		for (uint32_t i = 0; i < variableCount; i++)
		{
			// search for copies
			variables[i] = material->getVariables()[i]->copy(false);
			this->variables.push_back(variables[i]);
		}

		EMaterial* em = new EMaterial(textureCount, textures, variableCount, variables);
		materials.push_back(em);
		return em;
	}

	EObject* Scene::addObject(Model* obj, Vector<3, float> pos, Quaternion rot, ObjectType type, bool active)
	{
		uint32_t meshCount = obj->getMeshCount();
		EMesh** meshes = new EMesh*[meshCount];//(EMesh**)malloc(meshCount * sizeof(EMesh*));
		for (uint32_t i = 0; i < meshCount; i++)
		{
			uint32_t vertexCount = obj->getVertexCount(i);
			VectorList<Vector<3, float>> verticesList = obj->getVertices(i);
			Vector<3, float>* vertices = new Vector<3, float>[vertexCount];
			for (uint32_t j = 0; j < vertexCount; j++)
			{
				vertices[j] = verticesList.at(j);
			}

			Vector<2, float>** uvs = new Vector<2, float>*[UVChannelCount];
			for (uint32_t j = 0; j < UVChannelCount; j++)
			{
				uvs[j] = new Vector<2, float>[vertexCount];
				VectorList<Vector<2, float>> uvsList = obj->getUVs(i, j);
				for (uint32_t k = 0; k < vertexCount; k++)
				{
					uvs[j][k] = uvsList.at(k);
				}
			}

			uint32_t indexCount = obj->getIndexCount(i);
			VectorList<uint32_t> indicesList = obj->getIndices(i);
			uint32_t* indices = new uint32_t[vertexCount];
			for (uint32_t j = 0; j < indexCount; j++)
			{
				indices[j] = indicesList.at(j);
			}

			meshes[i] = new EMesh(addMaterial(obj->getMaterial(i)), vertexCount, indexCount, vertices, uvs, indices);
		}

		objects.push_back(new EObject(meshCount, meshes, type, active, pos, rot));

		return nullptr;
	}

	void Scene::update()
	{
		// thing
		// do later
	}

	void Scene::clear()
	{
		/*
		for (uint32_t i = 0; i < objects.size(); i++)
		{
			EObject* obj = objects.at(i);
		}
		*/
		for (auto it = materials.begin(); it != materials.end();) {
			if ((*it)->getReferences() <= 0)
			{
				delete &(*it);
				it = materials.erase(it);
			}
			else
			{
				it++;
			}
		}
		for (auto it = textures.begin(); it != textures.end();) {
			if ((*it)->references() <= 0)
			{
				delete &(*it);
				it = textures.erase(it);
			}
			else
			{
				it++;
			}
		}
		for (auto it = variables.begin(); it != variables.end();) {
			if ((*it)->references() <= 0)
			{
				delete& (*it);
				it = variables.erase(it);
			}
			else
			{
				it++;
			}
		}
	}

}