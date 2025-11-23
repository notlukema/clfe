#ifndef CLFE_ISTEPPABLE_H
#define CLFE_ISTEPPABLE_H

#ifndef LAYER_TYPE
#define LAYER_TYPE int
#endif

typedef LAYER_TYPE layer_t;

namespace clfe
{

	class ISteppable
	{
	public:
		virtual bool init() = 0;
		virtual bool step() = 0;
		virtual void terminate() = 0;
		virtual ~ISteppable() {}

		virtual layer_t layer() const
		{
			return 0;
		}

	};

}

#endif