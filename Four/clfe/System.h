#ifndef CLFE_SYSTEM_H
#define CLFE_SYSTEM_H

#include "Attachment.h"
#include "InstanceTypes.h"

#include "List.h"
//#include "Concepts.h"

// Included for the sake of being "part of the system"
#include "CrossPlatform.h"
#include "Log.h"

#include <cstdint>

namespace clfe
{

	using clid = uint32_t;
	constexpr clid BlankID = 0;

	// Forward declarations
	class InstanceBase;

	class InstanceLink;

	template <typename T>
	class InstanceList;

	template <typename T>
	class InstanceListHandle;


	class System
	{
	private:
		static Attachment SystemAttachment;
		static List<InstanceBase*> Instances;
		static clid NextID;

		friend class InstanceBase; // For access to addInstance and removeInstance

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
		static InstanceListHandle<T>* getInstanceList()
		{
			InstanceList<T>* list = getInstanceListInner<T>();
			if (list)
			{
				return list->getHandle();
			}

			return nullptr;
		}

	};

	//
	// Range based list implementation for InstanceList and InstanceListHandle
	//

	struct inslist_null {};

	template <typename T>
	struct inslist_iterator
	{

		InstanceLink* node;
		inslist_iterator(InstanceList<T>* list) : node(list->getFirstLink()) {}

		void operator++()
		{
			node = node->next;
		}

		T* operator*() const
		{
			return static_cast<T*>(node);
		}

		bool operator!=(inslist_null end) const
		{
			return node != nullptr;
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

	//
	// InstanceListHandle
	//

	template <typename T>
	inslist_iterator<T> begin(InstanceListHandle<T>& list);

	template <typename T>
	class InstanceListHandle
	{
	private:
		// For access to list in iterator constructor
		template <typename U>
		friend inslist_iterator<U> begin(InstanceListHandle<U>& list);

		InstanceList<T>* list;

	public:
		InstanceListHandle(InstanceList<T>* list) : list(list) {}

		InsType_t getType() const
		{
			return list->getType();
		}

		int length()
		{
			return list->length();
		}

		bool hasInstance(clid id)
		{
			return list->hasInstance(id);
		}

		T* find(clid id)
		{
			return list->find(id);
		}

	};

	template <typename T>
	inslist_iterator<T> begin(InstanceListHandle<T>& list)
	{
		return inslist_iterator<T>(list.list);
	};

	template <typename T>
	inslist_null end(InstanceListHandle<T>& list)
	{
		return inslist_null();
	};
	
	//
	// InstanceList implementation
	//

	class InstanceBase
	{
	protected:
		InstanceBase(InsType_t type);
		InsType_t type;

		friend class InstanceLink;

		InstanceLink* first;
		int len;

	public:
		virtual ~InstanceBase();

		inline InsType_t getType() const
		{
			return type;
		}

		inline InstanceLink* getFirstLink() const
		{
			return first;
		}

		inline int length() const
		{
			return len;
		}

		virtual bool hasInstance(clid id) = 0;

	};

	class InstanceLink
	{
	public:
		const clid id;
		InstanceBase* const parent;

	private:
		// For access to next pointers
		template <typename T>
		friend struct inslist_iterator;
		template <typename T>
		friend class InstanceList;

		InstanceLink* next;
		InstanceLink* last;

	public:
		InstanceLink(clid id, InstanceBase* parent);
		~InstanceLink();

		inline clid getID() const
		{
			return id;
		}

	};

	// Any type T that isn't a child class of InstanceLink will cause major problems (usually crashing)
	// Instance Interface handles instance indexing stuff as well
	template <typename T>
	class InstanceInterface : public InstanceLink
	{
	public:
		InstanceInterface(InstanceList<T>* list) : InstanceLink(System::genNextID(), list)
		{
			// stuff
		}

	};

	template <typename T>
	class InstanceList : public InstanceBase
	{
	public:
		InstanceList(InsType_t type) : InstanceBase(type) {}

		virtual ~InstanceList()
		{
			while (first != nullptr)
			{
				T* obj = static_cast<T*>(first);
				delete obj;
			}
		}

		InstanceListHandle<T> getHandle()
		{
			return InstanceListHandle<T>(this);
		}

		bool hasInstance(clid id) override
		{
			InstanceLink* node = first;
			while (node != nullptr)
			{
				if (node->getID() == id)
				{
					return true;
				}
				node = node->next;
			}
			return false;
		}

		// The key difference between InstanceList and the non-template base class
		T* find(clid id)
		{
			InstanceLink* node = first;
			while (node != nullptr)
			{
				if (node->getID() == id)
				{
					return static_cast<T*>(node);
				}
				node = node->next;
			}
			return nullptr;
		}

	};


}

#endif