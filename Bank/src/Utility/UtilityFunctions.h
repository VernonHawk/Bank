#ifndef UTILITY_FUNCTIONS_H
#define UTILITY_FUNCTIONS_H

#include "../Controller.h"
#include <cpprest/base_uri.h>
#include <cpprest/http_msg.h>

namespace util
{
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

	[[nodiscard]]
	auto areParametersCorrect(
		const web::json::value& got, 
		const std::vector<utility::string_t>& expected
	) -> std::pair<bool, utility::string_t>;

	[[nodiscard]]
	auto areParametersCorrect(
		const std::map<utility::string_t, utility::string_t>& got, 
		const std::vector<utility::string_t>& expected
	) -> std::pair<bool, utility::string_t>;

	void startServer(const Controller::uri_t&);
}

#endif
