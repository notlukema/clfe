#include "EObject.h"

namespace clfe
{

	EObject::EObject(ObjectType type, bool active) : Object(active), type(type), pos()
	{}

	EObject::EObject(Vector3f pos, ObjectType type, bool active) : Object(active), type(type), pos(pos)
	{}

}