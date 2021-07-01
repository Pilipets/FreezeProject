#include "pch.h"

#include "ThreadClass.h"
#include <iostream>

void ThreadClass::processQueue()
{
	while (1) {
		std::function<void()> action;
		{
			std::unique_lock<std::mutex> lk(post_mutex);
			cv.wait(lk, [&] { return !msg_queue.empty() || job_finished; });
			if (msg_queue.empty()) {
				std::cout << "Msg queue empty\n";
				break;
			}

			action = std::move(msg_queue.front());
			msg_queue.pop();
		}

		action();
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
}

ThreadClass::ThreadClass() :
	job_finished(false),
	worker_thread(&ThreadClass::processQueue, this) {
}

ThreadClass::~ThreadClass()
{
	std::cout << "Dtor called\n";
	{
		std::lock_guard<std::mutex> lk(post_mutex);
		job_finished = true;
		cv.notify_one();
	}
	worker_thread.join();
	std::cout << "Dtor joined\n";
}

ThreadClass& ThreadClass::getInstance()
{
	static ThreadClass ins;
	return ins;
}
