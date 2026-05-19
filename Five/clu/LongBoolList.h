#ifndef CLU_LONGBOOLLIST_H
#define CLU_LONGBOOLLIST_H

#include <cstdint>
#include <climits>
#include <malloc.h>

namespace clfe
{

	class LongBoolList
	{
	private:
		const uint32_t size;
		const uint32_t size2;
		bool* data;

	public:
		LongBoolList(uint32_t size) : size(size), size2(size / CHAR_BIT)
		{
			data = (bool*)calloc(size2, sizeof(bool));
			// Hope this stuff works because some nitty gritty details may be missed and result in big issues
			// Good thing I'm not using this thing, just for proof of concept and stuff
			// No .cpp file too since I'm not using it and stuff so no point
		}

		~LongBoolList()
		{
			free(data);
		}

		void set(uint32_t i, bool val)
		{
			uint32_t i2 = i / CHAR_BIT;
			uint8_t bit = i - i2;

			if (val)
			{
				data[i2] |= (1 << bit);
			}
			else
			{
				data[i2] &= ~(1 << bit);
			}
		}

		bool get(uint32_t i) const
		{
			uint32_t i2 = i / CHAR_BIT;
			uint8_t bit = i - i2;
			return (data[i2] >> bit) & 1;
		}

	};

	template<uint32_t SIZE>
	using LongBoolListT = LongBoolList<SIZE / CHAR_BIT, SIZE % CHAR_BIT>;

	template <uint32_t SIZE, uint32_t SIZE2>
	class LongBoolList2
	{
	private:
		bool data[SIZE];

	public:
		LongBoolList2() : data{ false }
		{};

		void set(uint32_t i, bool val)
		{
			uint32_t i2 = i / CHAR_BIT;
			uint8_t bit = i - i2;

			if (val)
			{
				data[i2] |= (1 << bit);
			}
			else
			{
				data[i2] &= ~(1 << bit);
			}
		}

		bool get(uint32_t i) const
		{
			uint32_t i2 = i / CHAR_BIT;
			uint8_t bit = i - i2;
			return (data[i2] >> bit) & 1;
		}

	};

}

#endif