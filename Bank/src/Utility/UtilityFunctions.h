#ifndef UTILITY_FUNCTIONS_H
#define UTILITY_FUNCTIONS_H

#include "../Controller.h"
#include <cpprest/base_uri.h>
#include <cpprest/http_msg.h>

namespace util
{
	inline auto parseRequestPath(const web::http::http_request& req)
	{
		return web::uri::split_path(req.relative_uri().path());
	}

	void startServer(const Controller::uri_t&);
}

#endif
