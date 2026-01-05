#ifndef CLFE_MATRIX_H
#define CLFE_MATRIX_H

#include "../VecMatCommon.h"
#include "../vec/Vector.h"

namespace clfe
{
	
	template <msize_t Rows, msize_t Cols, typename T, typename P = lowp>
	class Matrix
	{
	protected:
		Vector<Cols, T, P> array[Rows];

	public:
		Matrix(bool identity = true) requires (Rows == Cols) : array{} // Only works for square matrices
		{
			if (identity) {
				for (msize_t i = 0; i < Rows; i++)
				{
					array[i].setAt(i, static_cast<T>(1));
				}
			}
		}

		Matrix(bool identity = true) requires (Rows != Cols) : array{} {} // Always all 0 if not a square matrix

		/* Initializes like:
		* 1  2  3  4
		* 5  6  7  8
		* 9  10 11 12
		* 13 14 15 16
		*/
		template <typename... Args>
			requires (sizeof...(Args) == Rows * Cols)
		Matrix(Args... args) : array{}
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

		template <typename P1>
		Matrix(const Matrix<Rows, Cols, T, P1>& mat) : array{ mat.array }
		{
			/*
			for (int r = 0; r < Rows; r++)
			{
				for (int c = 0; c < Cols; c++)
				{
					array[r][c] = mat.get(r, c);
				}
			}
			*/
		}

		inline int rows() const
		{
			return Rows;
		}

		inline int cols() const
		{
			return Cols;
		}

		inline Vector<Cols, T, P> getRow(int r) const
		{
			return array[r];
		}

		Vector<Cols, T, P>& getRowr(int r)
		{
			return array[r];
		}

		template <typename P1>
		void setRow(int r, const Vector<Cols, T, P1>& vec)
		{
			array[r] = Vector<Cols, T, P>(vec);
		}

		inline const Vector<Cols, T, P>* const get() const
		{
			return static_cast<const Vector<Cols, T, P>* const>(array);
		}

		inline T get(int r, int c) const
		{
			return array[r].get(c);
		}

		inline void setAt(int r, int c, T value)
		{
			array[r].setAt(c, value);
		}

		void transpose() requires (Rows == Cols)
		{
			for (msize_t i = 1; i < Rows; i++)
			{
				for (msize_t j = 0; j < i; j++) {
					T temp = get(i, j);
					setAt(i, j, get(j, i));
					setAt(j, i, temp);
				}
			}
		}

		Matrix<Cols, Rows, T, P> transposed()
		{
			Matrix<Cols, Rows, T, P> result;
			for (msize_t r = 0; r < Cols; r++)
			{
				Vector<Rows, T, P>& row = result.getRowr(r);
				for (msize_t c = 0; c < Rows; c++)
				{
					row.setAt(c, get(c, r));
				}
			}
			return result;
		}

	};

}

#include "MatOp.h"
#ifdef CLFE_VECTOR_H // Unnecessary but whatever
#include "../VecMatOp.h"
#endif

#endif