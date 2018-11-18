#include "Controller.h"

#include <cassert>

Controller::Controller(const IRouter& router, const utility::string_t& uri)
	: _router {&router}, _listener {router.endpoint(uri)}
{
	assert(web::uri::validate(endpoint()));

	using methods = web::http::methods;

	_listener.support(methods::GET  , std::bind(&IRouter::handleGet   , _router, std::placeholders::_1));
	_listener.support(methods::POST , std::bind(&IRouter::handlePost  , _router, std::placeholders::_1));
	_listener.support(methods::PATCH, std::bind(&IRouter::handlePatch , _router, std::placeholders::_1));
	_listener.support(methods::DEL  , std::bind(&IRouter::handleDelete, _router, std::placeholders::_1));
}

auto Controller::start() -> Controller&
{
	_listener.open().wait();

#ifndef NDEBUG
	std::wcout << "Server listening for requests at: " << endpoint() << '\n';
#endif

	return *this;
}
