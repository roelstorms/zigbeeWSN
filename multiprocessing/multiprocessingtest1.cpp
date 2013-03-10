#include <unistd.h>
#include <iostream>


int main (void)
{
	pid_t pid = fork();
	if(pid == 0)
	{
		std::cout << "child" << std::endl;
		for(int i = 0; i<100; ++i)
		{
			std::cout << "child count: "<< i << std::endl; 
		}

	}
	else if (pid == -1)
	{
		std::cout << "error" << std::endl;
	}
	else
	{
        	std::cout << "parent" << std::endl;
		for(int i = 0; i<100; ++i)
		{
			std::cout << "parent count: "<< i << std::endl; 
		}
	}


}
