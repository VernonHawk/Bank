#ifndef SALT_GENERATOR_H
#define SALT_GENERATOR_H

#include <cpprest/asyncrt_utils.h>

class SaltGenerator
{
public:
	[[nodiscard]] static
	auto next() -> utility::string_t;

	// no need to be constructed
	SaltGenerator() = delete;

private:
	static size_t _counter;
};

#endif
