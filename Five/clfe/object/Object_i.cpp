#include "Object_i.h"

namespace clfe
{

	Object::Object(bool active) : active(active)
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