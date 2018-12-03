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

	//helpers
	bool checkFormatNumber(std::string);
	bool checkFormatPIN(std::string);
	std::wstring s2ws(const std::string& s);
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

	void addUser(const std::string& name, const std::string& surname);
	void addAccount(unsigned int user_id, std::string number, std::string PIN);
	//void addTransaction(unsigned int from_id, unsigned int to_id, double amount, time_t  t = time(0));
	//void deleteAccount(unsigned int id);

	auto getCard(std::string number) -> std::optional<Card>;

	//void updatePIN(size_t account_id,);

	~DBHandler();
};