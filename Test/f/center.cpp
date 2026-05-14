#include "center.h"

#include <iostream>

namespace thig
{
	int f::num = 0;

	bool f::postint(int i)
	{
		num = i;
		std::cout << "new f: " << num << std::endl;
		return true;
	}
}