#ifndef SQL_H
#define SQL_H
#include "sqlite3.h"
#include <stdio.h>
#include <iostream>
#include <string>
#include <map>
#include <utility>
#include <vector>
#include "../enums.h"

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

	
	//Table nodes: 	nodeID (int), zigbee64bitaddress(text), zigbee16bitaddress(text), temperatureID(int), humidityID(int), pressureID(int),
	//		batteryID (int), co2ID(int), anemoID(int), pluvioID(int)
	std::string makeNewNode(int nodeID, std::string zigbee64bitAddress);
	std::string changeSensorInNode(int nodeID, SensorType name, int sensorID);
	std::string getNodeAddress(int nodeID);	
};

#endif
