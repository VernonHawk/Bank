#include "Controller.h"
#include "utility/TerminationWaiter.h"

#include <string>

Controller::Controller(const utility::string_t& uri)
	: _listener {web::http::uri {uri}}
{
	using methods = web::http::methods;

	_listener.support(methods::GET  , std::bind(&Controller::handleGet, this, std::placeholders::_1));
	_listener.support(methods::POST , std::bind(&Controller::handlePost, this, std::placeholders::_1));
	_listener.support(methods::PATCH, std::bind(&Controller::handlePatch, this, std::placeholders::_1));
	_listener.support(methods::DEL  , std::bind(&Controller::handleDelete, this, std::placeholders::_1));
}

auto Controller::start() -> pplx::task<void>
{
	_listener.open().wait();

#ifndef NDEBUG
	std::wcout << "Server listening for requests at: " << endpoint() << '\n';
#endif

	util::TerminationWaiter::wait();

	return _listener.close();
}

#pragma region handlers
void Controller::handleGet(const request& req) const
{
	using web::json::value;

	auto response = value::object();

	response[U("res")] = value::string(U("Hello form bank"));

	req.reply(web::http::status_codes::OK, response);
}

void Controller::handlePost(const request& req) const
{
	req.reply(web::http::status_codes::OK);
}

void Controller::handlePatch(const request& req) const
{
	req.reply(web::http::status_codes::OK);
}

void Controller::handleDelete(const request& req) const
{
	req.reply(web::http::status_codes::OK);
}
#pragma endregion 
