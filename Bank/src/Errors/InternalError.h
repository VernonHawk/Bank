#ifndef INTERNAL_ERROR_H
#define INTERNAL_ERROR_H

#include "IError.h"

class InternalError : public IError
{
public:
	explicit InternalError(const reason_t& reason) : IError {reason} {}

private:
	[[nodiscard]]
	auto _code() const noexcept -> const code_t& override
	{
		return web::http::status_codes::InternalError;
	}
};

#endif
