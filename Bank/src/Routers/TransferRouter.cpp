#include "TransferRouter.h"
#include "../BL/BusinessLogic.h"

void TransferRouter::_handlePatch(const request_t& req) const
{
	using web::http::status_codes;
	using web::json::value;

	req.extract_json()
		.then([req](const pplx::task<value>& task)
	{
		const auto body = task.get();

		auto resp = value {};

		const auto[correct, reason] = util::areParametersCorrect(body, {U("to"), U("from"), U("amount")});

		if (!correct)
		{
			resp[U("reason")] = value {reason};
			req.reply(status_codes::BadRequest, resp);
			return;
		}

		// TODO: pass body to something that will process it and get real response

		req.reply(status_codes::OK);
	});
}