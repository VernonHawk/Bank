﻿#include "UserRouter.h"
#include "../Utility/UtilityFunctions.h"

void UserRouter::_handlePost(const request_t& req) const
{
	using web::http::status_codes;

	const auto path = util::parseRequestPath(req);

	if (path.size() != 1 || path[0] != U("authorize"))
	{
		req.reply(status_codes::NotFound);
		return;
	}

	using web::json::value;

	req.extract_json()
	   .then([req](const pplx::task<value>& task)
	   {
			const auto body = task.get();

			const auto check = util::areParametersCorrect(body, {U("number"), U("pin")});

			auto resp = value {};

		    if (!check.first)
		    {
				resp[U("reason")] = value {check.second};
				req.reply(status_codes::BadRequest, resp);
				return;
		    }

		    // TODO: pass json to something that will process it and get real response

			const auto code = status_codes::OK; // TODO: get real code
			
		    req.reply(code, resp);
	   });
}
