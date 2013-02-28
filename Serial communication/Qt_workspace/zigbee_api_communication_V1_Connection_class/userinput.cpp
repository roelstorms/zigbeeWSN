#include "userinput.h"

UserInput::UserInput(bool * a_stop) : stop(a_stop)
{
	std::cout << "stop in Userinput::UserInput: " << stop << std::endl;
}

UserInput::UserInput(const UserInput & source)
{
	stop = source.stop;
	std::cout << "stop in Userinput::UserInput CC: " << stop << std::endl;
}

UserInput::~UserInput()
{

}


void UserInput::operator() ()
{
	std::string input;
	std::cout << "UserInput::operator() ()" << std::endl;
	std::cout << "stop bool in UserInput: " << *stop << std::endl;
	while(input != std::string("quit"))
	{
		std::cin >> input;
		std::cout << "input: " << input << std::endl;
	}
	std::cout << "stop set to true" << std::endl;
	*stop = true;
}
