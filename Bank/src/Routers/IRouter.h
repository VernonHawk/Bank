#ifndef IROUTER_H
#define IROUTER_H

#include <cpprest/http_msg.h>

class IRouter
{
protected:
	using request = web::http::http_request;

public:
	IRouter() = default;

	virtual ~IRouter() = 0;

	[[nodiscard]] 
	auto endpoint(const utility::string_t& uri) const noexcept { return _endpoint(uri); }

	void handleGet(const request& req)    const { _handleGet(req); }
	void handlePost(const request& req)   const { _handlePost(req); }
	void handlePatch(const request& req)  const { _handlePatch(req); }
	void handleDelete(const request& req) const { _handleDelete(req); }

	IRouter(const IRouter&) = delete;
	IRouter& operator=(const IRouter&) = delete;

	IRouter(IRouter&&) = delete;
	IRouter& operator=(IRouter&&) = delete;

private:
	virtual web::uri _endpoint(const utility::string_t&) const noexcept = 0;

	virtual void _handleGet(const request&)    const = 0;
	virtual void _handlePost(const request&)   const = 0;
	virtual void _handlePatch(const request&)  const = 0;
	virtual void _handleDelete(const request&) const = 0;
};

inline IRouter::~IRouter() = default;

#endif // IROUTER_H
