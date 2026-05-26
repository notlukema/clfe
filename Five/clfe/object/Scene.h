#ifndef CLFE_SCENE_H
#define CLFE_SCENE_H

#include "engine/EObject_i.h"
#include "engine/EMesh_i.h"
#include "engine/EMaterial_i.h"
#include "Model_i.h"
#include "Material_i.h"

#include "clm/VectorImpl.h"
#include "clm/Quaternion.h"

#include "VectorList.h"

#include <cstdint>

namespace clfe
{

	// Instance list here later for updates and stuff

	class Scene
	{
	private:
		VectorList<EObject*> objects;
		VectorList<EMaterial*> materials;
		VectorList<TextureBase*> textures;
		VectorList<MVariableBase*> variables;

		EMaterial* addMaterial(Material* material);

	public:
		Scene(uint32_t targetSize = 100);

		EObject* addObject(Model* obj, Vector<3, float> pos = Vector<3, float>(), Quaternion rot = Quaternion(), ObjectType type = ObjectType::Static, bool active = true);

		void update();
		void clear();

	};

}

#endif