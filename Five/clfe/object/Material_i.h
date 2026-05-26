#ifndef CLFE_MATERIAL_I_H
#define CLFE_MATERIAL_I_H

#include "TextureImpl.h"
#include "MVariable.h"

#include <cstdint>

namespace clfe
{

	class Material
	{
	private:
		const uint32_t texCount;
		TextureBase** textures;

		const uint32_t varCount;
		MVariableBase** variables;

		uint32_t references;
		bool deleteOnNoRef;

		void triggerReferences();

	public:
		Material(uint32_t texCount, TextureBase** textures, uint32_t varCount, MVariableBase** variables, bool deleteOnNoRef = true);
		Material(TextureBase* texture, uint32_t varCount, MVariableBase** variables, bool deleteOnNoRef = true);
		Material(uint32_t texCount, TextureBase** textures, MVariableBase* variable, bool deleteOnNoRef = true);
		Material(TextureBase* texture, MVariableBase* variable, bool deleteOnNoRef = true);
		Material(TextureBase* texture, bool deleteOnNoRef = true);
		Material(MVariableBase* variable, bool deleteOnNoRef = true);
		~Material();

		inline uint32_t getReferences() const
		{
			return references;
		}

		void addReference();
		void removeReference();

		inline bool deleteOnNoReferences() const
		{
			return deleteOnNoRef;
		}

		inline void setDeleteOnNoReferences(bool value)
		{
			deleteOnNoRef = value;
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