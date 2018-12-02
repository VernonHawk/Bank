#pragma once
#include <mysql.h>
#include <string>
#include <iostream>

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
public:
	class ErrorConnection {
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
	};

	static DBHandler * getInstance() {
		if (!handler)
			handler = new DBHandler();
		return handler;
	}
	DBHandler& connect();

	void addUser(const std::string& name, const std::string& surname);
	void addAccount(unsigned int user_id, std::string number, std::string PIN);
	//void addTransaction(unsigned int from_id, unsigned int to_id, double amount, time_t date);
	//void deleteAccount(unsigned int id);


	//void updatePIN(size_t account_id,);

	~DBHandler();
};