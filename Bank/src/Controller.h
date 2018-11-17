#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <cpprest/http_listener.h>

class Controller
{
public:
	explicit Controller(const utility::string_t& uri);

	auto endpoint() const { return _listener.uri().to_string(); }

	auto start() -> pplx::task<void>;

private:
	web::http::experimental::listener::http_listener _listener;

	using request = web::http::http_request;

	void handleGet(const request&) const;
	void handlePost(const request&) const;
	void handlePatch(const request&) const;
	void handleDelete(const request&) const;

	static auto parseRequestPath(const request& req)
	{
		return web::uri::split_path(web::uri::decode(req.relative_uri().path()));
	}
};

#endif
