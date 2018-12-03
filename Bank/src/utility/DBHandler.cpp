#include "DBHandler.h"
#include <algorithm>
#include "UtilityFunctions.h"

DBHandler* DBHandler::handler = 0;

DBHandler& DBHandler::connect() {

	if (connection != NULL) return *this;

	mysql_init(&mysql);
	this->connection = mysql_real_connect(&mysql, "localhost", "root", "Vaao095037448182", "bank", 3306, 0, 0);

	if (mysql_errno(&mysql)) throw new ErrorConnection(&mysql);

	return *this;
};


auto DBHandler::getCard(std::wstring& number) -> std::optional<Card> {
	connect();
	std::string req = "SELECT * FROM accounts where number = " + util::sw2s(number);
	mysql_query(connection, req.c_str());
	if (mysql_errno(&mysql)) throw ErrorConnection(&mysql);

	MYSQL_RES *result = mysql_store_result(connection);

	MYSQL_ROW row = mysql_fetch_row(result);

	return row ? std::optional<Card>{Card(atoi(row[0]), atoi(row[1]), util::s2ws(row[2]), util::s2ws(row[3]), util::s2ws(row[4]), strtod(row[5], 0), atoi(row[6]))} : std::nullopt;
}

void DBHandler::updateCard(const Card& card) {
	connect();
	std::string req = "UPDATE accounts SET balance = '" + std::to_string(card.balance()) + "', authorizationTries = '" 
		+ std::to_string(card.authTries()) + "' WHERE id = '" + std::to_string(card.id()) + '\'' ;
	mysql_query(connection, req.c_str());

	if (mysql_errno(&mysql)) throw ErrorConnection(&mysql);
};


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