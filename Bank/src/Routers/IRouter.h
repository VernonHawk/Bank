#ifndef IROUTER_H
#define IROUTER_H

#include <cpprest/http_msg.h>

class IRouter
{
protected:
	using request_t = web::http::http_request;

	#pragma region other handlers
	static void handleNotAllowed(const request_t& req)
	{
		req.reply(web::http::status_codes::MethodNotAllowed);
	}

	static void handleInternalError(const request_t& req)
	{
		req.reply(web::http::status_codes::InternalError);
	}

	static void handleInternalError(const request_t& req, const std::exception& ex)
	{
		req.reply(web::http::status_codes::InternalError, ex.what());
	}
	#pragma endregion 

public:
	using uri_t = web::uri;

	IRouter() noexcept = default;

	virtual ~IRouter() noexcept = default;

	[[nodiscard]] 
	auto endpoint(const uri_t& uri) const { return _endpoint(uri); }

	void handleGet   (const request_t& req) const;
	void handlePost  (const request_t& req) const;
	void handlePatch (const request_t& req) const;
	void handleDelete(const request_t& req) const;

	#pragma region deleted functions
	IRouter(const IRouter&) = delete;
	IRouter& operator=(const IRouter&) = delete;

	IRouter(IRouter&&) = delete;
	IRouter& operator=(IRouter&&) = delete;
	#pragma endregion 

private:
	virtual uri_t _endpoint(const uri_t&) const = 0;

	virtual void _handleGet   (const request_t&) const = 0;
	virtual void _handlePost  (const request_t&) const = 0;
	virtual void _handlePatch (const request_t&) const = 0;
	virtual void _handleDelete(const request_t&) const = 0;
};

#endif // IROUTER_H
