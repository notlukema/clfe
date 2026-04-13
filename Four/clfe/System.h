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

		static inline const std::list<InstanceBase*>& getInstances()
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

		InstanceList<T>::Node* first() const
		{
			return list->firstNode();
		}

	};

	class InstanceBase
	{
	protected:
		InstanceBase(InsType_t type);
		InsType_t type;

	public:
		virtual ~InstanceBase();
		virtual void deepDelete() = 0;

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
		InstanceList<T>::Node* current;
		inslist_iterator(InstanceList<T>* list) : list(list), current(list->firstNode()) {}

		void operator++()
		{
			if (current != nullptr)
			{
				current = current->next;
			}
		}

		T* operator*() const
		{
			return current->object;
		}

		bool operator!=(inslist_null end) const
		{
			return current != nullptr;
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

	// Actual list implementation
	template <typename T>
	class InstanceList : public InstanceBase
	{
	public:
		struct Node
		{
			clid id;
			T* object;
			Node* next;

			Node(clid id, T* object, Node* next) : id(id), object(object), next(next) {}
		};

	private:
		Node* first;
		int len;

		InstanceListWrapper<T>* wrapper;

	public:
		InstanceList(InsType_t type) : InstanceBase(type), first(nullptr), len(0)
		{
			wrapper = new InstanceListWrapper(this);
		}

		~InstanceList()
		{
			Node* node = first;

			while (node != nullptr)
			{
				Node* next = node->next;
				delete node;

				node = next;
			}

			delete wrapper;
		}

		InstanceListWrapper<T>* getWrapper()
		{
			return wrapper;
		}

		void deepDelete() override
		{
			// Since all objects should remove themselves from the list, let them have the chance to do that first
			const int len2 = len;
			T** objs = new T*[len2];

			Node* node = first;
			for (int i = 0; i < len2; i++)
			{
				if (node == nullptr)
				{
					CLFE_ERROR("Recorded length was shorter than actual length in InstanceList!");
					return;
				}

				objs[i] = node->object;
				node = node->next;
			}

			for (int i = 0; i < len2; i++)
			{
				delete objs[i];
			}

			delete[] objs;
			
			// Delete any leftovers that weren't removed by the objects themselves, just in case
			// Not that it's illegal in the context of the code, but generally objects that use InstanceLists should be expected to remove themselves
			if (first != nullptr)
			{
				CLFE_LOG("InstanceList has leftover object entries after DeepDelete! It is recommended for objects that use InstanceList to remove themselves upon deletion.");
			}

			node = first;
			while (node != nullptr)
			{
				Node* next = node->next;
				delete node;

				node = next;
			}

			len = 0;
			
		}

		int length()
		{
			return len;
		}

		Node* firstNode() const
		{
			return first;
		}

		void add(clid id, T* object)
		{
			Node* node = new Node(id, object, first);
			first = node;
			len++;
		}

		T* remove(clid id)
		{
			if (first == nullptr)
			{
				return nullptr;
			}

			if (first->id == id)
			{
				T* ret = first->object;
				Node* next = first->next;

				delete first;
				first = next;
				len--;

				return ret;
			}

			Node* lastNode = first;
			Node* node = first->next;

			while (node != nullptr)
			{
				if (node->id == id)
				{
					T* ret = node->object;
					lastNode->next = node->next;

					len--;
					delete node;

					return ret;
				}

				lastNode = node;
				node = node->next;
			}

			return nullptr;
		}

		bool hasInstance(clid id) override
		{
			Node* node = first;
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
			Node* node = first;

			while (node != nullptr)
			{
				if (node->id == id)
				{
					return node->object;
				}

				node = node->next;
			}

			return nullptr;
		}

	};

}

#endif