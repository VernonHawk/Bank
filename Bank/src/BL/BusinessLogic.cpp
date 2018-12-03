#include "BusinessLogic.h"
#include "../Errors/InternalError.h"
#include "../Errors/InvalidArgument.h"
//#include "../Errors/NotFound.h"
//#include "../Errors/CantAuthorize.h"
#include "../Models/Card.h"
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
		//const auto maybeCard = getCard(number);

		//if (!maybeCard.has_value())
			//return std::make_unique<NotFound>(U("number"));

		// if (maybeCard.value().authTries() > Card::maxAuthTries)
			// return std::make_unique<CantAuthorize>(U("auth tries"));

		// if (hash_password(pin, card.salt()) != card.pin())
		// {
		//	   card.incrementAuthTries();
		//	   updateCard(card);

		//     return std::make_unique<CantAuthorize>(U("pin"));
		// }  

		// card.resetAuthTries();
		// updateCard(card);
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

auto tryGetBalance(const utility::string_t& number) -> std::variant<double, std::unique_ptr<IError>>
{
	if (!details::isCorrectNumber(number))
		return std::make_unique<InvalidArgument>(U("number"));

	try
	{
		//const auto maybeCard = getCard(number);

		//if (!maybeCard.has_value())
			//return std::make_unique<NotFound>(U("number"));

		// return maybeCard.value().balance();
		return 0; 
	}
	catch (const std::exception&)
	{
		return std::make_unique<InternalError>(U("db"));
	}
	catch (...)
	{
		return std::make_unique<InternalError>(U("server"));
	}
}

