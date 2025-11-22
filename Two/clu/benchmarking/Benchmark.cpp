#include "Benchmark.h"

namespace clu
{

	void Benchmark::addFunction(BenchmarkFunction func)
	{
		functions.push_back(func);
	}

}