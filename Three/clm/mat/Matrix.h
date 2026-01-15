#ifndef CLM_MATRIX_H
#define CLM_MATRIX_H

#include "../VecMatCommon.h"
#include "../vec/Vector.h"

namespace clfe
{
	
	template <msize_t Cols, msize_t Rows, typename T>
	class Matrix
	{
	protected:
		Vector<Cols, T> array[Rows];

	public:
		Matrix(T scalar = static_cast<T>(1)) requires (Cols == Rows) : array{} // Only works for square matrices
		{
			for (msize_t i = 0; i < Rows; i++)
			{
				array[i].setAt(i, scalar);
			}
		}

		Matrix() requires (Cols != Rows) : array{} {} // Always all 0 if not a square matrix

		/* Initializes like:
		* 1  2  3  4
		* 5  6  7  8
		* 9  10 11 12
		* 13 14 15 16
		*/
		template <typename... Args>
			requires (sizeof...(Args) == Cols * Rows) && AllCompatible<T, Args...>
		Matrix(Args... args)
		{
			T temp[] = { static_cast<T>(args)... };
			for (msize_t r = 0; r < Rows; r++)
			{
				for (msize_t c = 0; c < Cols; c++)
				{
					array[r].setAt(c, temp[r * Cols + c]);
				}
			}
		}

		Matrix(const T* arr[])
		{
			for (msize_t r = 0; r < Rows; r++)
			{
				for (msize_t c = 0; c < Cols; c++)
				{
					array[r].setAt(c, arr[r * Cols + c]);
				}
			}
		}

		Matrix(const Matrix<Cols, Rows, T>& mat)
		{
			for (msize_t r = 0; r < Rows; r++)
			{
				array[r] = mat.getRow(r);
			}
		}

		inline int rows() const
		{
			return Rows;
		}

		inline int cols() const
		{
			return Cols;
		}

		inline Vector<Cols, T>& operator[](int i)
		{
			return array[i];
		}

		inline Vector<Cols, T> getRow(int i) const
		{
			return array[i];
		}

		inline void setRow(int r, const Vector<Cols, T>& vec)
		{
			array[r] = vec;
		}

		inline const Vector<Cols, T>* const get() const
		{
			return static_cast<const Vector<Cols, T>* const>(array);
		}

		// x-y style: column, then row
		inline T get(int c, int r) const
		{
			return array[r].get(c);
		}

		// x-y style: column, then row
		inline void setAt(int c, int r, T value)
		{
			array[r].setAt(c, value);
		}

		void transpose() requires (Cols == Rows)
		{
			for (msize_t r = 1; r < Rows; r++)
			{
				for (msize_t c = 0; c < r; c++) {
					T temp = get(r, c);
					setAt(r, c, get(c, r));
					setAt(c, r, temp);
				}
			}
		}

		Matrix<Rows, Cols, T> transposed() const
		{
			Matrix<Rows, Cols, T> result;
			for (msize_t r = 0; r < Cols; r++)
			{
				Vector<Rows, T>& row = result[r];
				for (msize_t c = 0; c < Rows; c++)
				{
					row.setAt(c, get(c, r));
				}
			}
			return result;
		}
		
	private:
		template <typename U = T>
		U detHelper(msize_t c, msize_t r, msize_t size, msize_t target) const
		{
			if (size <= 2) {
				if (c + 1 == target)
				{
					return static_cast<U>(get(c, r) * get(c + 2, r + 1) - get(c + 2, r) * get(c, r + 1));
				}
				if (c == target)
				{
					c++;
				}
				return static_cast<U>(get(c, r) * get(c + 1, r + 1) - get(c + 1, r) * get(c, r + 1));
			}

			U sum = static_cast<U>(0);
			U flip = static_cast<U>(1);
			for (msize_t i = 0; i < size; i++)
			{
				// skip target
				sum += flip * (get(c + i, r) * detHelper(c, r + 1, size - 1, c + i));
				flip = static_cast<U>(0) - flip;
			}

			return sum;
		}
		
		/*
		template <typename U = T, typename Size>
		U detHelper(const Matrix<Size, Size, U>& mat) const
		{
			if (Size <= 2) {
				return static_cast<U>(mat.get(0, 0) * mat.get(1, 1) - mat.get(1, 0) * mat.get(0, 1));
			}

			U sum = static_cast<U>(0);
			U flip = static_cast<U>(1);
			for (msize_t i = 0; i < Size; i++)
			{
				sum += flip * (1);
				flip = static_cast<U>(0) - flip;
			}
			return sum;
		}
		*/

	public:
		template <typename U = T>
		inline U determinant() const requires (Cols == Rows) && (Cols >= 2) && Arithmetic2<T, U>
		{
			return detHelper<U>(0, 0, Cols, Cols);
		}

		

	};

}

namespace clfe
{

	template <typename T = float>
	Matrix<4, 4, T> scale(T scale)
	{
		return Matrix<4, 4, T>(
			scale, 0, 0, 0,
			0, scale, 0, 0,
			0, 0, scale, 0,
			0, 0, 0, 1
		);
	}

	template <typename T = float>
	Matrix<4, 4, T> scale(T scaleX, T scaleY, T scaleZ)
	{
		return Matrix<4, 4, T>(
			scaleX, 0, 0, 0,
			0, scaleY, 0, 0,
			0, 0, scaleZ, 0,
			0, 0, 0, 1
		);
	}

	template <typename T = float>
	Matrix<4, 4, T> translate(T tx, T ty, T tz)
	{
		return Matrix<4, 4, T>(
			1, 0, 0, tx,
			0, 1, 0, ty,
			0, 0, 1, tz,
			0, 0, 0, 1
		);
	}

	template <typename T = float>
	Matrix<4, 4, T> rotateX(float rad)
	{
		T c = static_cast<T>(cos(rad));
		T s = static_cast<T>(sin(rad));
		return Matrix<4, 4, T>(
			1, 0, 0, 0,
			0, c, -s, 0,
			0, s, c, 0,
			0, 0, 0, 1
		);
	}

	template <typename T = float>
	Matrix<4, 4, T> rotateY(float rad)
	{
		T c = static_cast<T>(cos(rad));
		T s = static_cast<T>(sin(rad));
		return Matrix<4, 4, T>(
			c, 0, s, 0,
			0, 1, 0, 0,
			-s, 0, c, 0,
			0, 0, 0, 1
		);
	}

	template <typename T = float>
	Matrix<4, 4, T> rotateZ(float rad)
	{
		T c = static_cast<T>(cos(rad));
		T s = static_cast<T>(sin(rad));
		return Matrix<4, 4, T>(
			c, -s, 0, 0,
			s, c, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		);
	}

	template <typename T = float>
		requires Arithmetic<T>
	Matrix<4, 4, T> rotate(float rad, Vector<3, T> axis)
	{
		axis = axis.normalized();
		T c = static_cast<T>(cos(rad));
		T s = static_cast<T>(sin(rad));
		T t = static_cast<T>(1) - c;
		T x = axis.get(0);
		T y = axis.get(1);
		T z = axis.get(2);
		return Matrix<4, 4, T>(
			t * x * x + c,       t * x * y - s * z,   t * x * z + s * y, 0,
			t * x * y + s * z,   t * y * y + c,       t * y * z - s * x, 0,
			t * x * z - s * y,   t * y * z + s * x,   t * z * z + c,     0,
			0, 0, 0, 1
		);
	}

}

#include "MatOp.h"
#ifdef CLM_VECTOR_H // Unnecessary but whatever
#include "../VecMatOp.h"
#endif

#endif