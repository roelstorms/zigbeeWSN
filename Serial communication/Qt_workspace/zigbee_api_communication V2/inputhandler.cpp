#include "inputhandler.h"

InputHandler::InputHandler(FILE * fd) : fileDescriptor(fd)
{

}

InputHandler::~InputHandler()
{

}

void InputHandler::operator() ()
{
	unsigned char input[255];
	unsigned char i ;
	std::cout << sizeof(unsigned char) << std::endl;
	while(1)
	    {
		//std::cout << "bytes read: " << read(fileDescriptor, input, 1) << std::endl;
		//fread(input, 1, 1, fileDescriptor);
		i = fgetc(fileDescriptor);
		//input[1] = '0';

		//std::string inputString(input);
		//std::cout << "input string:" << input;
		//if(i == 0x7e)
		{
			//printf("\n");
			

		}
		//else
		{
			
			
			printf("%x\n",  i);
			fflush(stdout);
		}
		//std::cout << i << std::endl ;
	    }	
}
