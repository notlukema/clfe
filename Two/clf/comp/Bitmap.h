#ifndef CLFE_BITMAP_H
#define CLFE_BITMAP_H

#include <type_traits>

namespace clfe
{

	template <typename T, int Channels>
	class Bitmap
	{
	private:
		const int width, height, size;
		T* data;

	public:
		Bitmap(int width, int height);
		Bitmap(int width, int height, bool init);
		// Initialize without data using nullptr here. Also, make sure data is large enough otherwise there will be problems
		Bitmap(int width, int height, T* data);

		// Work on later
		//template <typename ...Args, typename std::enable_if<sizeof...(Args) == Channels>::type* = nullptr>
		//Bitmap(int width, int height, Args... args);

		// Make sure data is large enough.
		void setData(T* data);
		T* getData();
		inline int index(int x, int y);

	};

}

// Definitions

namespace clfe
{

	template <typename T, int Channels>
	Bitmap<T, Channels>::Bitmap(int width, int height) : width(width), height(height)
	{
		size = width * height * Channels;
		data = (T*)malloc(size * sizeof(T));
	}

	template <typename T, int Channels>
	Bitmap<T, Channels>::Bitmap(int width, int height, bool init) : width(width), height(height)
	{
		size = width * height * Channels;
		if (init) {
			data = (T*)calloc(size * sizeof(T));
		}
		else {
			data = (T*)malloc(size * sizeof(T));
		}
	}

	template <typename T, int Channels>
	Bitmap<T, Channels>::Bitmap(int width, int height, T* data) : width(width), height(height), data(data)
	{
		size = width * height * Channels;
	}

	template <typename T, int Channels>
	void Bitmap<T, Channels>::setData(T* data)
	{
		if (this->data != nullptr) {
			delete[] this->data;
		}

		this->data = data;
	}

	template <typename T, int Channels>
	T* Bitmap<T, Channels>::getData()
	{
		return data;
	}

	template <typename T, int Channels>
	inline int Bitmap<T, Channels>::index(int x, int y)
	{
		return (x + y * width) * channels;
	}

}

#endif