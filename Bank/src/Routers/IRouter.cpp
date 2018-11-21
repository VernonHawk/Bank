#include "IRouter.h"

void IRouter::handleGet(const request_t& req) const
{
	try
	{
		_handleGet(req);
	}
	catch (...)
	{
		handleInternalError(req);
	}
}

void IRouter::handlePost(const request_t& req) const
{
	try
	{
		_handlePost(req);
	}
	catch (...)
	{
		handleInternalError(req);
	}
}

void IRouter::handlePatch(const request_t& req) const
{
	try
	{
		_handlePatch(req);
	}
	catch (...)
	{
		handleInternalError(req);
	}
}

void IRouter::handleDelete(const request_t& req) const
{
	try
	{
		_handleDelete(req);
	}
	catch (...)
	{
		handleInternalError(req);
	}
}