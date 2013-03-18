#ifndef SQL_H
#define SQL_H
#include "sqlite3.h"
#include <stdio.h>
#include <iostream>
#include <string>
#include <map>
#include <utility>

class Sql
{
	private:
	sqlite3 *db;	
	std::multimap<std::string, std::string> selectReturn;
	public:
	Sql(std::string dbName);
	~Sql();
	std::multimap<std::string, std::string> executeQuery(std::string aQuery);		
	static int callbackWrapper(void *thisPointer, int argc, char **argv, char **azColName);
	int callback(int argc, char **argv, char **azColName);
	void addIpsumPacket(const std::string& url, const std::string& XML);
	std::multimap<std::string, std::string> retrieveIpsumPacket(std::string& url, std::string& XML);
};

#endif
