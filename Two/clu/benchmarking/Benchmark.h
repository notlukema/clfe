#ifndef CLU_BENCHMARK_H
#define CLU_BENCHMARK_H

#include <vector>

namespace clu
{

	using BenchmarkFunction = void (*)();

	class Benchmark
	{
	public:

		struct BenchmarkTimeResults
		{
			int length;
			float* times;

			BenchmarkTimeResults(int length, float* times);
			~BenchmarkTimeResults();
		};

		struct BenchmarkCountResults
		{
			int length;
			int* counts;

			BenchmarkCountResults(int length, int* counts);
			~BenchmarkCountResults();
		};

		using TimeResultCallback = void (*)(BenchmarkTimeResults results);
		using CountResultCallback = void (*)(BenchmarkCountResults results);

		static std::vector<BenchmarkFunction*> functions;

		static void addFunction(BenchmarkFunction*);
		static void removeFunction(BenchmarkFunction*);

		static BenchmarkTimeResults runAll_LoopSequential(unsigned int iterations);
		static BenchmarkCountResults runAll_TimeSequential(unsigned long long milliseconds);
		static BenchmarkTimeResults runAll_LoopParallel(unsigned int iterations);
		static BenchmarkCountResults runAll_TimeParallel(unsigned long long milliseconds);

		static void dispatchAll_LoopSequential(unsigned int iterations, TimeResultCallback* callback);
		static void dispatchAll_TimeSequential(unsigned long long milliseconds, CountResultCallback* callback);
		static void dispatchAll_LoopParallel(unsigned int iterations, TimeResultCallback* callback);
		static void dispatchAll_TimeParallel(unsigned long long milliseconds, CountResultCallback* callback);
		
	};

}

#endif