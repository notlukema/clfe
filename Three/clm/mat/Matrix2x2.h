#ifndef CLM_MATRIX_2X2_H
#define CLM_MATRIX_2X2_H

#include "Matrix.h"

namespace clfe
{

	template <typename T>
	class Matrix<2, 2, T>
	{

	protected:
		using ct = Vector<2, T>;
		ct array[2];

	public:
		Matrix(T scalar = static_cast<T>(1)) : array{
			ct(scalar, 0),
			ct(0, scalar)
		} {}

		template <typename... Args>
			requires (sizeof...(Args) == Rows * Cols) && AllCompatible<T, Args...>
		Matrix(Unpack(Args...) unpack) : array{
			ct(unpack[0], unpack[1]),
			ct(unpack[2], unpack[3])
		} {
			for (msize_t i = 0; i < Rows * Cols; i++)
			{
				std::cout << unpack[i] << ", ";
			}
			std::cout << "\n";
		}

		Matrix(const T* arr[]) : array{
			ct(arr[0], arr[1]),
			ct(arr[2], arr[3])
		} {}

		Matrix(const Matrix<Rows, Cols, T>& mat) : array{
			ct(mat.get(0)),
			ct(mat.get(1))
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
		constexpr swap(msize_t i1, msize_t j1, msize_t i2, msize_t j2)
		{
			T temp = get(i1, j1);
			setAt(i1, j1, get(i2, j2));
			setAt(i2, j2, temp);
		}

	public:
		void transpose()
		{
			swap(0, 1, 1, 0);
		}

		Matrix<2, 2, T> transposed()
		{
			return Matrix<2, 2, T>(
				get(0, 0), get(1, 0),
				get(0, 1), get(1, 1)
			);
		}

	};

}

#endif