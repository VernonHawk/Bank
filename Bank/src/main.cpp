#include <iostream>

#include "Controller.h"
#include "Utility/UtilityFunctions.h"

int main(const int argc, wchar_t* argv[])
{
	const auto host = utility::string_t {U("http://localhost:")};

	const auto port = argc == 2 ? argv[1] : U("1337");

	const auto api = U("/api");

	util::startServer(host + port + api);

#ifndef NDEBUG
	std::cout << "Server stopped\n";
#endif

	return 0;
}
