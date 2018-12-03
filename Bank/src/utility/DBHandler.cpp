#include "DBHandler.h"
#include <algorithm>


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

auto DBHandler::getCard(std::string number) -> std::optional<Card> {
	connect();
	std::string req = "SELECT * FROM accounts where number = " + number;
	mysql_query(connection, req.c_str());
	if (mysql_errno(&mysql)) throw ErrorConnection(&mysql);

	MYSQL_RES *result = mysql_store_result(connection);

	MYSQL_ROW row = mysql_fetch_row(result);

	return row ? std::optional<Card>{Card(atoi(row[0]), atoi(row[1]), s2ws(row[2]), s2ws(row[3]), s2ws(row[4]), strtod(row[5], 0), atoi(row[6]))} : std::nullopt;
}

std::wstring DBHandler::s2ws(const std::string& s)
{
	std::wstring temp(s.length(), L' ');
	std::copy(s.begin(), s.end(), temp.begin());
	return temp;
}


//void DBHandler::addTransaction(unsigned int from_id, unsigned int to_id, double amount, time_t  t) {
//	connect();
//
//	std::tm* time = std::localtime(&t);
//
//	mysql_real_query(&mysql, "BEGIN", 6);
//	std::string q = "INSERT INTO accounts SET fromId = \"" + std::to_string(from_id) + "\", toId = \""
//		+ std::to_string(to_id) + "\", amount = \"" + std::to_string(amount) + "\",date = \"" 
//		+ std::to_string(time->tm_year + 1900) + '-' + std::to_string(time->tm_mon + 1) + '-' 
//		+ std::to_string(time->tm_mday) + ' '+ std::to_string(time->tm_hour) + ':' + std::to_string(time->tm_min)
//		+ ':' + std::to_string(time->tm_sec);
//	std::cout << q << std::endl;
//	mysql_query(&mysql, q.c_str());
//	//commit transaction
//	mysql_real_query(&mysql, "COMMIT", 6);
//
//	if (mysql_errno(&mysql)) throw ErrorConnection(&mysql);
//}

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