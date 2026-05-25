#include "Model_i.h"

namespace clfe
{

	// Submesh

	Model::SubMesh::SubMesh(Material* material, uint32_t targetSize) : material_(material), vCount(0), iCount(0), vertices_(targetSize), uvs_{ VectorList<Vector<2, float>>(targetSize) }, indices_(targetSize)
	{}

	Model::SubMesh::~SubMesh()
	{
		// don't delete material yet
	}

	void Model::SubMesh::addVertex(Vector<3, float> vertex, Vector<2, float>* uvs, uint8_t uvCount)
	{
		vCount++;
		vertices_.push_back(vertex);

		uint8_t i = 0;
		while (i < uvCount)
		{
			uvs_[i].push_back(uvs[i]);
			i++;
		}
		while (i < UVChannelCount)
		{
			uvs_[i].push_back(Vector<2, float>());
			i++;
		}
	}

	void Model::SubMesh::addIndex(uint32_t index)
	{
		iCount++;
		indices_.push_back(index);
	}

	void Model::SubMesh::addTri(uint32_t index1, uint32_t index2, uint32_t index3)
	{
		iCount += 3;
		indices_.push_back(index1);
		indices_.push_back(index2);
		indices_.push_back(index3);
	}

	void Model::SubMesh::removeVertex(uint32_t i)
	{
		if (i < 0 && i >= vCount)
		{
			return;
		}

		vCount--;
		vertices_.erase(vertices_.begin() + i);
		for (uint8_t j = 0; j < UVChannelCount; j++)
		{
			uvs_[j].erase(uvs_[j].begin() + i);
		}
	}

	void Model::SubMesh::removeIndex(uint32_t i)
	{
		if (i < 0 && i >= iCount)
		{
			return;
		}

		iCount--;
		indices_.erase(indices_.begin() + i);
	}
	
	// Model

	Model::Model(Material* material) : meshCount(0), meshes()
	{
		newMesh(material);
	}

	Model::~Model()
	{
		// something here?
	}

	void Model::newMesh(Material* material)
	{
		meshCount++;
		meshes.push_back(SubMesh(material));
	}

	void Model::removeMesh(uint32_t mesh)
	{
		if (mesh < 0 && mesh >= meshCount)
		{
			return;
		}

		meshCount--;
		meshes.erase(meshes.begin() + mesh);
	}

	uint32_t Model::getTotalVertexCount() const
	{
		uint32_t count = 0;
		for (uint32_t i = 0; i < meshCount; i++)
		{
			count += meshes[i].vertexCount();
		}
		return count;
	}

	uint32_t Model::getTotalIndexCount() const
	{
		uint32_t count = 0;
		for (uint32_t i = 0; i < meshCount; i++)
		{
			count += meshes[i].indexCount();
		}
		return count;
	}

}