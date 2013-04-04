#include "sql.h"
#include "../testclass.h"
int main(int argc, char ** argv)
{
	Sql sql(std::string("zigbee.dbs"));
	std::cout << "main" << std::endl;
	std::cout << "threadsafe: " << sqlite3_threadsafe();
	std::cout << "output: " << std::endl << sql.changeSensorInNode(132111, TEMP, 13) << std::endl;
	std::cout << sql.getNodeAddress(132111);
	TestClass::assert(sql.getNodeAddress(132111) == std::string("zigbee address"), "Testing Sql::getNodeAddress");
}
