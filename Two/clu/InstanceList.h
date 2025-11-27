#ifndef CLU_INSTANCELIST_H
#define CLU_INSTANCELIST_H

namespace clu // Might change namespace due to special usage
{

	// This list uses basic incremental searching, unoptimized but works for now

	template <typename K, typename V> // Kind of like key value pair
	class InstanceList
	{
	public:
		struct Node // Key value pair with linked list??!!?
		{
			K key;
			V* value;
			Node* next;

			Node(K key, V* value, Node* next);
		};

		struct ValueArray
		{
			V** array;
			int length;

			ValueArray(V** arr, int length);
		};

	private:
		Node* first;
		int len; // Intresting ahh decision, may or may not remove

	public:
		InstanceList();
		~InstanceList();

		int length();

		void add(K key, V* value);
		V* remove(K key);
		V* find(K key);

		typedef bool (*FilterFunc)(K key, V* value);

		ValueArray filter(FilterFunc func, bool remove);

		inline ValueArray filterOut(FilterFunc func)
		{
			return filter(func, true);
		}

		inline ValueArray filterGet(FilterFunc func)
		{
			return filter(func, false);
		}

	};

}

#endif