#ifndef CLU_BENCHMARK_H
#define CLU_BENCHMARK_H

#include <vector>

namespace clu
{

	class Benchmark
	{
	public:
		struct Result
		{

		};

		typedef void (*BenchmarkFunction)();
		typedef void (*ResultCallback)(Result* results);

		static std::vector<BenchmarkFunction> functions;

		static void addFunction(BenchmarkFunction);
		static void removeFunction(BenchmarkFunction);

		static Result* runAll_LoopSequential(uint32_t iterations);
		static Result* runAll_TimeSequential(unsigned long long milliseconds);
		static Result* runAll_LoopParallel(uint32_t iterations);
		static Result* runAll_TimeParallel(unsigned long long milliseconds);

		static void dispatchAll_LoopSequential(uint32_t iterations, ResultCallback callback);
		static void dispatchAll_TimeSequential(unsigned long long milliseconds, ResultCallback callback);
		static void dispatchAll_LoopParallel(uint32_t iterations, ResultCallback callback);
		static void dispatchAll_TimeParallel(unsigned long long milliseconds, ResultCallback callback);
		
	};

}

#endif