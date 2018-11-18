#ifndef USER_ROUTER_H
#define USER_ROUTER_H

#include "IRouter.h"

class UserRouter : public IRouter
{
	[[nodiscard]] 
	uri_t _endpoint(const uri_t& uri) const override
	{
		return web::uri_builder {uri}.append_path(U("user")).to_uri();
	}

	void _handleGet	  (const request_t& req) const override { handleNotAllowed(req); }
	void _handlePost  (const request_t& req) const override;
	void _handlePatch (const request_t& req) const override { handleNotAllowed(req); }
	void _handleDelete(const request_t& req) const override { handleNotAllowed(req); }
};

#endif
