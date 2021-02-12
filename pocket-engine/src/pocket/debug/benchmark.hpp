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

		inline long long end(bool print = true) {
			auto finish = std::chrono::high_resolution_clock::now();
			auto taken = std::chrono::duration_cast<T>(finish - begin).count();
			if(print)
				std::cout << "time taken: " << taken << "\n";
			return taken;
		}
	private:
		std::chrono::high_resolution_clock::time_point begin;
	};

	template<size_t MAX = 100>
	struct median {

		median() {
			for (auto &t : times)
				t = -1;
		}
		
		void add(long long value) {
			times[counter++] = value;
			if (counter == MAX)
				counter = 0;
		}

		double get() {
			double res = 0.0;
			size_t n = 0;
			for (auto &t : times) {
				if (t == -1)
					break;
				n++;
				res += t;
			}

			return res / n;
		}

	private:
		long long times[MAX]{};
		size_t counter = 0;
	};
} // namespace debug 

