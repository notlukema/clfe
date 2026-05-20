#include "EObject.h"

namespace clfe
{

	EObject::EObject(ObjectType type, bool active) : Object(type, active), pos()
	{}

	EObject::EObject(Vector3f pos, ObjectType type, bool active) : Object(type, active), pos(pos)
	{}

}