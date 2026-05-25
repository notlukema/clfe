#ifndef CLFE_SCENE_H
#define CLFE_SCENE_H

#include "EObject.h"
#include "Model_i.h"

#include "clm/VectorImpl.h"
#include "clm/Quaternion.h"

#include "VectorList.h"

#include <cstdint>

namespace clfe
{

	class Scene
	{
	private:
		VectorList<EObject*> objects;

	public:
		Scene(uint32_t targetSize = 100);

		// Custom allocated object
		EObject* createObject(Model* obj, Vector<3, float> pos = Vector<3, float>(), Quaternion rot = Quaternion());
		// No deletion yet (temporary)

	};

}

#endif