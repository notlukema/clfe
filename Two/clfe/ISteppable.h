#ifndef CLFE_ISTEPPABLE_H
#define CLFE_ISTEPPABLE_H

namespace clfe
{

	class ISteppable
	{
	public:
		virtual bool init() = 0;
		virtual bool step() = 0;
		virtual void terminate() = 0;
		virtual ~ISteppable() {}

		using layer_t = int;

		virtual layer_t layer() const
		{
			return 0;
		}

	};

}

#endif