#ifndef HASHING_H
#define HASHING_H

#include <cpprest/asyncrt_utils.h>

namespace util
{
	[[nodiscard]]
	auto hash(const utility::string_t&) -> utility::string_t;

	[[nodiscard]]
	auto hashPassword(const utility::string_t& pass) -> std::pair<utility::string_t, utility::string_t>;

	[[nodiscard]] inline
	auto hashPassword(const utility::string_t& pass, const utility::string_t& salt)
	{
		return hash(pass + salt);
	}
}

#endif
