#include "UserRouter.h"

void UserRouter::_handlePost(const request_t& req) const
{
	using web::json::value;

	auto response = value::object();

	response[U("res")] = value::string(U("Hello from user endpoint"));

	req.reply(web::http::status_codes::OK, response);
}
