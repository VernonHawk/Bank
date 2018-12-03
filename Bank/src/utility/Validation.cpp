#include "Validation.h"
#include <cpprest/asyncrt_utils.h>
#include <cpprest/http_msg.h>
#include <cwctype>

namespace util
{
	auto areParametersCorrect(
		const web::json::value& got, const std::vector<u_string_t>& expected
	) -> std::pair<bool, u_string_t>
	{
		using std::to_wstring;

		if (got.size() != expected.size())
		{
			return {false, U("Expected ") + to_wstring(expected.size()) +
							U(" parameters, but got ") + to_wstring(got.size()) + U('.')};
		}

		for (const auto& param : expected)
		{
			if (!got.has_field(param))
				return {false, U("Parameter ") + param + U(" is required but was not found.")};
		}

		return {true, U("")};
	}

	auto areParametersCorrect(
		const std::map<u_string_t, u_string_t>& got, const std::vector<u_string_t>& expected
	) -> std::pair<bool, u_string_t>
	{
		auto jsonGot = web::json::value {};

		for (const auto& pair : got)
			jsonGot[pair.first] = web::json::value {pair.second};

		return areParametersCorrect(jsonGot, expected);
	}

	bool isValidDigitSequence(const u_string_t& seq, const size_t& size)
	{
		if (seq.size() != size)
			return false;

		for (auto c : seq)
		{
			if (!std::iswdigit(c))
				return false;
		}

		return true;
	}
	
}
