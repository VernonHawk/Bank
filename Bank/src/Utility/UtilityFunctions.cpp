﻿#include "UtilityFunctions.h"

#include "../Controller.h"
#include "../Routers/UserRouter.h"
#include "TerminationWaiter.h"

namespace util
{
	void startServer(const utility::string_t& uri)
	{
		const auto userRouter = UserRouter {};
		auto userController = Controller {userRouter, uri};

		userController.start();

		TerminationWaiter::wait();
	}
}
