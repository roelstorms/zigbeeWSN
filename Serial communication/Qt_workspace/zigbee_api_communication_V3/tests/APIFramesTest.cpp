#include "../APIFrames.h"	
#include "../connection.h"
#include "unistd.h"
#include "stdlib.h"

int main(int argc, char* argv[])
{
	
	Connection con(argv[1]);
	con.startInputHandler();
	std::vector<unsigned char> ATCommand(2, 0);
	std::vector<unsigned char> data(1,0);
	std::vector<unsigned char> empty(0,0);
	
	ATCommand.at(0) = 'N';
	ATCommand.at(1) = 'J';
	data.at(0) = 0x22;
	//data.at(1) = 0x0B;
	con.sendPacket( APIFrames::ATCommand(ATCommand, data, empty));
	ATCommand.at(0) = 'A';
	ATCommand.at(1) = 'C';
	//con.sendPacket( APIFrames::ATCommand(ATCommand, empty, empty));
	ATCommand.at(0) = 'W';
	ATCommand.at(1) = 'R';
	con.sendPacket( APIFrames::ATCommand(ATCommand, empty, empty));
	std::cout << "end" << std::endl;
	con.closeConnection();
	return 0;
}
