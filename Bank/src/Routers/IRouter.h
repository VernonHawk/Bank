#ifndef IROUTER_H
#define IROUTER_H

#include <cpprest/http_msg.h>
#include <utility>

class IRouter
{
protected:
	using request_t = web::http::http_request;
	using path_t    = utility::string_t;

public:
	using uri_t = web::uri;

	explicit IRouter(path_t path) noexcept : _path {std::move(path)} {};

	virtual ~IRouter() noexcept = default;

	void handleGet   (const request_t& req) const;
	void handlePost  (const request_t& req) const;
	void handlePatch (const request_t& req) const;
	void handleDelete(const request_t& req) const;

	[[nodiscard]]
	const path_t& path() const noexcept { return _path; }

	#pragma region deleted functions
	IRouter(const IRouter&) = delete;
	IRouter& operator=(const IRouter&) = delete;

	IRouter(IRouter&&) = delete;
	IRouter& operator=(IRouter&&) = delete;
	#pragma endregion 

protected:
	const path_t _path;

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

private:
	virtual void _handleGet   (const request_t&) const = 0;
	virtual void _handlePost  (const request_t&) const = 0;
	virtual void _handlePatch (const request_t&) const = 0;
	virtual void _handleDelete(const request_t&) const = 0;
};

#endif // IROUTER_H
