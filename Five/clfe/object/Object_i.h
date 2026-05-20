#ifndef CLFE_OBJECT_I_H
#define CLFE_OBJECT_I_H

namespace clfe
{

	// Object types

	enum class ObjectType
	{

		Dynamic = 1,
		Static = 2

	};

	// Object

	class Object
	{
	protected:
		const ObjectType type;
		bool active;

		Object(ObjectType type = ObjectType::Static, bool active = true);

	public:
		inline ObjectType getType() const
		{
			return type;
		}

		inline bool isActive() const
		{
			return active;
		}

		void deactivate();
		void activate();
		void setActive(bool active);

	};

}

#endif