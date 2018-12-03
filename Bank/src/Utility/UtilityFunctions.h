#ifndef UTILITY_FUNCTIONS_H
#define UTILITY_FUNCTIONS_H

#include "../Controller.h"
#include <cpprest/base_uri.h>
#include <cpprest/http_msg.h>
#include <optional>

namespace util
{
	[[nodiscard]]
	auto tryParseNumber(const utility::string_t&) -> std::optional<double>;

	[[nodiscard]] inline 
	auto parseRequestPath(const web::http::http_request& req)
	{
		return web::uri::split_path(req.relative_uri().path());
	}

	[[nodiscard]] inline 
	auto parseRequestQuery(const web::http::http_request& req)
	{
		return web::uri::split_query(req.relative_uri().query());
	}

	void startServer(const Controller::uri_t&);

	std::wstring s2ws(const std::string& s);
	std::string sw2s(const std::wstring& s);
}

#endif
