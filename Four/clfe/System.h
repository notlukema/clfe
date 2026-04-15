#ifndef CLFE_SYSTEM_H
#define CLFE_SYSTEM_H

#include "MutualLink.h"
#include "Attachment.h"
#include "InstanceTypes.h"
#include "List.h"
#include "Function.h"

// Included for the sake of being "part of the system"
#include "CrossPlatform.h"
#include "Log.h"

#include <cstdint>

namespace clfe
{

	using clid = uint32_t;
	constexpr clid BlankID = 0;

	class InstanceBase;

	template <typename T>
	class InstanceList;

	template <typename T>
	class InstanceListWrapper;

	class System
	{
	private:
		static Attachment SystemAttachment;
		static List<InstanceBase*> Instances;
		static clid NextID;

		friend class InstanceBase;

		template <typename T>
		friend class InstanceList;

		static void addInstance(InstanceBase* instance);
		static void removeInstance(InstanceBase* instance);

		template <typename T>
		static InstanceList<T>* getInstanceListInner()
		{
			for (InstanceBase* instance : Instances)
			{
				InstanceList<T>* list = dynamic_cast<InstanceList<T>*>(instance);
				if (list)
				{
					return list;
				}
			}
			return nullptr;
		}

	public:
		static bool init();
		static void terminate();
		static clid genNextID();

		static InsType_t getInstanceType(clid id);

		static inline const List<InstanceBase*>& getInstances()
		{
			return Instances;
		}

		template <typename T>
		static T* findInstance(clid id)
		{
			InstanceList<T>* list = getInstanceListInner<T>();
			if (list)
			{
				return list->find(id);
			}

			return nullptr;
		}
		
		template <typename T>
		static InstanceListWrapper<T>* getInstanceList()
		{
			InstanceList<T>* list = getInstanceListInner<T>();
			if (list)
			{
				return list->getWrapper();
			}

			return nullptr;
		}

	};

	template <typename T>
	class InstanceListWrapper
	{
	private:
		InstanceList<T>* list;

		friend class InstanceList<T>;
		InstanceListWrapper(InstanceList<T>* list) : list(list) {}

	public:
		T* find(clid id)
		{
			return list->find(id);
		}

		int length()
		{
			return list->length();
		}
		/*
		List<T*> getAll()
		{
			List<T*> all = List<T*>();
			for (InstanceLink<T>* link : list->links)
			{
				all.push_back(link->obj);
			}
			return all;
		}
		*/
		
	};

	class InstanceBase
	{
	protected:
		InstanceBase(InsType_t type);
		InsType_t type;

	public:
		virtual ~InstanceBase();

		inline InsType_t getType() const
		{
			return type;
		}

		virtual bool hasInstance(clid id) = 0;

	};


	// Range based list implementation
	

	struct inslist_null {};

	template <typename T>
	struct inslist_iterator
	{
		InstanceList<T>* list;
		size_t i;
		inslist_iterator(InstanceList<T>* list) : list(list), i(0) {}

		void operator++()
		{
			i++;
		}

		T* operator*() const
		{
			auto it = std::next(list->links.begin(), i);
			return (*it)->obj;
		}


		bool operator!=(inslist_null end) const
		{
			return i != list->length();
		}

	};

	template <typename T>
	inslist_iterator<T> begin(InstanceList<T>& list)
	{
		return inslist_iterator<T>(&list);
	};

	template <typename T>
	inslist_null end(InstanceList<T>& list)
	{
		return inslist_null();
	};
	

	// InstanceList


	template <typename T>
	class MutualLink<T, InstanceList<T>>
	{
	public:
		T* obj;
		Function<void()> deleteFunc;
		const clid id;
		InstanceList<T>* list;

		MutualLink(T* obj, Function<void()> deleteFunc, clid id, InstanceList<T>* list) : obj(obj), deleteFunc(deleteFunc), id(id), list(list) {}

		~MutualLink()
		{
			deleteFunc();
			list->remove(id);
		}

	};

	template <typename T>
	using InstanceLink = MutualLink<T, InstanceList<T>>;

	// Actual list implementation
	template <typename T>
	class InstanceList : public InstanceBase
	{
	private:
		friend inslist_iterator;
		List<InstanceLink<T>*> links;
		InstanceListWrapper<T>* wrapper;

	public:
		InstanceList(InsType_t type) : InstanceBase(type)
		{
			links = List<InstanceLink<T>*>();
			wrapper = new InstanceListWrapper(this);
		}

		~InstanceList()
		{
			while (!links.empty())
			{
				delete links.front();
			}
		}

		InstanceListWrapper<T>* getWrapper()
		{
			return wrapper;
		}

		size_t length()
		{
			return links.size();
		}

		InstanceLink<T>* add(clid id, T* object, Function<void()> deleteFunc)
		{
			InstanceLink<T>* link = new InstanceLink<T>(object, deleteFunc, id, this);
			links.push_back(link);
			return link;
		}

		// Also deletes the object
		bool remove(clid id)
		{
			return links.remove_if([id](InstanceLink<T>* link)
			{
				if (link->id == id)
				{
					delete link;
					return true;
				}
				return false;
			});
		}

		bool hasInstance(clid id) override
		{
			for (InstanceLink<T>* link : links)
			{
				if (link->id == id)
				{
					return true;
				}
			}

			return false;
		}

		T* find(clid id)
		{
			for (InstanceLink<T>* link : links)
			{
				if (link->id == id)
				{
					return link->obj;
				}
			}

			return nullptr;
		}

	};

}

#endif