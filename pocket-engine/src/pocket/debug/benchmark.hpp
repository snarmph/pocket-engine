#pragma once

#include <chrono>
#include <iostream>

namespace debug {

	using micro = std::chrono::microseconds;
	using milli = std::chrono::milliseconds;

	template<typename T>
	struct benchmark {
		inline void start() {
			begin = std::chrono::high_resolution_clock::now();
		}

		inline auto end() {
			auto finish = std::chrono::high_resolution_clock::now();
			auto taken = std::chrono::duration_cast<T>(finish - begin).count();
			std::cout << "time taken: " << taken << "\n";
			return taken;
		}
	private:
		std::chrono::high_resolution_clock::time_point begin;
	};
} // namespace debug 

