#ifndef CLFE_SYSTEM_H
#define CLFE_SYSTEM_H

#include "CrossPlatform.h"
#include "Error.h"
#include "CLFE.h"
#include "Attachment.h"
#include "InstanceTypes.h"

#include <list>

namespace clfe
{

	using clid = unsigned int;

	class InstanceBase;

	template <typename T>
	class InstanceList;

	template <typename T>
	class InstanceListWrapper;

	class System
	{
	private:
		static Attachment SystemAttachment;
		static std::list<InstanceBase*> Instances;
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
			Node* node = first;
			while (node != nullptr)
			{
				Node* next = node->next;
				delete node->object;
				delete node;

				node = next;
			}

			first = nullptr;
			len = 0;
		}

		int length()
		{
			return len;
		}

		void add(clid id, T* object)
		{
			Node* node = new Node(id, object, first);
			first = node;
			len++;
		}

		T* remove(clid id)
		{
			Node* lastNode = nullptr;
			Node* node = first;

			while (node != nullptr)
			{
				if (node->id == id)
				{
					T* ret = node->object;

					if (lastNode == nullptr)
					{
						first = node->next;
					}
					else
					{
						lastNode->next = node->next;
					}

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