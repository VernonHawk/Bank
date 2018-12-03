#pragma once
#include "../Models/Card.h"
#include <mysql.h>
#include <string>
#include <iostream>
#include <ctime>
#include <optional>

class DBHandler
{
private:
	static DBHandler * handler;
	MYSQL *connection;
	MYSQL mysql;

	
	DBHandler() {}
	DBHandler(const DBHandler&) = delete;
	DBHandler& operator=(DBHandler&);

public:
	class ErrorConnection : public std::exception{
	private:
		std::string _message;
		size_t _code;
		ErrorConnection& operator=(const ErrorConnection&);
	public:
		ErrorConnection(MYSQL *mysql) :_message(mysql_error(mysql)), _code(mysql_errno(mysql)) {}
		~ErrorConnection() {};
		void printMessage() {
			std::cerr << _message << "; code: " << _code << std::endl;
		}
		const char * what() const throw ()
		{
			std::string str = _message + "; code: " + std::to_string(_code);
			return str.c_str();
		}
	};

	static DBHandler * getInstance() {
		if (!handler)
			handler = new DBHandler();
		return handler;
	}
	DBHandler& connect();

	//void addTransaction(unsigned int from_id, unsigned int to_id, double amount, time_t  t = time(0));
	//void deleteAccount(unsigned int id);

	auto getCard(const utility::string_t& number) -> std::optional<Card>;
	void updateCard(const Card&);
	void makeTransfer(const Card& from, const Card& to, double amount);

	//void updatePIN(size_t account_id,);

	~DBHandler();
};