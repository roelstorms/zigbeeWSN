#include "sql.h"


Sql::Sql(std::string dbName)
{
	int rc;
	rc = sqlite3_open(dbName.c_str(), &db);
	if( rc )
	{
		std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
		sqlite3_close(db);
	}
}

Sql::~Sql()
{
	sqlite3_close(db);
}

int Sql::callbackWrapper(void *thisPointer, int argc, char **argv, char **azColName)
{

	return static_cast<Sql *>(thisPointer)->callback( argc,  argv, azColName);
}

int Sql::callback(int argc, char **argv, char **azColName)
{
	int i;
	std::map<std::string, std::string> map;
	std::cout << "Sql::callback with argc: " << argc << std::endl;
	for(i=0; i<argc; i++)
	{
		map.insert(std::pair<std::string, std::string>(std::string(azColName[i]), std::string(argv[i] ? argv[i] : "NULL")));
		
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	selectReturn.push_back(map);
	printf("\n");

	return 0;
}


std::vector<std::map<std::string, std::string>> Sql::executeQuery(std::string aQuery)
{
	char *zErrMsg = 0;

	int rc = sqlite3_exec(db, aQuery.c_str(), &Sql::callbackWrapper, (void *) this, &zErrMsg);
	if( rc!=SQLITE_OK )
	{
		std::cerr << "SQL error: " << zErrMsg << std::endl;
	
		sqlite3_free(zErrMsg);
	}
	std::string output("");
	auto returnValue = selectReturn;
	selectReturn.clear();	
	return returnValue;

}

void Sql::addIpsumPacket(const std::string& url, const std::string& XML)
{
	std::string query("INSERT INTO ipsum_packets (url, XML) VALUES('");
	query.append(url);
	query.append("', '");
	query.append(XML);
	query.append("')");
	executeQuery(query);
}	

std::vector<std::map<std::string, std::string>> Sql::retrieveIpsumPacket()
{
	std::string query("SELECT *  FROM ipsum_packets");
	std::vector<std::map<std::string, std::string>> ipsumPacket = executeQuery(query);
	return ipsumPacket;
}

void  Sql::removeIpsumPacket(int id)
{
	std::string query("DELETE FROM ipsum_packets WHERE id = '");
	query.append(std::to_string(id));
	query.append("'");
	executeQuery(query);
}

std::string Sql::makeNewNode(int nodeID, std::string zigbee64bitAddress)
{

	std::string query("INSERT INTO nodes (nodeID, zigbee64bitaddress) VALUES(");
	query.append(nodeID + ", '" + zigbee64bitAddress);	
	query.append("')");
	std::cout << "query :" << query << std::endl;
	executeQuery(query);
	query.clear();
	query.append("SELECT * FROM nodes");
	auto vector = executeQuery(query);
	for(auto it = vector.begin(); it < vector.end(); ++it)
	{
		auto field = it->find("nodeID");
		if(field != it->end())
		{
			std::cout << "fieldname: " << field->first << "fieldvalue: " << field->second << std::endl;
		}
		field = it->find("zigbee64bitaddress");
		if(field != it->end())
		{
			std::cout << "fieldname: " << field->first << "fieldvalue: " << field->second << std::endl;
		}
	}
	std::string t("t");
	return vector.begin()->find("nodeID")->second;

}

	
std::string Sql::updateSensorsInNode(int nodeID, SensorType name, int sensorID)	
{
	std::string sensorName;
	switch(name)
	{
		case TEMP:
			sensorName = "temperatureID";
		break;	
		case HUM:
			sensorName = "humidityID";
		break;	
		case PRES:
			sensorName = "pressureID";
		break;	
		case BAT:
			sensorName = "batteryID";
		break;	
		case CO2:
			sensorName = "co2ID";
		break;	
		case ANEMO:
			sensorName = "anemoID";
		break;	
		case VANE:
			sensorName = "vaneID";
		break;	
		case PLUVIO:
			sensorName = "pluvioID";
		break;	

	}
	std::string query("UPDATE nodes SET " + sensorName + "=" + std::to_string(sensorID) + " WHERE nodeID=" + std::to_string(nodeID));
	executeQuery(query);
	return query;	
}


std::string Sql::getNodeAddress(int nodeID)
{
	std::string query("SELECT zigbee64bitaddress from  nodes WHERE nodeID = " + std::to_string(nodeID));
	auto data = executeQuery(query);
	for(auto it = data.begin(); it < data.end(); ++it)
	{
		auto field = it->find("zigbee64bitaddress");
		if(field != it->end())
		{
			return field->second;		
		}
		
	}
	return "Null";

}

#define CHECKSENSOR(name, sensortype)\
	 field = it->find(#name);\
	if(field != it->end())\
	{\
		if(field->second != std::string("-1"))\
		{\
			bool badCast = false;\
			int sensorID;\
			try\
			{\
				sensorID = boost::lexical_cast<int>(field->second);\
			}\
			catch(boost::bad_lexical_cast)\
			{\
				badCast = true;\
				std::cerr << "Nodes table contained a non number as SensorID, this sensor has been ignored" << std::endl;\
			}\
			if(!badCast)\
			{\
				sensors.insert(std::pair<SensorType,int>(sensortype, sensorID));\
			}\
		}\
	}

std::map<SensorType, int> Sql::getSensorsFromNode(int nodeID)
{
	std::string query("SELECT temperatureID, humidityID, pressureID, batteryID, co2ID, anemoID, vaneID, pluvioID  from  nodes WHERE nodeID = " + std::to_string(nodeID));
	auto data = executeQuery(query);
	std::cout << "data.size() " << data.size() << std::endl;
	if (data.size() != 1)
	{
		throw SqlError();
	}

	std::map<SensorType, int> sensors;
	auto it = data.begin();
	std::map<std::string, std::string>::iterator  field;
	CHECKSENSOR(temperatureID, TEMP)
	CHECKSENSOR(humidityID, HUM)
	CHECKSENSOR(pressureID, PRES)
	CHECKSENSOR(batteryID, BAT)
	CHECKSENSOR(co2ID, CO2)
	CHECKSENSOR(anemoID, ANEMO)
	CHECKSENSOR(vaneID, VANE)
	CHECKSENSOR(pluvioID, PLUVIO)
	/*	
	field = it->find("temperatureID");
	if(field != it->end())
	{
		if(field->second != std::string("-1"))
		{	
			sensors.insert(std::pair<SensorType,int>(TEMP, boost::lexical_cast<int>(field->second)));
		}	
	}
	*/	

	return sensors;

}



