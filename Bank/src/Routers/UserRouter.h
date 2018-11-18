#ifndef USER_ROUTER_H
#define USER_ROUTER_H

#include "IRouter.h"

class UserRouter : public IRouter
{
	[[nodiscard]] 
	web::uri _endpoint(const utility::string_t& uri) const noexcept override
	{
		return web::uri_builder {uri}.append_path(U("user")).to_uri();
	}

	void _handleGet(const request&) const override;
	void _handlePost(const request&) const override;
	void _handlePatch(const request&) const override;
	void _handleDelete(const request&) const override;
};

#endif
