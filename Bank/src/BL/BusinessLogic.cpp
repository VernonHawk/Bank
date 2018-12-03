#include "BusinessLogic.h"
#include "../Errors/InternalError.h"
#include "../Errors/InvalidArgument.h"
//#include "../Errors/NotFound.h"
//#include "../Errors/CantAuthorize.h"
//#include "../Models/Card.h"
#include "../Utility/UtilityFunctions.h"
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

auto tryChangeBalance(const utility::string_t& number, const utility::string_t& amount)
	-> std::optional<std::unique_ptr<IError>>
{
	if (!details::isCorrectNumber(number))
		return std::make_unique<InvalidArgument>(U("number"));

	const auto maybeAmount = util::tryParseNumber(amount);

	if (!maybeAmount.has_value())
		return std::make_unique<InvalidArgument>(U("amount"));

	try
	{
		//const auto maybeCard = getCard(number);

		//if (!maybeCard.has_value())
			//return std::make_unique<NotFound>(U("number"));

		// card.addToBalance(maybeAmount.value());

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

[[nodiscard]]
auto tryTransfer(const utility::string_t& from, const utility::string_t& to, const utility::string_t& amount)
 -> std::optional<std::unique_ptr<IError>>
{
	if (!details::isCorrectNumber(from))
		return std::make_unique<InvalidArgument>(U("from"));

	if (!details::isCorrectNumber(to))
		return std::make_unique<InvalidArgument>(U("to"));

	const auto maybeAmount = util::tryParseNumber(amount);

	if (!maybeAmount.has_value() || maybeAmount.value() < 1)
		return std::make_unique<InvalidArgument>(U("amount"));

	try
	{
		//const auto maybeFrom = getCard(from);

		//if (!maybeFrom.has_value())
			//return std::make_unique<NotFound>(U("from"));

		//const auto maybeTo = getCard(to);

		//if (!maybeTo.has_value())
			//return std::make_unique<NotFound>(U("to"));

		// makeTransfer(maybeFrom.value(), maybeTo.value(), maybeAmount.value());
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
