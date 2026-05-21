#ifndef CLFE_OBJECT_I_H
#define CLFE_OBJECT_I_H

namespace clfe
{

	// Object

	class Object
	{
	protected:
		bool active;

		Object(bool active = true);

	public:

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