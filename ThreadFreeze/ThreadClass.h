#pragma once

#ifdef THREADFREEZE_EXPORTS
#define THREADFREEZE_API __declspec(dllexport)
#else
#define THREADFREEZE_API __declspec(dllimport)
#endif


#include <thread>
#include <mutex>
#include <queue>
#include <functional>

struct THREADFREEZE_API ThreadClass {
	void processQueue();
	ThreadClass();
	~ThreadClass();
	static ThreadClass& getInstance();

	bool job_finished;
	std::mutex post_mutex;
	std::condition_variable cv;
	std::queue<std::function<void ()>> msg_queue;
	std::thread worker_thread;
};