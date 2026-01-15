#ifndef CLM_MATRIX_OP_H
#define CLM_MATRIX_OP_H

// Guards against if anyone decides to include this file directly
#include "Matrix.h"

namespace clfe
{

	static constexpr int smax2(int a, int b)
	{
		return (a > b) ? a : b;
	}

	// Addition

	template <msize_t Cols, msize_t Rows, typename T, typename U>
		requires Arithmetic<T> && Arithmetic<U>
	auto operator+(const Matrix<Cols, Rows, T>& mat1, const Matrix<Cols, Rows, U>& mat2) -> Matrix<Cols, Rows, decltype(static_cast<T>(0) + static_cast<U>(0))>
	{
		auto result = Matrix<Cols, Rows, decltype(static_cast<T>(0) + static_cast<U>(0))>();
		for (msize_t r = 0; r < Rows; r++)
		{
			result.setRow(r, mat1.get(r) + mat2.get(r));
		}
		return result;
	}

	template <msize_t Cols1, msize_t Rows1, msize_t Cols2, msize_t Rows2, typename T, typename U>
		requires Arithmetic<T> && Arithmetic<U>
	auto operator+(const Matrix<Cols1, Rows1, T>& mat1, const Matrix<Cols2, Rows2, U>& mat2) -> Matrix<smax2(Cols1, Cols2), smax2(Rows1, Rows2), decltype(static_cast<T>(0) + static_cast<U>(0))>
	{
		auto result = Matrix<smax2(Cols1, Cols2), smax2(Rows1, Rows2), decltype(static_cast<T>(0) + static_cast<U>(0))>();
		for (msize_t r = 0; r < smax2(Rows1, Rows2); r++)
		{
			result.setRow(r,
				((r < Rows1) ? mat1.getRow(r) : Vector<Cols1, T>()) +
				((r < Rows2) ? mat2.getRow(r) : Vector<Cols2, U>())
			);
		}
		return result;
	}

	template <msize_t Cols, msize_t Rows, typename T, typename U>
		requires Arithmetic3<T, U>
	Matrix<Cols, Rows, T>& operator+=(Matrix<Cols, Rows, T>& mat1, const Matrix<Cols, Rows, U>& mat2)
	{
		for (msize_t r = 0; r < Rows; r++)
		{
			mat1.setRow(r, mat1.getRow(r) + mat2.getRow(r));
		}
		return mat1;
	}

	// Subtraction

	template <msize_t Cols, msize_t Rows, typename T, typename U>
		requires Arithmetic<T> && Arithmetic<U>
	auto operator-(const Matrix<Cols, Rows, T>& mat1, const Matrix<Cols, Rows, U>& mat2) -> Matrix<Cols, Rows, decltype(static_cast<T>(0) + static_cast<U>(0))>
	{
		auto result = Matrix<Cols, Rows, decltype(static_cast<T>(0) + static_cast<U>(0))>();
		for (msize_t r = 0; r < Rows; r++)
		{
			result.setRow(r, mat1.get(r) - mat2.get(r));
		}
		return result;
	}

	template <msize_t Cols1, msize_t Rows1, msize_t Cols2, msize_t Rows2, typename T, typename U>
		requires Arithmetic<T> && Arithmetic<U>
	auto operator-(const Matrix<Cols1, Rows1, T>& mat1, const Matrix<Cols2, Rows2, U>& mat2) -> Matrix<smax2(Cols1, Cols2), smax2(Rows1, Rows2), decltype(static_cast<T>(0) + static_cast<U>(0))>
	{
		auto result = Matrix<smax2(Cols1, Cols2), smax2(Rows1, Rows2), decltype(static_cast<T>(0) + static_cast<U>(0))>();
		for (msize_t r = 0; r < smax2(Rows1, Rows2); r++)
		{
			result.setRow(r,
				((r < Rows1) ? mat1.getRow(r) : Vector<Cols1, T>()) -
				((r < Rows2) ? mat2.getRow(r) : Vector<Cols2, U>())
			);
		}
		return result;
	}

	template <msize_t Cols, msize_t Rows, typename T, typename U>
		requires Arithmetic3<T, U>
	Matrix<Cols, Rows, T>& operator-=(Matrix<Cols, Rows, T>& mat1, const Matrix<Cols, Rows, U>& mat2)
	{
		for (msize_t r = 0; r < Rows; r++)
		{
			mat1.setRow(r, mat1.getRow(r) - mat2.getRow(r));
		}
		return mat1;
	}

	// Multiplication

#ifdef CLM_USEREALMULT

	template <msize_t Cols, msize_t Rows, typename T, typename U>
		requires Arithmetic<T>&& Arithmetic<U>
	auto operator*(const Matrix<Cols, Rows, T>& mat1, const Matrix<Cols, Rows, U>& mat2) -> Matrix<Cols, Rows, decltype(static_cast<T>(0) + static_cast<U>(0))>
	{
		auto result = Matrix<Cols, Rows, decltype(static_cast<T>(0) + static_cast<U>(0))>();
		for (msize_t r = 0; r < Rows; r++)
		{
			result.setRow(r, mat1.get(r) * mat2.get(r));
		}
		return result;
	}

	template <msize_t Cols, msize_t Rows, typename T, typename U>
		requires Arithmetic3<T, U>
	Matrix<Cols, Rows, T>& operator*=(Matrix<Cols, Rows, T>& mat1, const Matrix<Cols, Rows, U>& mat2)
	{
		for (msize_t r = 0; r < Rows; r++)
		{
			mat1.setRow(r, mat1.getRow(r) * mat2.getRow(r));
		}
		return mat1;
	}

	template <msize_t Cols1, msize_t Rows1, msize_t Cols2, msize_t Rows2, typename T, typename U>
		requires (Cols1 == Rows2) && Arithmetic<T> && Arithmetic<U>
	auto matmul(const Matrix<Cols1, Rows1, T>& mat1, const Matrix<Cols2, Rows2, U>& mat2) -> Matrix<Cols2, Rows1, decltype(static_cast<T>(0) + static_cast<U>(0))>
	{
		auto result = Matrix<Cols2, Rows1, decltype(static_cast<T>(0) + static_cast<U>(0))>();
		for (msize_t r = 0; r < Rows1; r++)
		{
			for (msize_t c = 0; c < Cols2; c++)
			{
				decltype(static_cast<T>(0) + static_cast<U>(0)) sum = 0;
				for (msize_t k = 0; k < Cols1; k++)
				{
					sum += mat1.get(k, r) * mat2.get(c, k);
				}
				result.setAt(c, r, sum);
			}
		}
		return result;
	}

	template <msize_t Cols, msize_t Rows, msize_t Size, typename T, typename U>
		requires (Cols == Size) && Arithmetic<T> && Arithmetic<U>
	auto matmul(const Matrix<Cols, Rows, T>& mat1, const Vector<Size, U>& vec2) -> Vector<Rows, decltype(static_cast<T>(0) + static_cast<U>(0))>
	{
		auto result = Vector<Rows, decltype(static_cast<T>(0) + static_cast<U>(0))>();
		for (msize_t r = 0; r < Rows; r++)
		{
			decltype(static_cast<T>(0) + static_cast<U>(0)) sum = 0;
			for (msize_t k = 0; k < Cols; k++)
			{
				sum += mat1.get(k, r) * vec2.get(k);
			}
			result.setAt(r, sum);
		}
		return result;
	}

#else

	template <msize_t Cols1, msize_t Rows1, msize_t Cols2, msize_t Rows2, typename T, typename U>
		requires (Cols1 == Rows2) && Arithmetic<T>&& Arithmetic<U>
	auto operator*(const Matrix<Cols1, Rows1, T>& mat1, const Matrix<Cols2, Rows2, U>& mat2) -> Matrix<Cols2, Rows1, decltype(static_cast<T>(0) + static_cast<U>(0))>
	{
		auto result = Matrix<Cols2, Rows1, decltype(static_cast<T>(0) + static_cast<U>(0))>();
		for (msize_t r = 0; r < Rows1; r++)
		{
			for (msize_t c = 0; c < Cols2; c++)
			{
				decltype(static_cast<T>(0) + static_cast<U>(0)) sum = 0;
				for (msize_t k = 0; k < Cols1; k++)
				{
					sum += mat1.get(k, r) * mat2.get(c, k);
				}
				result.setAt(c, r, sum);
			}
		}
		return result;
	}

	template <msize_t Cols, msize_t Rows, msize_t Size, typename T, typename U>
		requires (Cols == Size) && Arithmetic<T>&& Arithmetic<U>
	auto operator*(const Matrix<Cols, Rows, T>& mat1, const Vector<Size, U>& vec2) -> Vector<Rows, decltype(static_cast<T>(0) + static_cast<U>(0))>
	{
		auto result = Vector<Rows, decltype(static_cast<T>(0) + static_cast<U>(0))>();
		for (msize_t r = 0; r < Rows; r++)
		{
			decltype(static_cast<T>(0) + static_cast<U>(0)) sum = 0;
			for (msize_t k = 0; k < Cols; k++)
			{
				sum += mat1.get(k, r) * vec2.get(k);
			}
			result.setAt(r, sum);
		}
		return result;
	}

	template <msize_t Cols, msize_t Rows, typename T, typename U>
		requires Arithmetic<T>&& Arithmetic<U>
	auto matmul(const Matrix<Cols, Rows, T>& mat1, const Matrix<Cols, Rows, U>& mat2) -> Matrix<Cols, Rows, decltype(static_cast<T>(0) + static_cast<U>(0))>
	{
		auto result = Matrix<Cols, Rows, decltype(static_cast<T>(0) + static_cast<U>(0))>();
		for (msize_t r = 0; r < Rows; r++)
		{
			result.setRow(r, mat1.get(r) * mat2.get(r));
		}
		return result;
	}

#endif

	// Division

	template <msize_t Cols, msize_t Rows, typename T, typename U>
		requires Arithmetic<T> && Arithmetic<U>
	auto operator/(const Matrix<Cols, Rows, T>& mat1, const Matrix<Cols, Rows, U>& mat2) -> Matrix<Cols, Rows, decltype(static_cast<T>(0) + static_cast<U>(0))>
	{
		auto result = Matrix<Cols, Rows, decltype(static_cast<T>(0) + static_cast<U>(0))>();
		for (msize_t r = 0; r < Rows; r++)
		{
			result.setRow(r, mat1.get(r) / mat2.get(r));
		}
		return result;
	}

	template <msize_t Cols, msize_t Rows, typename T, typename U>
		requires Arithmetic3<T, U>
	Matrix<Cols, Rows, T>& operator/=(Matrix<Cols, Rows, T>& mat1, const Matrix<Cols, Rows, U>& mat2)
	{
		for (msize_t r = 0; r < Rows; r++)
		{
			mat1.setRow(r, mat1.getRow(r) / mat2.getRow(r));
		}
		return mat1;
	}

	//
	// Scalar operations
	//

	// Addition

	template <msize_t Cols, msize_t Rows, typename T, typename U>
		requires Arithmetic<T> && Arithmetic<U>
	auto operator+(const Matrix<Cols, Rows, T>& mat, U scalar) -> Matrix<Cols, Rows, decltype(static_cast<T>(0) + static_cast<U>(0))>
	{
		auto result = Matrix<Cols, Rows, decltype(static_cast<T>(0) + static_cast<U>(0))>();
		for (msize_t r = 0; r < Rows; r++)
		{
			result.setRow(r, mat.getRow(r) + scalar);
		}
		return result;
	}

	template <msize_t Cols, msize_t Rows, typename T, typename U>
		requires Arithmetic3<T, U>
	Matrix<Cols, Rows, T>& operator+=(Matrix<Cols, Rows, T>& mat, U scalar)
	{
		for (msize_t r = 0; r < Rows; r++)
		{
			mat.setRow(r, mat.getRow(r) + scalar);
		}
		return mat;
	}

	// Subtraction

	template <msize_t Cols, msize_t Rows, typename T, typename U>
		requires Arithmetic<T> && Arithmetic<U>
	auto operator-(const Matrix<Cols, Rows, T>& mat, U scalar) -> Matrix<Cols, Rows, decltype(static_cast<T>(0) + static_cast<U>(0))>
	{
		auto result = Matrix<Cols, Rows, decltype(static_cast<T>(0) + static_cast<U>(0))>();
		for (msize_t r = 0; r < Rows; r++)
		{
			result.setRow(r, mat.getRow(r) - scalar);
		}
		return result;
	}

	template <msize_t Cols, msize_t Rows, typename T, typename U>
		requires Arithmetic3<T, U>
	Matrix<Cols, Rows, T>& operator-=(Matrix<Cols, Rows, T>& mat, U scalar)
	{
		for (msize_t r = 0; r < Rows; r++)
		{
			mat.setRow(r, mat.getRow(r) - scalar);
		}
		return mat;
	}

	// Multiplication

	template <msize_t Cols, msize_t Rows, typename T, typename U>
		requires Arithmetic<T> && Arithmetic<U>
	auto operator*(const Matrix<Cols, Rows, T>& mat, U scalar) -> Matrix<Cols, Rows, decltype(static_cast<T>(0) + static_cast<U>(0))>
	{
		auto result = Matrix<Cols, Rows, decltype(static_cast<T>(0) + static_cast<U>(0))>();
		for (msize_t r = 0; r < Rows; r++)
		{
			result.setRow(r, mat.getRow(r) * scalar);
		}
		return result;
	}

	template <msize_t Cols, msize_t Rows, typename T, typename U>
		requires Arithmetic3<T, U>
	Matrix<Cols, Rows, T>& operator*=(Matrix<Cols, Rows, T>& mat, U scalar)
	{
		for (msize_t r = 0; r < Rows; r++)
		{
			mat.setRow(r, mat.getRow(r) * scalar);
		}
		return mat;
	}

	// Division

	template <msize_t Cols, msize_t Rows, typename T, typename U>
		requires Arithmetic<T> && Arithmetic<U>
	auto operator/(const Matrix<Cols, Rows, T>& mat, U scalar) -> Matrix<Cols, Rows, decltype(static_cast<T>(0) + static_cast<U>(0))>
	{
		auto result = Matrix<Cols, Rows, decltype(static_cast<T>(0) + static_cast<U>(0))>();
		for (msize_t r = 0; r < Rows; r++)
		{
			result.setRow(r, mat.getRow(r) / scalar);
		}
		return result;
	}

	template <msize_t Cols, msize_t Rows, typename T, typename U>
		requires Arithmetic3<T, U>
	Matrix<Cols, Rows, T>& operator/=(Matrix<Cols, Rows, T>& mat, U scalar)
	{
		for (msize_t r = 0; r < Rows; r++)
		{
			mat.setRow(r, mat.getRow(r) / scalar);
		}
		return mat;
	}

	//
	// Comparisons
	//

	template <msize_t Cols, msize_t Rows, typename T, typename U>
	bool operator==(const Matrix<Cols, Rows, T>& mat1, const Matrix<Cols, Rows, U>& mat2)
	{
		for (msize_t r = 0; r < Rows; r++)
		{
			if (mat1.getRow(r) != mat2.getRow(r))
			{
				return false;
			}
		}
		return true;
	}

	template <msize_t Cols, msize_t Rows, typename T, typename U>
	bool operator!=(const Matrix<Cols, Rows, T>& mat1, const Matrix<Cols, Rows, U>& mat2)
	{
		for (msize_t r = 0; r < Rows; r++)
		{
			if (mat1.getRow(r) != mat2.getRow(r))
			{
				return true;
			}
		}
		return false;
	}

}

#endif