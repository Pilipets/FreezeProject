#include "pch.h"

#include "AsioClass.h"

AsioClass::AsioClass() :
	work_guard(boost::asio::make_work_guard(ioc)),
	worker_thread([this] { ioc.run(); }) {
}

AsioClass::~AsioClass()
{
	work_guard.reset();
	worker_thread.join();
}

AsioClass& AsioClass::getInstance()
{
	static AsioClass ins;
	return ins;
}
