﻿#include <iostream>

#include "Controller.h"
#include "Routers/UserRouter.h"
#include "Utility/TerminationWaiter.h"

int main(const int argc, wchar_t* argv[])
{
	const auto host = utility::string_t {U("http://localhost:")};

	const auto port = argc == 2 ? argv[1] : U("1337");

	const auto api  = U("/api");

	const auto userRouter = UserRouter {};
	auto userController = Controller {userRouter, host + port + api};

	userController.start();

	util::TerminationWaiter::wait();

#ifndef NDEBUG
	std::cout << "Server stopped\n";
#endif

	return 0;
}
