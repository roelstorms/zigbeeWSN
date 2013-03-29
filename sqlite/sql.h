#ifndef SQL_H
#define SQL_H
#include "sqlite3.h"
#include <stdio.h>
#include <iostream>
#include <string>
#include <map>
#include <utility>
#include <vector>

class Sql
{
	private:
	sqlite3 *db;	
	std::vector<std::map<std::string, std::string>> selectReturn;
	public:
	Sql(std::string dbName);
	~Sql();
	static int callbackWrapper(void *thisPointer, int argc, char **argv, char **azColName);
	int callback(int argc, char **argv, char **azColName);
	std::vector<std::map<std::string, std::string>> executeQuery(std::string aQuery);		
	void addIpsumPacket(const std::string& url, const std::string& XML);
	std::vector<std::map<std::string, std::string>> retrieveIpsumPacket();
	void removeIpsumPacket(int id);
	std::string makeNewNode();	//Table nodes: ID (
	//void addNode(std::string zbAddress, std::string nodeIdentifier, std::string ipsumName);
};

#endif
