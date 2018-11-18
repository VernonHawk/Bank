#ifndef IROUTER_H
#define IROUTER_H

#include <cpprest/http_msg.h>

class IRouter
{
protected:
	using request_t = web::http::http_request;

	static void handleNotAllowed(const request_t& req)
	{
		req.reply(web::http::status_codes::MethodNotAllowed);
	}

public:
	using uri_t = web::uri;

	IRouter() = default;

	virtual ~IRouter() = default;

	[[nodiscard]] 
	auto endpoint(const uri_t& uri) const noexcept { return _endpoint(uri); }

	void handleGet   (const request_t& req) const { _handleGet(req); }
	void handlePost  (const request_t& req) const { _handlePost(req); }
	void handlePatch (const request_t& req) const { _handlePatch(req); }
	void handleDelete(const request_t& req) const { _handleDelete(req); }

	IRouter(const IRouter&) = delete;
	IRouter& operator=(const IRouter&) = delete;

	IRouter(IRouter&&) = delete;
	IRouter& operator=(IRouter&&) = delete;

private:
	virtual uri_t _endpoint(const uri_t&) const noexcept = 0;

	virtual void _handleGet   (const request_t&) const = 0;
	virtual void _handlePost  (const request_t&) const = 0;
	virtual void _handlePatch (const request_t&) const = 0;
	virtual void _handleDelete(const request_t&) const = 0;
};

#endif // IROUTER_H
