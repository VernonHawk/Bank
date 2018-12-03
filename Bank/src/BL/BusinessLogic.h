﻿#ifndef BUSINESS_LOGIC_H
#define BUSINESS_LOGIC_H

#include "../Utility/Validation.h"
#include <cpprest/details/basic_types.h>
#include <optional>

class IError;

auto tryAuthorize(const utility::string_t& number, const utility::string_t& pin)
	-> std::optional<std::unique_ptr<IError>>;

namespace details
{
	[[nodiscard]] inline
	bool isCorrectNumber(const utility::string_t& number)
	{
		return util::isValidDigitSequence(number, 16);
	}

	[[nodiscard]] inline
	bool isCorrectPin(const utility::string_t& pin)
	{
		return util::isValidDigitSequence(pin, 4);
	}
}

#endif
