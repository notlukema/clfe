#include "DVars.h"
#include <memory>

namespace debug{

	int& Int(int v = 0) {
		data.push_back(std::pair<void*, short int>((void*)&v, 0));
		return v;
	}
}