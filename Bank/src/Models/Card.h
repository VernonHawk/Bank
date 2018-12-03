#ifndef CARD_H
#define CARD_H

#include "../Utility/UtilityFunctions.h"
#include <utility>

class Card
{
	using u_string_t = utility::string_t;

public:
	constexpr static size_t maxAuthTries = 3;

	Card(
		const size_t id, const size_t userId, 
		u_string_t number, u_string_t pin, u_string_t salt,
	    const double balance, const size_t authTries
	)
		: _id {id}, _userId {userId}, 
		  _number {std::move(number)}, _pin {std::move(pin)}, _salt {std::move(salt)}, 
		  _balance {balance}, _authTries {authTries}
	{}

	#pragma region special functions
	~Card() = default;

	Card(const Card&) = delete;
	Card& operator=(const Card&) = delete;

	Card(Card&&) = default;
	Card& operator=(Card&&) = default;
	#pragma endregion

	#pragma region selectors
	[[nodiscard]]		auto  id()        const noexcept { return _id; }
	[[nodiscard]]		auto  userId()    const noexcept { return _userId; }
	[[nodiscard]] const auto& number()    const noexcept { return _number; }
	[[nodiscard]] const auto& pin()       const noexcept { return _pin; }
	[[nodiscard]] const auto& salt()      const noexcept { return _salt; }
	[[nodiscard]]		auto  balance()   const noexcept { return _balance; }
	[[nodiscard]]		auto  authTries() const noexcept { return _authTries; }
	#pragma endregion

	auto incrementAuthTries() noexcept { return ++_authTries; }
	auto resetAuthTries()     noexcept { return _authTries = 0; }

	auto addToBalance(const double change) noexcept { return _balance += change; }

private:
	size_t _id;
	size_t _userId;
	u_string_t _number;
	u_string_t _pin;
	u_string_t _salt;
	double _balance;
	size_t _authTries;
};

#endif
