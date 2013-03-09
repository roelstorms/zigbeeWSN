#include "XML.h"
#include <utility>

int main(int argc, char* argv[])
{
	XML XMLParser;
	std::cout << XMLParser.analyzeLoginReply(std::string("garbage")) << std::endl;
	std::cout << "end" << std::endl;

	return 0;	
}

