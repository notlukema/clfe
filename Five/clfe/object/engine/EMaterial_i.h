#ifndef CLFE_MATERIAL_ENGINE_I_H
#define CLFE_MATERIAL_ENGINE_I_H

#include "../TextureImpl.h"
#include "../MVariable.h"

#include <cstdint>

namespace clfe
{
	
	class Scene;

	class EMaterial
	{
	private:
		uint32_t texCount;
		TextureBase** textures;

		uint32_t varCount;
		MVariableBase** variables;

		uint32_t references;

		bool update_;

		void clearData();

		friend class Scene;
		EMaterial(uint32_t texCount, TextureBase** textures, uint32_t varCount, MVariableBase** variables);
		~EMaterial();

		inline void requireUpdate()
		{
			update_ = true;
		}

	public:
		void update(uint32_t texCount, TextureBase** textures, uint32_t varCount, MVariableBase** variables);

		inline uint32_t getReferences() const
		{
			return references;
		}

		// Use these to prevent EMaterial from being automatically cleaned out by the corresponding Scene
		void addReference();
		void removeReference();

		inline bool needUpdate() const
		{
			return update_;
		}

		inline void clearUpdate()
		{
			update_ = false;
		}

		inline uint32_t getTextureCount()
		{
			return texCount;
		}

		inline TextureBase** getTextures()
		{
			return textures;
		}

		inline uint32_t getVariableCount()
		{
			return varCount;
		}

		inline MVariableBase** getVariables()
		{
			return variables;
		}

	};

}

#endif