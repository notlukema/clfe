#include <stdio.h>
#include <vector>
#include <typeinfo>

namespace debug {

	std::vector<std::pair<void*, short int>> data;

	int& Int(int v);

}
