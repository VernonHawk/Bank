﻿#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Routers/IRouter.h"
#include <cpprest/http_listener.h>

class Controller
{
public:
	using uri_t = IRouter::uri_t;

	Controller(const IRouter&, const uri_t&);

	~Controller() noexcept { _listener.close(); }

	[[nodiscard]]
	auto endpoint() const { return _listener.uri().to_string(); }

	auto start() -> Controller&;

	#pragma region deleted functions
	// We don't want a temporary Router
	Controller(const IRouter&&, const uri_t&) = delete;

	Controller(const Controller&) = delete;
	Controller& operator=(const Controller&) = delete;

	Controller(Controller&&) = delete;
	Controller& operator=(Controller&&) = delete;
	#pragma endregion 

private:
	const IRouter* _router;
	
	web::http::experimental::listener::http_listener _listener;
};

#endif
