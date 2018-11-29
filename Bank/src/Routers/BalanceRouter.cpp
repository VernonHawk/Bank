#include "BalanceRouter.h"
#include "../Utility/UtilityFunctions.h"

void BalanceRouter::_handleGet(const request_t& req) const
{
	using web::http::status_codes;
	using web::json::value;

	auto resp = value {};

	const auto query = util::parseRequestQuery(req);

	if (query.size() != 1 || query.find(U("number")) == query.end())
	{
		resp[U("reason")] = value {U("Only one parameter 'number' is allowed and required.")};
		req.reply(status_codes::BadRequest, resp);
		return;
	}

	// TODO: pass code somewhere to process and get balance or error

	resp[U("balance")] = value {322}; // TODO: get real balance

	const auto code = status_codes::OK; // TODO: get real code

	req.reply(code, resp);
}

void BalanceRouter::_handlePatch(const request_t& req) const
{
	const auto code = web::http::status_codes::OK; // TODO: get real code

	req.reply(code);
}
