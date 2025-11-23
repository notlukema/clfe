#include "Benchmark.h"

// ARTIFACT1: Should already be included by Benchmark.h
#include <vector>

namespace clu
{

	std::vector<BenchmarkFunction> Benchmark::functions;

	void Benchmark::addFunction(BenchmarkFunction func)
	{
		functions.push_back(func);
	}

}