#ifndef VALIDATION_H
#define VALIDATION_H

#include <cpprest/asyncrt_utils.h>
#include <map>

namespace web::json { class value; }

namespace util
{
	using u_string_t = utility::string_t;

	[[nodiscard]]
	auto areParametersCorrect(
		const web::json::value& got, const std::vector<u_string_t>& expected
	) -> std::pair<bool, u_string_t>;

	[[nodiscard]]
	auto areParametersCorrect(
		const std::map<u_string_t, u_string_t>& got, const std::vector<u_string_t>& expected
	) -> std::pair<bool, u_string_t>;

	[[nodiscard]]
	bool isValidDigitSequence(const u_string_t& seq, const size_t& size);
}

#endif
