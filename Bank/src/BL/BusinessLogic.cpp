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
	}
	catch (const std::exception&)
	{
		return std::make_unique<InternalError>(U("db"));
	}

	// check authorize tries  : 403

	// hash pass and check it : 403

	return {};
}
