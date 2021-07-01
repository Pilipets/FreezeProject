#include "pch.h"

#include "MyClass.h"

MyClass::MyClass() :
	work_guard(boost::asio::make_work_guard(ioc)),
	worker_thread([this] { ioc.run(); }) {
}

MyClass::~MyClass()
{
	work_guard.reset();
	worker_thread.join();
}

MyClass& MyClass::getInstance()
{
	static MyClass ins;
	return ins;
}
