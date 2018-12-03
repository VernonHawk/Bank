#ifndef BUSINESS_LOGIC_H
#define BUSINESS_LOGIC_H

#include "../Utility/Validation.h"
#include <cpprest/details/basic_types.h>

void tryAuthorize(const utility::string_t& number, const utility::string_t& pin);

namespace details
{
	[[nodiscard]] inline
	bool isNumberCorrect(const utility::string_t& number)
	{
		return util::isValidDigitSequence(number, 16);
	}

	[[nodiscard]] inline
	bool isPinCorrect(const utility::string_t& pin)
	{
		return util::isValidDigitSequence(pin, 4);
	}
}

#endif
