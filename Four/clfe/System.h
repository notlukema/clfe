#ifndef CLFE_SYSTEM_H
#define CLFE_SYSTEM_H

#include "Attachment.h"
#include "InstanceTypes.h"
#include "List.h"

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

	template <typename T>
	class InstanceListHandle
	{
	private:
		InstanceList<T>* list;

	public:
		InstanceListHandle(InstanceList<T>* list) : list(list) {}

		int length()
		{
			return list->length();
		}

		bool remove(clid id)
		{
			return list->remove(id);
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

	//
	// Range based list implementation for InstanceList
	//

	struct inslist_null {};

	template <typename T>
	struct inslist_iterator
	{
		InstanceList<T>::InstanceLink* node;
		inslist_iterator(InstanceList<T>* list) : node(list->getFirstLink()) {}

		void operator++()
		{
			node = node->next;
		}

		T* operator*() const
		{
			return node->obj;
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
	// InstanceList
	//

	template <typename T>
	class InstanceHandle;

	template <typename T>
	class InstanceList : public InstanceBase
	{
	public:
		struct InstanceLink;

	private:
		InstanceLink* first;
		int len;

	public:
		// Deleting the link deletes the entry in the list, but not the object. However, deleting through the list itself will delete the object.
		// The link should not be exposed outside of object implmentations, otherwise there is danger of dangling objects.
		struct InstanceLink
		{
		public:
			T* const obj;
			const clid id;
			InstanceList<T>* const parent;

		private:
			friend class InstanceList<T>; // For access to next and last
			friend struct inslist_iterator<T>; // For access to next and last
			InstanceLink* next;
			InstanceLink* last;

		public:
			InstanceLink(T* obj, clid id, InstanceList<T>* parent, InstanceLink* next, InstanceLink* last) : obj(obj), id(id), parent(parent), next(next), last(last) {}

			// Does not delete the object
			~InstanceLink()
			{
				parent->len--;
				if (last == nullptr)
				{
					parent->first = next;
				}
				else
				{
					last->next = next;
				}
			}

		};

	public:
		InstanceList(InsType_t type) : InstanceBase(type), first(nullptr), len(0) {}

		~InstanceList()
		{
			while (first != nullptr)
			{
				delete first->obj;
				//delete first; // solve later
			}
		}

		InstanceListHandle<T> getHandle()
		{
			return InstanceListHandle<T>(this);
		}

		InstanceLink* getFirstLink()
		{
			return first;
		}

		int length()
		{
			return len;
		}

		InstanceHandle<T>* add(T* object, clid id)
		{
			InstanceLink* node = new InstanceLink(object, id, this, first, nullptr);
			if (first != nullptr)
			{
				first->last = node;
			}
			first = node;
			len++;
			return new InstanceHandle<T>(node);
		}

		// Also deletes the object
		bool remove(clid id)
		{
			InstanceLink* node = first;
			while (node != nullptr)
			{
				if (node->id == id)
				{
					delete node->obj;
					//delete node; // solve later
					return true;
				}
				node = node->next;
			}
			return false;
		}

		bool hasInstance(clid id) override
		{
			InstanceLink* node = first;
			while (node != nullptr)
			{
				if (node->id == id)
				{
					return true;
				}
				node = node->next;
			}
			return false;
		}

		T* find(clid id)
		{
			InstanceLink* node = first;
			while (node != nullptr)
			{
				if (node->id == id)
				{
					return node->obj;
				}
				node = node->next;
			}
			return nullptr;
		}

	};

	template <typename T>
	class InstanceHandle
	{
	private:
		InstanceList<T>::InstanceLink* link;
	public:
		InstanceHandle(InstanceList<T>::InstanceLink* link) : link(link) {}
		~InstanceHandle()
		{
			delete link;
		}
	};

}

#endif