#pragma once
#include <thread>
#include <type_traits>
#include <memory>
#include <future>
#include <mutex>
#include <condition_variable>
#include <functional>

#include <pocket/core/types.hpp>
#include <pocket/containers/containers.hpp>

namespace threads {
	inline u32 max_threads();

	struct threadpool {
		threadpool(size_t nthreads);
		~threadpool();
		
		template<typename F, typename... Fargs>
		auto enqueue(F &&func, Fargs &&... args)
			->std::future<typename std::result_of_t<F(Fargs...)>>;
	
	private:
		vector<std::thread> workers;
		queue<std::function<void()>> tasks;

		std::mutex queue_mutex;
		std::condition_variable condition;
		bool stopped = false;
	};

	inline threadpool::threadpool(size_t n_threads) {
		for (size_t i = 0; i < n_threads; i++) {
			workers.emplace_back(
				[this]() {
					for (;;) {
						std::function<void()> task;
						{
							// create a lock
							std::unique_lock<std::mutex> lock(queue_mutex);
							// use the lock to wait until the ThreadPool is stopped or there is another task waiting
							this->condition.wait(
								lock,
								[this] { return this->stopped || !this->tasks.empty(); }
							);
							// if it is stoppend AND there are no more tasks to complete
							if (this->stopped && this->tasks.empty())
								return;
							// get last task and pop it
							task = std::move(this->tasks.front());
							this->tasks.pop();
						}

						// actually do task
						task();
					}
				}
			);
		}
	}

	template<typename F, typename... Fargs>
	auto threadpool::enqueue(F &&func, Fargs &&... args)
		-> std::future<typename std::result_of_t<F(Fargs...)>> {
		using return_type = typename std::result_of_t<F(Fargs...) >> ;
		
		/*
		make_shared: 
			create a shared_ptr
		packaged_task: 
			wraps any callable object(lambda, function, etc)
			so they can be invoked asynchronously. Return value
			is stored in a future (task->get_future())
		bind:
			generates a call wrapper for <F> to be called with <Fargs>,
			this is why we don't need to pass the arguments later
			in (*task)()
		forward:
			forwards the data to the bind call, this way theres no
			useless copying
		*/
		auto task = std::make_shared<std::packaged_task<return_type(void)>>(
			std::bind(std::forward<F>(func), std::forward<Fargs>(args)...)
		);

		// create the future that will get the value later
		std::future<return_type> res = task->get_future();
		{
			std::unique_lock<std::mutex> lock(queue_mutex);

			if (stop) {
				std::cerr << "Enqueue on stopped pool\n";
				exit(-1);
			}

			tasks.emplace([task]() { (*task)(); });
		}
		// start one thread
		condition.notify_one();
		return res;
	}

	inline threadpool::~threadpool() {
		{
			std::unique_lock<std::mutex> lock(queue_mutex);
			stopped = true;
		}
		// turn on all threads
		condition.notify_all();
		for (std::thread &worker : workers)
			worker.join();
	}

	u32 max_threads() {
		return std::thread::hardware_concurrency();
	}
} // namespace threads 