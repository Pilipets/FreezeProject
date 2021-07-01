#pragma once

#ifdef ASIOFREEZE_EXPORTS
#define ASIOFREEZE_API __declspec(dllexport)
#else
#define ASIOFREEZE_API __declspec(dllimport)
#endif


#include <thread>
#include <boost/asio/io_context.hpp>

struct ASIOFREEZE_API MyClass {
	MyClass();
	~MyClass();
	static MyClass& getInstance();

	boost::asio::io_context ioc;
	boost::asio::executor_work_guard<boost::asio::io_context::executor_type> work_guard;
	std::thread worker_thread;
};