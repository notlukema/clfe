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
		T array[Rows][Cols];

	public:
		Matrix(bool identity = true) requires (Rows == Cols) : array{} // Only works for square matrices
		{
			if (identity) {
				for (msize_t i = 0; i < Rows; i++)
				{
					array[i][i] = static_cast<T>(1);
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
			for (int r = 0; r < Rows; r++)
			{
				for (int c = 0; c < Cols; c++)
				{
					array[r][c] = temp[r * Cols + c];
				}
			}
		}

		Matrix(const T* arr[])
		{
			for (int r = 0; r < Rows; r++)
			{
				for (int c = 0; c < Cols; c++)
				{
					array[r][c] = arr[r][c];
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

		/*
		inline Vector<Cols, T, P> getRowVec(int r) const
		{
			return Vector<Cols, T, P>();
		}
		*/

		inline const T* getRow(int r) const
		{
			return static_cast<const T*>(array[r]);
		}

		template <typename... Args>
			requires (sizeof...(Args) == Cols)
		void setRow(int r, Args... args)
		{
			array[r] = { static_cast<T>(args)... };
		}

		inline T get(int r, int c) const
		{
			return array[r][c];
		}

		inline void setAt(int r, int c, T value)
		{
			array[r][c] = value;
		}

	};

}

#include "MatOp.h"
#ifdef CLFE_VECTOR_H // Unnecessary but whatever
#include "../VecMatOp.h"
#endif

#endif