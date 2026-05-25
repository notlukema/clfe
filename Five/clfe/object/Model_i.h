#ifndef CLFE_MODEL_I_H
#define CLFE_MODEL_I_H

#include "Mesh.h"
#include "Material_i.h"

#include "clm/VectorImpl.h"

#include "TypeTraits.h"
#include "VectorList.h"

namespace clfe
{

	class Model
	{
	protected:
		struct SubMesh
		{
		private:
			uint32_t vCount;
			uint32_t iCount;

			VectorList<Vector<3, float>> vertices_;
			VectorList<Vector<2, float>> uvs_[UVChannelCount];
			VectorList<uint32_t> indices_;

			Material* material_;

		public:
			SubMesh(Material* material, uint32_t targetSize = 10);
			~SubMesh();

			template <typename... Args>
			void addVertex(Vector<3, float> vertex, Args... args) requires (sizeof...(Args) <= UVChannelCount) && (sizeof...(Args) >= 1) && (IsSame<Args, Vector<2, float>> && ...)
			{
				vCount++;
				vertices_.push_back(vertex);

				uint8_t i = 0;
				((uvs_[i++].push_back(args)), ...);
				while (i < UVChannelCount)
				{
					uvs_[i].push_back(Vector<2, float>());
					i++;
				}
			}

			void addVertex(Vector<3, float> vertex, Vector<2, float>* uvs, uint8_t uvCount);
			void addIndex(uint32_t index);

			void addTri(uint32_t index1, uint32_t index2, uint32_t index3);

			void removeVertex(uint32_t i);
			void removeIndex(uint32_t i);

			uint32_t vertexCount() const
			{
				return vCount;
			}

			uint32_t indexCount() const
			{
				return iCount;
			}

			inline const VectorList<Vector<3, float>>& vertices() const
			{
				return vertices_;
			}

			inline const VectorList<Vector<2, float>>& uv(uint32_t i) const
			{
				return uvs_[i];
			}

			inline const VectorList<uint32_t>& indices() const
			{
				return indices_;
			}

			inline Material* material() const
			{
				return material_;
			}

		};

	private:
		uint32_t meshCount;
		VectorList<SubMesh> meshes;

	public:
		Model(Material* material);
		~Model();

		void newMesh(Material* material);
		void removeMesh(uint32_t mesh);

		uint32_t getTotalVertexCount() const;
		uint32_t getTotalIndexCount() const;

		inline uint32_t getVertexCount() const
		{
			return meshes[meshCount - 1].vertexCount();
		}

		inline uint32_t getIndexCount() const
		{
			return meshes[meshCount - 1].indexCount();
		}

		inline uint32_t getVertexCount(uint32_t mesh) const
		{
			return meshes[mesh].vertexCount();
		}

		inline uint32_t getIndexCount(uint32_t mesh) const
		{
			return meshes[mesh].indexCount();
		}

		inline uint32_t getMeshCount()
		{
			return meshCount;
		}

		inline const SubMesh& getMesh(uint32_t mesh)
		{
			return meshes[mesh];
		}

		template <typename... Args>
		inline void addVertex(Vector<3, float> vertex, Args... args) requires (sizeof...(Args) <= UVChannelCount) && (sizeof...(Args) >= 1) && (IsSame<Args, Vector<2, float>> && ...)
		{
			meshes[meshCount - 1].addVertex(vertex, args...);
		}

		inline void addVertex(Vector<3, float> vertex, Vector<2, float>* uvs, uint8_t uvCount)
		{
			meshes[meshCount - 1].addVertex(vertex, uvs, uvCount);
		}

		inline void addVertex(uint32_t mesh, Vector<3, float> vertex, Vector<2, float>* uvs, uint8_t uvCount)
		{
			meshes[mesh].addVertex(vertex, uvs, uvCount);
		}

		inline void addIndex(uint32_t index)
		{
			meshes[meshCount - 1].addIndex(index);
		}

		inline void addIndex(uint32_t mesh, uint32_t index)
		{
			meshes[mesh].addIndex(index);
		}

		inline void addTri(uint32_t index1, uint32_t index2, uint32_t index3)
		{
			meshes[meshCount - 1].addTri(index1, index2, index3);
		}

		inline void addTri(uint32_t mesh, uint32_t index1, uint32_t index2, uint32_t index3)
		{
			meshes[mesh].addTri(index1, index2, index3);
		}

		inline void removeVertex(uint32_t i)
		{
			meshes[meshCount - 1].removeVertex(i);
		}

		inline void removeVertex(uint32_t mesh, uint32_t i)
		{
			meshes[mesh].removeVertex(i);
		}

		inline void removeIndex(uint32_t i)
		{
			meshes[meshCount - 1].removeIndex(i);
		}

		inline void removeIndex(uint32_t mesh, uint32_t i)
		{
			meshes[mesh].removeIndex(i);
		}

	};

}

#endif