#include "Benchmark.h"

#include <vector>
#include <memory>
#include <chrono>

namespace clu
{

	Benchmark::BenchmarkTimeResults::BenchmarkTimeResults(int length, float* times) : length(length), times(times) {}
	Benchmark::BenchmarkCountResults::BenchmarkCountResults(int length, int* counts) : length(length), counts(counts) {}

	Benchmark::BenchmarkTimeResults::~BenchmarkTimeResults()
	{
		delete times;
	}

	Benchmark::BenchmarkCountResults::~BenchmarkCountResults()
	{
		delete counts;
	}



	std::vector<BenchmarkFunction*> Benchmark::functions;

	void Benchmark::addFunction(BenchmarkFunction* func)
	{
		functions.push_back(func);
	}

	void Benchmark::removeFunction(BenchmarkFunction* func)
	{
		// Not sure if it works, never needed anyways
		functions.erase(std::remove(functions.begin(), functions.end(), func), functions.end());
	}

	Benchmark::BenchmarkTimeResults Benchmark::runAll_LoopSequential(unsigned int iterations)
	{
		float* times = new float[functions.size()];
		for (int i = 0; i < functions.size(); i++) {
			BenchmarkFunction func = *functions.at(i);
			auto start = std::chrono::system_clock::now();
			for (unsigned int j = 0; j < iterations; j++) {
				func();
			}
			auto elapsed = std::chrono::system_clock::now() - start;
			times[i] = elapsed.count();
		}

		return BenchmarkTimeResults(functions.size(), times);
	}

}