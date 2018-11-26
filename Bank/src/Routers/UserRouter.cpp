#include "UserRouter.h"
#include "../Utility/UtilityFunctions.h"

void UserRouter::_handlePost(const request_t& req) const
{
	const auto path = util::parseRequestPath(req);

	if (path.size() != 1 || path[0] != U("authorize"))
	{
		req.reply(web::http::status_codes::NotFound);
		return;
	}

	using web::json::value;

	req.extract_json()
	   .then([req](const pplx::task<value>& task)
	   {
			const auto body = task.get();

		    // TODO: pass json to something that will process it

			const auto response = body; // TODO: get real response
			const auto code = web::http::status_codes::OK; // TODO: get real code
			
		    return req.reply(code, response);
	   });
}
