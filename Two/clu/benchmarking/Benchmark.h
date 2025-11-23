#ifndef CLU_BENCHMARK_H
#define CLU_BENCHMARK_H

#include <vector>

namespace clu
{

	struct BenchmarkResult
	{

	};
	typedef void (*BenchmarkFunction)();
	typedef void (*ResultCallback)(BenchmarkResult* results);

	class Benchmark
	{
	public:

		static std::vector<BenchmarkFunction> functions;

		static void addFunction(BenchmarkFunction);
		static void removeFunction(BenchmarkFunction);

		static BenchmarkResult* runAll_LoopSequential(uint32_t iterations);
		static BenchmarkResult* runAll_TimeSequential(unsigned long long milliseconds);
		static BenchmarkResult* runAll_LoopParallel(uint32_t iterations);
		static BenchmarkResult* runAll_TimeParallel(unsigned long long milliseconds);

		static void dispatchAll_LoopSequential(uint32_t iterations, ResultCallback callback);
		static void dispatchAll_TimeSequential(unsigned long long milliseconds, ResultCallback callback);
		static void dispatchAll_LoopParallel(uint32_t iterations, ResultCallback callback);
		static void dispatchAll_TimeParallel(unsigned long long milliseconds, ResultCallback callback);
		
	};

}

#endif