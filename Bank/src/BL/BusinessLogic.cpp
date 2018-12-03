#include "BusinessLogic.h"
#include "../Errors/InternalError.h"
#include "../Errors/InvalidArgument.h"
#include <optional>

auto tryAuthorize(const utility::string_t& number, const utility::string_t& pin) 
	-> std::optional<std::unique_ptr<IError>>
{
	if (!details::isCorrectNumber(number))
		return std::make_unique<InvalidArgument>(U("number"));

	if (!details::isCorrectPin(pin))
		return std::make_unique<InvalidArgument>(U("pin"));

	try
	{
		// TODO: get data from db : 404

		// TODO: check authorize tries : 403
		// if (card.authTries() > Card::maxAuthTries)
		//	   return std::make_unique<CantAuthorize>(U("auth tries"));

		// TODO: hash pass and check it : 403
		// if (hash_password(pin, card.salt()) != card.pin())
		// {
		//	   increment card tries
		//     return std::make_unique<CantAuthorize>(U("pin"));
		// }  

		// TODO: set card tries to 0
	}
	catch (const std::exception&)
	{
		return std::make_unique<InternalError>(U("db"));
	}
	catch (...)
	{
		return std::make_unique<InternalError>(U("server"));
	}

	return {};
}
