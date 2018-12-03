#ifndef NOT_FOUND_H
#define NOT_FOUND_H

#include "IError.h"

class NotFound : public IError
{
public:
	explicit NotFound(const reason_t& reason) : IError {reason} {}

private:
	[[nodiscard]]
	auto _code() const noexcept -> const code_t& override
	{
		return web::http::status_codes::NotFound;
	}
};

#endif
