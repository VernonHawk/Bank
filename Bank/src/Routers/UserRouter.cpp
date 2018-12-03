#include "UserRouter.h"
#include "../BL/BusinessLogic.h"
#include "../Errors/IError.h"
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

			auto resp = value {};

			const auto [correct, reason] = util::areParametersCorrect(body, {U("number"), U("pin")});

			if (!correct)
			{
			    resp[U("reason")] = value {reason};
			    req.reply(status_codes::BadRequest, resp);
			    return;
		    }

			const auto maybeError = tryAuthorize(
				body.at(U("number")).as_string(), body.at(U("pin")).as_string()
			);

		    if (maybeError.has_value()) // is error
		    {
			    resp[U("reason")] = value {maybeError.value()->reason()};
			    req.reply(maybeError.value()->code(), resp);
			    return;
		    }

		    req.reply(status_codes::OK);
	   });
}
