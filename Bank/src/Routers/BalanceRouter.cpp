﻿#include "BalanceRouter.h"
#include "../BL/BusinessLogic.h"
#include "../Utility/UtilityFunctions.h"
#include "../Errors/IError.h"

void BalanceRouter::_handleGet(const request_t& req) const
{
	using web::http::status_codes;
	using web::json::value;

	auto resp = value {};

	const auto query = util::parseRequestQuery(req);
	const auto [correct, reason] = util::areParametersCorrect(query, {U("number")});

	if (!correct)
	{
		resp[U("reason")] = value {reason};
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
	using web::http::status_codes;
	using web::json::value;

	req.extract_json()
	   .then([req](const pplx::task<value>& task)
	   {
			const auto body = task.get();

			auto resp = value {};

			const auto [correct, reason] = util::areParametersCorrect(body, {U("number"), U("amount")});

			if (!correct)
			{
				resp[U("reason")] = value {reason};
				req.reply(status_codes::BadRequest, resp);
				return;
			}

			const auto maybeError = tryChangeBalance(
				body.at(U("number")).as_string(), body.at(U("amount")).as_string()
			);

			if (maybeError.has_value()) // is error
			{
				resp[U("reason")] = value {maybeError.value()->reason()};
				req.reply(maybeError.value()->code(), resp);
				return;
			}

			req.reply(status_codes::OK);
	   });
}
