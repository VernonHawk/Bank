#include "UserRouter.h"

void UserRouter::_handleGet(const request& req) const
{
	using web::json::value;

	auto response = value::object();

	response[U("res")] = value::string(U("Hello from user endpoint"));

	req.reply(web::http::status_codes::OK, response);
}

void UserRouter::_handlePost(const request& req) const
{
	req.reply(web::http::status_codes::OK);
}

void UserRouter::_handlePatch(const request& req) const
{
	req.reply(web::http::status_codes::OK);
}

void UserRouter::_handleDelete(const request& req) const
{
	req.reply(web::http::status_codes::OK);
}
