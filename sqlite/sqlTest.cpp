#include "sql.h"

int main(int argc, char ** argv)
{
	Sql sql(std::string("zigbee.dbs"));
	std::cout << "main" << std::endl;
	sql.addIpsumPacket(std::string("url"), std::string("xml"));
	sql.executeQuery("SELECT * FROM ipsum_packets");

	
}
