#ifndef CLFE_SHAREDLINK_H
#define CLFE_SHAREDLINK_H

namespace clfe
{

	class SharedLink;

	class LinkBase
	{
	protected:
		friend class SharedLink; // Exclusive access
		SharedLink* first;
		int len;

		LinkBase();

	public:
		inline int length()
		{
			return len;
		}

	};

	// Theoretically useable between more than 3 LinkPools but not tested and not intended to be used that way
	class SharedLink
	{
	private:
		LinkBase* a; // Well
		LinkBase* b; // Pool
		SharedLink* nexta;
		SharedLink* nextb;
		SharedLink* lasta;
		SharedLink* lastb;

		SharedLink* next(LinkBase* parent);
		SharedLink* last(LinkBase* parent);

		friend class LinkBase; // Exclusive access
		SharedLink(LinkBase* a, SharedLink* nexta, SharedLink* nextb);
		~SharedLink();

	};

	template <typename This, typename Other>
	class LinkWell : public LinkBase
	{
	public:
		LinkWell()
		{

		}

		SharedLink* pull()
		{
			SharedLink* node = new SharedLink(this, first, nullptr);
			if (first != nullptr)
			{
				first->lasta = node;
			}
			first = node;
			len++;
			return node;
		}

	};

	template <typename This, typename Other>
	class LinkPool : public LinkBase
	{
	public:
		LinkPool()
		{

		}

		bool attach(SharedLink* link)
		{
			return true;
		}

	};

}

#endif