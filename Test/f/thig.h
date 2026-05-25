#pragma once

#include "center.h"
#include <iostream>

namespace thig
{

	class thig2;

	struct thig
	{
		inline static f f2 = f("thig loaded");
	private:
		friend class thig2;
		inline static void func()
		{
			std::cout << "func running\n";
		}

	public:
		inline static void fun33()
		{
			std::cout << "fun33\n";
		}
	};

}