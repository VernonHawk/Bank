﻿#include "UtilityFunctions.h"

#include "../Controller.h"
#include "../Routers/BalanceRouter.h"
#include "../Routers/TransferRouter.h"
#include "../Routers/UserRouter.h"
#include "TerminationWaiter.h"

namespace util
{
	auto tryParseNumber(const utility::string_t& number) -> std::optional<double>
	{
		try
		{
			auto validCharsNum = size_t {};

			const auto res = std::stod(number, &validCharsNum);

			if (validCharsNum == number.size())
				return res;
		}
		catch (...)
		{}

		return {};
	}

	void startServer(const Controller::uri_t& uri)
	{
		const auto userRouter     = UserRouter {U("user")};
		const auto balanceRouter  = BalanceRouter {U("balance")};
		const auto transferRouter = TransferRouter {U("transfer")};

		auto userController     = Controller {userRouter    , uri};
		auto balanceController  = Controller {balanceRouter , uri};
		auto transferController = Controller {transferRouter, uri};

		userController.start();
		balanceController.start();
		transferController.start();

		TerminationWaiter::wait();
	}

	std::wstring s2ws(const std::string& s)
	{
		std::wstring temp(s.length(), L' ');
		std::copy(s.begin(), s.end(), temp.begin());

		return temp;
	}

	std::string sw2s(const utility::string_t& s) {
		std::string temp(s.length(), ' ');
		std::copy(s.begin(), s.end(), temp.begin());

		return temp;
	}
}
