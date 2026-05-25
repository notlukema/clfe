#include "Model_i.h"

#ifndef CLFE_MODEL_H
#define CLFE_MODEL_H

#include "Material_i.h"

namespace clfe
{

	Model* createRectModel(float dx, float dy, float dz, Material* material);

}

#endif