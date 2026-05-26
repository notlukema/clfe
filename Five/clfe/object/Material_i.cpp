#include "Material_i.h"

namespace clfe
{

	Material::Material(uint32_t texCount, TextureBase** textures, uint32_t varCount, MVariableBase** variables, bool deleteOnNoRef) : texCount(texCount), textures(textures), varCount(varCount), variables(variables), deleteOnNoRef(deleteOnNoRef), references(0)
	{
		triggerReferences();
	}

	Material::Material(TextureBase* texture, uint32_t varCount, MVariableBase** variables, bool deleteOnNoRef) : texCount(1), textures(nullptr), varCount(varCount), variables(variables), deleteOnNoRef(deleteOnNoRef), references(0)
	{
		textures = (TextureBase**)malloc(sizeof(TextureBase*));
		textures[0] = texture;
		triggerReferences();
	}

	Material::Material(uint32_t texCount, TextureBase** textures, MVariableBase* variable, bool deleteOnNoRef) : texCount(texCount), textures(textures), varCount(1), variables(nullptr), deleteOnNoRef(deleteOnNoRef), references(0)
	{
		variables = (MVariableBase**)malloc(sizeof(MVariableBase*));
		variables[0] = variable;
		triggerReferences();
	}

	Material::Material(TextureBase* texture, MVariableBase* variable, bool deleteOnNoRef) : texCount(1), textures(nullptr), varCount(1), variables(nullptr), deleteOnNoRef(deleteOnNoRef), references(0)
	{
		textures = (TextureBase**)malloc(sizeof(TextureBase*));
		textures[0] = texture;
		variables = (MVariableBase**)malloc(sizeof(MVariableBase*));
		variables[0] = variable;
		triggerReferences();
	}

	Material::Material(TextureBase* texture, bool deleteOnNoRef) : texCount(1), textures(nullptr), varCount(0), variables(nullptr), deleteOnNoRef(deleteOnNoRef), references(0)
	{
		textures = (TextureBase**)malloc(sizeof(TextureBase*));
		textures[0] = texture;
		triggerReferences();
	}

	Material::Material(MVariableBase* variable, bool deleteOnNoRef) : texCount(0), textures(nullptr), varCount(1), variables(nullptr), deleteOnNoRef(deleteOnNoRef), references(0)
	{
		variables = (MVariableBase**)malloc(sizeof(MVariableBase*));
		variables[0] = variable;
		triggerReferences();
	}

	Material::~Material()
	{
		if (textures != nullptr)
		{
			for (uint32_t i = 0; i < texCount; i++)
			{
				textures[i]->removeReference();
			}
		}
		if (variables != nullptr)
		{
			for (uint32_t i = 0; i < varCount; i++)
			{
				variables[i]->removeReference();
			}
		}

		delete textures;
		delete variables;
	}

	void Material::triggerReferences()
	{
		if (textures != nullptr)
		{
			for (uint32_t i = 0; i < texCount; i++)
			{
				textures[i]->addReference();
			}
		}
		if (variables != nullptr)
		{
			for (uint32_t i = 0; i < varCount; i++)
			{
				variables[i]->addReference();
			}
		}
	}

	void Material::addReference()
	{
		references++;
	}

	void Material::removeReference()
	{
		references--;
		if (references <= 0 && deleteOnNoRef)
		{
			delete this;
		}
	}

}