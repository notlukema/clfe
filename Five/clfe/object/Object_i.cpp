#include "Object_i.h"

namespace clfe
{

	Object::Object(ObjectType type, bool active) : type(type), active(active)
	{}

	void Object::deactivate()
	{
		active = false;
	}

	void Object::activate()
	{
		active = true;
	}

	void Object::setActive(bool active)
	{
		this->active = active;
	}

}