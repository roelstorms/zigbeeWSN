#include "sql.h"

int main(int argc, char ** argv)
{
	Sql sql(std::string("zigbee.dbs"));
	std::cout << "main" << std::endl;
	sql.removeIpsumPacket(10);

}
