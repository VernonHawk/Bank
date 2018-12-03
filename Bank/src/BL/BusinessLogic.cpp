#include "BusinessLogic.h"
#include "../Errors/InternalError.h"
#include "../Errors/InvalidArgument.h"
#include "../Errors/NotFound.h"
#include "../Errors/CantAuthorize.h"
#include "../Utility/UtilityFunctions.h"
#include "../Utility/DBHandler.h"
#include "../Cryptography/Hashing.h"
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
		auto maybeCard = DBHandler::getInstance()->getCard(number);

		if (!maybeCard.has_value())
			return std::make_unique<NotFound>(U("number"));

		auto card = std::move(maybeCard.value());

		if (card.authTries() > Card::maxAuthTries)
			return std::make_unique<CantAuthorize>(U("auth tries"));

		if (util::hashPassword(pin, card.salt()) != card.pin())
		{
			card.incrementAuthTries();
			DBHandler::getInstance()->updateCard(card);

		    return std::make_unique<CantAuthorize>(U("pin"));
		}  

		card.resetAuthTries();
		DBHandler::getInstance()->updateCard(card);
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
		const auto maybeCard = DBHandler::getInstance()->getCard(number);

		if (!maybeCard.has_value())
			return std::make_unique<NotFound>(U("number"));

		return maybeCard.value().balance();
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
		auto maybeCard = DBHandler::getInstance()->getCard(number);

		if (!maybeCard.has_value())
			return std::make_unique<NotFound>(U("number"));

		if (maybeAmount.value() + maybeCard.value().balance() < 0)
			return std::make_unique<InvalidArgument>(U("balance"));

		maybeCard.value().addToBalance(maybeAmount.value());

		DBHandler::getInstance()->updateCard(maybeCard.value());
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
		const auto maybeFrom = DBHandler::getInstance()->getCard(from);

		if (!maybeFrom.has_value())
			return std::make_unique<NotFound>(U("from"));

		if (maybeAmount.value() + maybeFrom.value().balance() < 0)
			return std::make_unique<InvalidArgument>(U("balance"));

		const auto maybeTo = DBHandler::getInstance()->getCard(to);

		if (!maybeTo.has_value())
			return std::make_unique<NotFound>(U("to"));

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
