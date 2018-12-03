#ifndef ERROR_H
#define ERROR_H

#include <cpprest/http_msg.h>
#include <utility>

class IError
{
protected:
	using reason_t = utility::string_t;
	using code_t   = web::http::status_code;

public:
	explicit IError(reason_t reason) : _reason {std::move(reason)} {}

	#pragma region special functions
	virtual ~IError() noexcept = default;

	IError(const IError&) = default;
	IError(IError&&)      = default;

	IError& operator=(const IError&) = default;
	IError& operator=(IError&&)      = default;
	#pragma endregion 

	[[nodiscard]]
	const auto& reason() const noexcept { return _reason; }

	[[nodiscard]]
	const auto& code() const noexcept { return _code(); }

private:
	reason_t _reason;

	[[nodiscard]]
	virtual auto _code() const noexcept -> const code_t& = 0;
};

#endif
