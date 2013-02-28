#include "../APIFrames.h"	
#include "../connection.h"
#include "unistd.h"
#include "stdlib.h"

int main(int argc, char* argv[])
{
	
	Connection con(argv[1]);
	con.startInputHandler();
	std::vector<unsigned char> ATCommand(2, 0);
	std::vector<unsigned char> empty(0,0);
	ATCommand.at(0) = 'I';
	ATCommand.at(1) = 'D';
	con.sendPacket( APIFrames::ATCommand(ATCommand, ATCommand, empty));
	ATCommand.at(0) = 'A';
	ATCommand.at(1) = 'C';
	con.sendPacket( APIFrames::ATCommand(ATCommand, empty, empty));
	ATCommand.at(0) = 'F';
	ATCommand.at(1) = 'R';
	con.sendPacket( APIFrames::ATCommand(ATCommand, empty, empty));
	std::cout << "end" << std::endl;
	return 0;
}
