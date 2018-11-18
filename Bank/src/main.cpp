#include <iostream>

#include "Controller.h"
#include "Utility/UtilityFunctions.h"

int main(const int argc, wchar_t* argv[])
{
	const auto port = argc == 2 ? argv[1] : U("1337");

	const auto uri = web::uri_builder{}
		.set_scheme(U("http"))
		.set_host(U("localhost"))
		.set_port(port)
		.set_path(U("api"))
		.to_uri();

	util::startServer(uri);

#ifndef NDEBUG
	std::cout << "Server stopped\n";
#endif

	return 0;
}
