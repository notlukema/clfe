#ifndef CLFE_VECTOR_H
#define CLFE_VECTOR_H

namespace clfe
{

	template <typename T, int Size>
	class Vector
	{
	protected:
		T* arr;

	public:
		Vector();
		// Make sure data length is large enough
		Vector(T* data);

		void set(T* data);
		const T* const get();

	};

}

// Definitions

namespace clfe
{

	template <typename T, int Size>
	Vector<T, Size>::Vector() : arr(nullptr) {};

	template <typename T, int Size>
	Vector<T, Size>::Vector(T* data) : arr(data) {};

	template <typename T, int Size>
	void Vector<T, Size>::set(T* data)
	{
		if (arr != nullptr) {
			delete[] arr;
		}

		arr = data;
	}

	template <typename T, int Size>
	const T* const Vector<T, Size>::get()
	{
		return arr;
	}

}

#endif