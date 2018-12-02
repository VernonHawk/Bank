#include "SaltGenerator.h"
#include "Hashing.h"

size_t SaltGenerator::_counter = 0;

auto SaltGenerator::next() -> utility::string_t
{
	namespace ch = std::chrono;

	const auto milis = ch::duration_cast<ch::milliseconds>(ch::system_clock::now().time_since_epoch()).count();

	return util::hash(std::to_wstring(milis + _counter++));
}
