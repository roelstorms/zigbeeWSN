
#include "sql.h"

int Sql::callbackWrapper(void *thisPointer, int argc, char **argv, char **azColName)
{

	return static_cast<Sql *>(thisPointer)->callback( argc,  argv, azColName);
}

int Sql::callback(int argc, char **argv, char **azColName)
{
	int i;
	for(i=0; i<argc; i++)
	{
		selectReturn.insert(std::pair<std::string, std::string>(std::string(azColName[i]), std::string(argv[i])));
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");

	return 0;
}

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

std::multimap<std::string, std::string> Sql::executeQuery(std::string aQuery)
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

std::multimap<std::string, std::string> Sql::retrieveIpsumPacket(std::string& url, std::string& XML)
{
	std::string query("SELECT FROM ipsum_packets (url, XML)");
	std::multimap<std::string, std::string> ipsumPacket = executeQuery(query);
	return ipsumPacket;
}	
