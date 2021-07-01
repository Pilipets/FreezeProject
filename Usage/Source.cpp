
#include <MyClass.h>
#include <boost/asio/deadline_timer.hpp>

int main() {
	//MyClass& ins = MyClass::getInstance();
	MyClass ins;
	ins.ioc.post([&] {
		boost::system::error_code err;
		boost::asio::deadline_timer(ins.ioc, boost::posix_time::milliseconds(1000)).wait(err);
	});
	return 0;
}