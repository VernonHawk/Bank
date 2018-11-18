#include <iostream>

#include "Controller.h"
#include "Utility/TerminationWaiter.h"

int main(const int argc, wchar_t* argv[])
{
	const auto port = argc == 2 ? argv[1] : U("1337");

	const auto host = utility::string_t {U("http://localhost:")};

	//auto c = Controller {r, host + port};

	//c.start();

	util::TerminationWaiter::wait();

#ifndef NDEBUG
	std::cout << "Server stopped\n";
#endif

	return 0;
}
