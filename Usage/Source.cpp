
/*#include <AsioClass.h>
#include <boost/asio/deadline_timer.hpp>

void test1() {
	AsioClass& ins = AsioClass::getInstance();
	std::cout << "temp\n";
	ins.ioc.post([&] {
		std::cout << "temp\n";
		boost::system::error_code err;
		boost::asio::deadline_timer(ins.ioc, boost::posix_time::milliseconds(1000)).wait(err);
	});
}*/

#include <iostream>
#include <ThreadClass.h>
int main() {
	//ThreadClass& ins = ThreadClass::getInstance();
	ThreadClass ins;
	std::cout << "temp\n";

	{
		std::lock_guard<std::mutex> lk(ins.post_mutex);
		ins.msg_queue.push([] {
			std::cout << "temp\n";
		});
		ins.cv.notify_one();
	}
	//std::this_thread::sleep_for(std::chrono::milliseconds(5000));
	return 0;
}