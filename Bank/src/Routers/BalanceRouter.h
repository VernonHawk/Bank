#ifndef BALANCE_ROUTER_H
#define BALANCE_ROUTER_H

#include "IRouter.h"

class BalanceRouter : public IRouter
{
public:
	explicit BalanceRouter(const path_t& path) : IRouter {path} {}

private:
	void _handleGet	  (const request_t& req) const override;
	void _handlePost  (const request_t& req) const override { handleNotAllowed(req); }
	void _handlePatch (const request_t& req) const override;
	void _handleDelete(const request_t& req) const override { handleNotAllowed(req); }
};

#endif
