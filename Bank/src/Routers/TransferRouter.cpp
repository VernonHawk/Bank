#include "TransferRouter.h"
#include "../BL/BusinessLogic.h"
#include "../Errors/IError.h"

void TransferRouter::_handlePatch(const request_t& req) const
{
	using web::http::status_codes;
	using web::json::value;

	req.extract_json()
		.then([req](const pplx::task<value>& task)
	{
		const auto body = task.get();

		auto resp = value {};

		const auto[correct, reason] = util::areParametersCorrect(body, {U("from"), U("to"), U("amount")});

		if (!correct)
		{
			resp[U("reason")] = value {reason};
			req.reply(status_codes::BadRequest, resp);
			return;
		}

		const auto maybeError = tryTransfer(
			body.at(U("from")).as_string(), body.at(U("to")).as_string(), body.at(U("amount")).as_string()
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