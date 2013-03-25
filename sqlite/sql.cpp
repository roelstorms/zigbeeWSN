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
	for(i=0; i<argc; i++)
	{
		map.insert(std::pair<std::string, std::string>(std::string(azColName[i]), std::string(argv[i])));
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
	return selectReturn;

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

std::string Sql::makeNewNode()
{
	std::string nodeName;

	std::string query("INSERT INTO nodes (zigbee64bitadress, temperature, humidity, pressure, co2, battery) VALUES('zigbee address', 'true', 'true', 'true', 'true', 'true')");
	executeQuery(query);
	query.clear();
	query.append("SELECT id FROM nodes ORDER BY id DESC");
	auto vector = executeQuery(query);
	for(auto it = vector.begin(); it < vector.end(); ++it)
	{
		auto field = it->find("id");
		std::cout << "fieldname: " << field->first << "fieldvalue: " << field->second << std::endl;
	}
	return vector.begin()->find("id")->second;

	


}

