#ifndef CLFE_BITMAP_RGBA_H
#define CLFE_BITMAP_RGBA_H

#include "Bitmap.h"
#include "../../math/vec/Vector4.h"
#include "../../math/vec/Vector3.h"

#include <cstdint>

namespace clfe
{

	template <typename T>
	class BitmapRGBA : public Bitmap<T, 4>
	{
	public:
		BitmapRGBA(int width, int height);
		BitmapRGBA(int width, int height, bool init);
		BitmapRGBA(int width, int height, T* data);
		BitmapRGBA(int width, int height, T r, T g, T b, T a);
		BitmapRGBA(int width, int height, const Vector4<T>& rgba);
		
		Vector4<T> pixel(int x, int y) const;

		void pixel(int x, int y, T r, T g, T b, T a);
		void pixel(int x, int y, const Vector4<T>& rgba);

		T r(int x, int y) const;
		T g(int x, int y) const;
		T b(int x, int y) const;
		T a(int x, int y) const;

		Vector3<T> rgb(int x, int y) const;

		void r(int x, int y, T r);
		void g(int x, int y, T g);
		void b(int x, int y, T b);
		void a(int x, int y, T a);

		void rgb(int x, int y, T r, T g, T b);
		void rgb(int x, int y, const Vector3<T>& rgb);

	};

}

namespace clfe
{

	using BitmapRGBAb = BitmapRGBA<uint8_t>;
	using BitmapRGBAf = BitmapRGBA<float>;
	using BitmapRGBAd = BitmapRGBA<double>;
	using BitmapRGBAi = BitmapRGBA<int>;

}

// Definitions

namespace clfe
{

	template <typename T>
	BitmapRGBA<T>::BitmapRGBA(int width, int height) : Bitmap<T, 4>(width, height) {}

	template <typename T>
	BitmapRGBA<T>::BitmapRGBA(int width, int height, bool init) : Bitmap<T, 4>(width, height, init) {}

	template <typename T>
	BitmapRGBA<T>::BitmapRGBA(int width, int height, T* data) : Bitmap<T, 4>(width, height, data) {}

	template <typename T>
	BitmapRGBA<T>::BitmapRGBA(int width, int height, T r, T g, T b, T a) : Bitmap<T, 4>(width, height)
	{
		for (int i = 0; i < this->size; i += 4) {
			this->data[i] = r;
			this->data[i + 1] = g;
			this->data[i + 2] = b;
			this->data[i + 3] = a;
		}
	}

	template <typename T>
	BitmapRGBA<T>::BitmapRGBA(int width, int height, const Vector4<T>& rgba) : Bitmap<T, 4>(width, height)
	{
		for (int i = 0; i < this->size; i += 4) {
			this->data[i] = rgba.r();
			this->data[i + 1] = rgba.g();
			this->data[i + 2] = rgba.b();
			this->data[i + 3] = rgba.a();
		}
	}

	template <typename T>
	Vector4<T> BitmapRGBA<T>::pixel(int x, int y) const
	{
		int i = this->index(x, y);
		return Vector4<T>(this->data[i], this->data[i + 1], this->data[i + 2], this->data[i + 3]);
	}

	template <typename T>
	void BitmapRGBA<T>::pixel(int x, int y, T r, T g, T b, T a)
	{
		int i = this->index(x, y);
		this->data[i] = r;
		this->data[i + 1] = g;
		this->data[i + 2] = b;
		this->data[i + 3] = a;
	}

	template <typename T>
	void BitmapRGBA<T>::pixel(int x, int y, const Vector4<T>& rgba)
	{
		int i = this->index(x, y);
		this->data[i] = rgba.r();
		this->data[i + 1] = rgba.g();
		this->data[i + 2] = rgba.b();
		this->data[i + 3] = rgba.a();
	}

	template <typename T>
	T BitmapRGBA<T>::r(int x, int y) const
	{
		return this->data[index(x, y)];
	}

	template <typename T>
	T BitmapRGBA<T>::g(int x, int y) const
	{
		return this->data[index(x, y) + 1];
	}

	template <typename T>
	T BitmapRGBA<T>::b(int x, int y) const
	{
		return this->data[index(x, y) + 2];
	}

	template <typename T>
	T BitmapRGBA<T>::a(int x, int y) const
	{
		return this->data[index(x, y) + 3];
	}

	template <typename T>
	Vector3<T> BitmapRGBA<T>::rgb(int x, int y) const
	{
		int i = this->index(x, y);
		return Vector3<T>(this->data[i], this->data[i + 1], this->data[i + 2]);
	}

	template <typename T>
	void BitmapRGBA<T>::r(int x, int y, T r)
	{
		this->data[index(x, y)] = r;
	}

	template <typename T>
	void BitmapRGBA<T>::g(int x, int y, T g)
	{
		this->data[index(x, y) + 1] = g;
	}

	template <typename T>
	void BitmapRGBA<T>::b(int x, int y, T b)
	{
		this->data[index(x, y) + 2] = b;
	}

	template <typename T>
	void BitmapRGBA<T>::a(int x, int y, T a)
	{
		this->data[index(x, y) + 3] = a;
	}

	template <typename T>
	void BitmapRGBA<T>::rgb(int x, int y, T r, T g, T b)
	{
		int i = this->index(x, y);
		this->data[i] = r;
		this->data[i + 1] = g;
		this->data[i + 2] = b;
	}

	template <typename T>
	void BitmapRGBA<T>::rgb(int x, int y, const Vector3<T>& rgb)
	{
		int i = this->index(x, y);
		this->data[i] = rgb.r();
		this->data[i + 1] = rgb.g();
		this->data[i + 2] = rgb.b();
	}

}

#endif