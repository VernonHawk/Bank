#include "Hashing.h"
#include "SaltGenerator.h"
#include <iomanip>
#include <openssl/sha.h>
#include <sstream>

namespace util
{
	auto hash(const utility::string_t& str) -> utility::string_t
	{
		unsigned char hash[SHA256_DIGEST_LENGTH];

		auto sha256 = SHA256_CTX{};

		SHA256_Init(&sha256);
		SHA256_Update(&sha256, str.data(), str.size() * sizeof(utility::string_t::value_type));
		SHA256_Final(hash, &sha256);

		auto res = std::wstringstream {};

		for (auto c : hash)
			res << std::hex << std::setw(2) << std::setfill(U('0')) << static_cast<int>(c);

		return res.str();
	}

	auto hashPassword(const utility::string_t& pass) -> std::pair<utility::string_t, utility::string_t>
	{
		const auto salt = SaltGenerator::next();

		return {hashPassword(pass, salt), salt};
	}
}
