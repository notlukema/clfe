#ifndef CLM_MATRIX_2X2_H
#define CLM_MATRIX_2X2_H

#include "Matrix.h"

namespace clfe
{

	template <typename T>
	class Matrix<2, 2, T>
	{
	protected: // Matrix reimplementation
		using ct = Vector<2, T>;
		ct array[2];

	public:
		Matrix(T scalar = static_cast<T>(1)) : array{
			ct(scalar, 0),
			ct(0, scalar)
		} {}

		Matrix(T m00, T m01,
			T m10, T m11) : array{
			ct(m00, m01),
			ct(m10, m11)
		} {}

		Matrix(const T* arr[]) : array{
			ct(arr[0], arr[1]),
			ct(arr[2], arr[3])
		} {}

		Matrix(const Matrix<2, 2, T>& mat) : array{
			ct(mat.getRow(0)),
			ct(mat.getRow(1))
		} {}

		inline int rows() const
		{
			return 2;
		}

		inline int cols() const
		{
			return 2;
		}

		inline Vector<2, T>& operator[](int i)
		{
			return array[i];
		}

		inline Vector<2, T> getRow(int i) const
		{
			return array[i];
		}

		inline void setRow(int r, const Vector<2, T>& vec)
		{
			array[r] = vec;
		}

		inline const Vector<2, T>* const get() const
		{
			return static_cast<const Vector<2, T>* const>(array);
		}

		inline T get(int r, int c) const
		{
			return array[r].get(c);
		}

		inline void setAt(int r, int c, T value)
		{
			array[r].setAt(c, value);
		}

	private:
		inline void swap(msize_t c1, msize_t r1, msize_t c2, msize_t r2)
		{
			T temp = get(c1, r1);
			setAt(c1, r1, get(c2, r2));
			setAt(c2, r2, temp);
		}

	public:
		void transpose()
		{
			swap(0, 1, 1, 0);
		}

		Matrix<2, 2, T> transposed() const
		{
			return Matrix<2, 2, T>(
				get(0, 0), get(0, 1),
				get(1, 0), get(1, 1)
			);
		}

	public: // Matrix2x2 specific
		inline T m00() const
		{
			return get(0, 0);
		}

		inline T m01() const
		{
			return get(0, 1);
		}

		inline T m10() const
		{
			return get(1, 0);
		}

		inline T m11() const
		{
			return get(1, 1);
		}

	};

}

namespace clfe
{

	template <typename T>
	using Matrix2x2 = Matrix<2, 2, T>;

	using Matrix2x2f = Matrix2x2<float>;
	using Matrix2x2d = Matrix2x2<double>;
	using Matrix2x2i = Matrix2x2<int>;

}

#endif