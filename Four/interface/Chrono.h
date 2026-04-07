#ifndef CLFE_INTERFACE_CHRONO_H
#define CLFE_INTERFACE_CHRONO_H

#include <chrono>

namespace clfe
{

	namespace chrono
	{

		using SteadyClock = std::chrono::steady_clock;
		using HighResClock = std::chrono::high_resolution_clock;
		using SystemClock = std::chrono::system_clock;

		template <typename T>
		using TimePoint = std::chrono::time_point<T>;

		template <typename T>
		using Duration = std::chrono::duration<T>;

	}

}

#endif