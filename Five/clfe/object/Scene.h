#ifndef CLFE_SCENE_H
#define CLFE_SCENE_H

#include "EObject.h"

#include <cstdint>

namespace clfe
{

	class Scene
	{
	private:

	public:
		Scene();

		// Custom allocated object
		virtual EObject* newObject() = 0;
		virtual void submitObject(EObject* obj) = 0;

	};

}

#endif