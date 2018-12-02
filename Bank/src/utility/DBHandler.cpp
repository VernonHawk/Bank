#include "DBHandler.h"
#include <algorithm>
#include <ctime>


DBHandler* DBHandler::handler = 0;

DBHandler& DBHandler::connect() {

	if (connection != NULL) return *this;

	mysql_init(&mysql);
	this->connection = mysql_real_connect(&mysql, "localhost", "root", "Vaao095037448182", "bank", 3306, 0, 0);

	if (mysql_errno(&mysql)) throw new ErrorConnection(&mysql);

	return *this;
};

void DBHandler::addUser(const std::string& name, const std::string& surname) {
	connect();
	mysql_real_query(&mysql, "BEGIN",6);

	std::string q = "INSERT INTO users SET name = \"" + name + "\", surname = \""+surname+"\"";
	mysql_query(&mysql,	q.c_str());
	//commit transaction
	mysql_real_query(&mysql, "COMMIT",6);

	if (mysql_errno(&mysql)) throw ErrorConnection(&mysql);
}

void DBHandler::addAccount(unsigned int user_id, std::string number, std::string PIN) {
	connect();
	//check data
	if(!checkFormatNumber(number)) return;
	if(!checkFormatPIN(PIN)) return;

	mysql_real_query(&mysql, "BEGIN", 6);
	std::string q = "INSERT INTO accounts SET userId = \"" + std::to_string(user_id) + "\", number = \"" 
		+ number + "\", PIN = \"" + PIN + "\",salt = \""+"some salt" + "\",balance = 0.0, authorizationTries = 0";//TODO
	mysql_query(&mysql, q.c_str());
	//commit transaction
	mysql_real_query(&mysql, "COMMIT", 6);

	if (mysql_errno(&mysql)) throw ErrorConnection(&mysql);
}


DBHandler::~DBHandler() {
	mysql_close(&mysql);
}


//-----------------------------------------------

bool DBHandler::checkFormatNumber(std::string number) {
	number.erase(std::remove(number.begin(), number.end(), ' '), number.end());
	if (number.length() != 16) return 0;
	for (size_t i = 0; i < 16; i++)
		if (number[i] > '9' || number[i] < '0') return 0;
	return 1;
}
bool DBHandler::checkFormatPIN(std::string number) {
	if (number.length() != 4) return 0;
	for (size_t i = 0; i < 4; i++)
		if (number[i] > '9' || number[i] < '0') return 0;
	return 1;
}