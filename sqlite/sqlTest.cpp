#include "sql.h"

int main(int argc, char ** argv)
{
	Sql sql(std::string("zigbee.dbs"));
	std::cout << "main" << std::endl;
	std::cout << "threadsafe: " << sqlite3_threadsafe();
	std::cout << "output: " << std::endl << sql.makeNewNode() << std::endl;

}
