#include "UtilityFunctions.h"

#include "../Controller.h"
#include "../Routers/BalanceRouter.h"
#include "../Routers/UserRouter.h"
#include "TerminationWaiter.h"

namespace util
{
	auto areParametersCorrect(
		const web::json::value& got, 
		const std::vector<utility::string_t>& expected
	) -> std::pair<bool, utility::string_t>
	{
		using std::to_wstring;

		if (got.size() != expected.size())
		{
			return { false, U("Expected ") + to_wstring(expected.size()) + 
							U(" parameters, but got ") + to_wstring(got.size()) + U('.')};
		}

		for (const auto& param : expected)
		{
			if (!got.has_field(param))
				return {false, U("Parameter ") + param + U(" is required but was not found.")};
		}

		return {true, U("")};
	}

	auto areParametersCorrect(
		const std::map<utility::string_t, utility::string_t>& got, 
		const std::vector<utility::string_t>& expected
	) -> std::pair<bool, utility::string_t>
	{
		auto jsonGot = web::json::value {};

		for (const auto& pair : got)
			jsonGot[pair.first] = web::json::value {pair.second};

		return areParametersCorrect(jsonGot, expected);
	}

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
}
