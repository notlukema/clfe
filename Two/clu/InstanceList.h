#ifndef CLU_INSTANCELIST_H
#define CLU_INSTANCELIST_H

#include "../clfe/System.h"

namespace clu // Might change namespace due to special usage
{

	// This list uses basic incremental searching, unoptimized but works for now

	template <typename T>
	class InstanceList
	{
	public:
		struct Node // Key value pair with linked list??!!?
		{
			clid id;
			T* value;
			Node* next;

			Node(clid id, T* value, Node* next);
		};

		struct ValueArray
		{
			T** array;
			int length;

			ValueArray(T** arr, int length);
			//~ValueArray(); Unneeded
		};

	private:
		Node* first;
		int len; // Intresting ahh decision, may or may not remove

	public:
		InstanceList();
		~InstanceList();

		int length();

		void add(clid id, T* value);
		T* remove(clid id);
		T* find(clid id);

		using FilterFunc = bool (*)(clid, T*);

		ValueArray* filter(FilterFunc func, bool remove);

		inline ValueArray* filterOut(FilterFunc func)
		{
			return filter(func, true);
		}

		inline ValueArray* filterGet(FilterFunc func)
		{
			return filter(func, false);
		}

	};

}

// Definitions

namespace clu
{

	template <typename T>
	InstanceList<T>::Node::Node(clid id, T* value, Node* next) : id(id), value(value), next(next) {}

	template <typename T>
	InstanceList<T>::ValueArray::ValueArray(T** arr, int length) : array(arr), length(length) {}

	template <typename T>
	InstanceList<T>::InstanceList()
	{
		first = nullptr;
		len = 0;
	}

	template <typename T>
	InstanceList<T>::~InstanceList()
	{
		Node* node = first;

		//for (int i = 0; i < len; i++) {
		while (node != nullptr) {
			Node* next = node->next;
			delete node;

			node = next;
		}
	}

	template <typename T>
	int InstanceList<T>::length()
	{
		return len;
	}

	template <typename T>
	void InstanceList<T>::add(clid id, T* value)
	{
		Node* node = new Node(id, value, first);
		first = node;
		len++;
	}

	template <typename T>
	T* InstanceList<T>::remove(clid id)
	{
		Node* lastNode = nullptr;
		Node* node = first;

		//for (int i = 0; i < len; i++) {
		while (node != nullptr) {
			if (node->id == id) {
				T* ret = node->value;

				if (lastNode == nullptr) {
					first = node->next;
				}
				else {
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

	template <typename T>
	T* InstanceList<T>::find(clid id)
	{
		Node* node = first;

		//for (int i = 0; i < len; i++) {
		while (node != nullptr) {
			if (node->id == id) {
				return node->value;
			}

			node = node->next;
		}

		return nullptr;
	}
	
	template <typename T>
	typename InstanceList<T>::ValueArray* InstanceList<T>::filter(FilterFunc func, bool remove)
	{
		T** array = new T * [len];
		int size = 0;

		Node* lastNode = nullptr;
		Node* node = first;

		//for (int i = 0; i < len; i++) {
		while (node != nullptr) {
			if (func(node->id, node->value)) {
				array[size] = node->value;
				size++;

				if (remove) {
					Node* next = node->next;
					if (lastNode == nullptr) {
						first = next;
					}
					else {
						lastNode->next = next;
					}

					len--;
					delete node;

					// lastNode doesn't change
					node = next;
					continue;
				}
			}

			lastNode = node;
			node = node->next;
		}

		return new ValueArray(array, size);
	}

}

#endif