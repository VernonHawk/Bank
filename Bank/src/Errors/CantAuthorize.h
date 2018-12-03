#ifndef CANT_AUTHORIZE_H
#define CANT_AUTHORIZE_H

#include "IError.h"

class CantAuthorize : public IError
{
public:
	explicit CantAuthorize(const reason_t& reason) : IError {reason} {}

private:
	[[nodiscard]]
	auto _code() const noexcept -> const code_t& override
	{
		return web::http::status_codes::Forbidden;
	}
};

#endif
