#ifndef USER_ROUTER_H
#define USER_ROUTER_H

#include "IRouter.h"

class UserRouter : public IRouter
{
public:
	explicit UserRouter(const path_t& path) : IRouter {path} {}

private:
	void _handleGet	  (const request_t& req) const override { handleNotAllowed(req); }
	void _handlePost  (const request_t& req) const override;
	void _handlePatch (const request_t& req) const override { handleNotAllowed(req); }
	void _handleDelete(const request_t& req) const override { handleNotAllowed(req); }
};

#endif
