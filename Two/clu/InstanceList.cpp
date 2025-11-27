#include "InstanceList.h"

namespace clu
{

	template <typename K, typename V>
	InstanceList<K, V>::Node::Node(K key, V* value, Node* next) : key(key), value(value), next(next) {}

	template <typename K, typename V>
	InstanceList<K, V>::ValueArray::ValueArray(V** arr, int length) : array(arr), length(length) {}

	template <typename K, typename V>
	InstanceList<K, V>::InstanceList()
	{
		first = nullptr;
		len = 0;
	}

	template <typename K, typename V>
	InstanceList<K, V>::~InstanceList()
	{
		Node* node = first;

		//for (int i = 0; i < len; i++) {
		while (node != nullptr) {
			Node* next = node->next;
			delete node;
			node = next;
		}
	}

	template <typename K, typename V>
	int InstanceList<K, V>::length()
	{
		return len;
	}

	template <typename K, typename V>
	void InstanceList<K, V>::add(K key, V* value)
	{
		Node* node = new Node(key, value, first);
		first = node;
		len++;
	}

	template <typename K, typename V>
	V* InstanceList<K, V>::remove(K key)
	{
		Node* lastNode = nullptr;
		Node* node = first;

		//for (int i = 0; i < len; i++) {
		while (node != nullptr) {
			if (node->key == key) {
				V* ret = node->value;

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

	template <typename K, typename V>
	V* InstanceList<K, V>::find(K key)
	{
		Node* node = first;

		//for (int i = 0; i < len; i++) {
		while (node != nullptr) {
			if (node->key == key) {
				return node->value;
			}

			node = node->next;
		}

		return nullptr;
	}

	template <typename K, typename V>
	typename InstanceList<K, V>::ValueArray InstanceList<K, V>::filter(FilterFunc func, bool remove)
	{
		V** array = new V * [len];
		int size = 0;

		Node* lastNode = nullptr;
		Node* node = first;
		//for (int i = 0; i < len; i++) {
		while (node != nullptr)
		{
			if (func(node->key, node->value)) {
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
		
		return ValueArray(array, size);
	}

}