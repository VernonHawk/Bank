#ifndef INVALID_ARGUMENT_H
#define INVALID_ARGUMENT_H
#include "IError.h"

class InvalidArgument : public IError
{
public:
	explicit InvalidArgument(const reason_t& reason) : IError {reason} {}

private:
	[[nodiscard]]
	auto _code() const noexcept -> const code_t& override
	{
		return web::http::status_codes::PreconditionFailed;
	}
};

#endif
