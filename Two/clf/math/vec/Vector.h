#ifndef CLFE_VECTOR_H
#define CLFE_VECTOR_H

namespace clfe
{

	template <typename T, int Size>
	class Vector
	{
	protected:
		T array[Size];

	public:
		Vector(); // Unnecessary due to variadic constructor, but helps with clarity
		template <typename... Args>
		Vector(Args... args); // Study "concepts" and other stuff later to constrain number of args

		const T* get() const;

	};

}

// Definitions

namespace clfe
{

	template <typename T, int Size>
	Vector<T, Size>::Vector() : array{} {};

	template <typename T, int Size>
	template <typename... Args>
	Vector<T, Size>::Vector(Args... args) : array{ static_cast<T>(args)... } {}

	template <typename T, int Size>
	const T* Vector<T, Size>::get() const
	{
		return static_cast<const T*>(array);
	}

}

#endif