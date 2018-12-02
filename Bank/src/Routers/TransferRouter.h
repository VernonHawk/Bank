#ifndef TRANSFER_ROUTER_H
#define TRANSFER_ROUTER_H

#include "IRouter.h"

class TransferRouter : public IRouter
{
public:
	explicit TransferRouter(const path_t& path) : IRouter {path} {}

private:
	void _handleGet	  (const request_t& req) const override { handleNotAllowed(req); }
	void _handlePost  (const request_t& req) const override { handleNotAllowed(req); }
	void _handlePatch (const request_t& req) const override { handleNotAllowed(req); }
	void _handleDelete(const request_t& req) const override { handleNotAllowed(req); }
};

#endif
