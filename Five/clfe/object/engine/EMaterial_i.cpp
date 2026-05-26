#include "EMaterial_i.h"

namespace clfe
{

	EMaterial::EMaterial(const uint32_t texCount, TextureBase** textures, const uint32_t varCount, MVariableBase** variables) : texCount(0), textures(nullptr), varCount(0), variables(nullptr), references(0), update_(true)
	{
		update(texCount, textures, varCount, variables);
	}

	EMaterial::~EMaterial()
	{
		clearData();
	}

	void EMaterial::clearData()
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

	void EMaterial::update(const uint32_t texCount, TextureBase** textures, const uint32_t varCount, MVariableBase** variables)
	{
		clearData();
		if (textures != nullptr)
		{
			for (uint32_t i = 0; i < texCount; i++)
			{
				textures[i]->addReference();
			}
		}
		this->textures = textures;

		if (variables != nullptr)
		{
			for (uint32_t i = 0; i < varCount; i++)
			{
				variables[i]->addReference();
			}
		}
		this->variables = variables;

		update_ = true;
	}

	void EMaterial::addReference()
	{
		references++;
	}

	void EMaterial::removeReference()
	{
		references--;
	}

}