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
		   const auto json = task.get();

		   // TODO: do something with body

		   return req.reply(web::http::status_codes::OK, json);
	   });
}
