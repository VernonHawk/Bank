﻿#include "UtilityFunctions.h"

#include "../Controller.h"
#include "../Routers/BalanceRouter.h"
#include "../Routers/UserRouter.h"
#include "TerminationWaiter.h"

namespace util
{
	void startServer(const Controller::uri_t& uri)
	{
		const auto userRouter    = UserRouter {U("user")};
		const auto balanceRouter = BalanceRouter {U("balance")};

		auto userController    = Controller {userRouter   , uri};
		auto balanceController = Controller {balanceRouter, uri};

		userController.start();
		balanceController.start();

		TerminationWaiter::wait();
	}

	std::wstring s2ws(const std::string& s)
	{
		std::wstring temp(s.length(), L' ');
		std::copy(s.begin(), s.end(), temp.begin());
		return temp;
	}
}
