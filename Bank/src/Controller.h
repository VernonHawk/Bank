#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Routers/IRouter.h"
#include <cpprest/http_listener.h>

class Controller
{
public:
	Controller(const IRouter&, const utility::string_t&);

	~Controller() { _listener.close(); }

	auto endpoint() const { return _listener.uri().to_string(); }

	auto start() -> Controller&;

#pragma region deleted functions
	// We don't want a temporary Router
	Controller(const IRouter&&, const utility::string_t&) = delete;

	// Copy and move are not expected
	Controller(const Controller&) = delete;
	Controller& operator=(const Controller&) = delete;

	Controller(Controller&&) = delete;
	Controller& operator=(Controller&&) = delete;
#pragma endregion 

private:
	const IRouter* _router;
	
	web::http::experimental::listener::http_listener _listener;
	
	static auto parseRequestPath(const web::http::http_request& req)
	{
		return web::uri::split_path(web::uri::decode(req.relative_uri().path()));
	}
};

#endif
