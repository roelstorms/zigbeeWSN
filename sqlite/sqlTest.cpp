#include "sql.h"

int main(int argc, char ** argv)
{
	Sql sql(std::string("zigbee.dbs"));
	std::cout << "main" << std::endl;
	sql.addIpsumPacket("/login/auth/", "<user>roel</user><password>roel</password>");
	std::vector<std::map<std::string, std::string>> ipsumPackets = sql.retrieveIpsumPacket();	
	for(auto packet : ipsumPackets)
	{
		for(auto field : packet)
		{
			std::cout << "fieldname: " << field.first << "fieldvalue: " << field.second << std::endl;
		}
		
		std::cout << "found xml: " << packet.find(std::string("XML"))->second << std::endl;
	}
}
