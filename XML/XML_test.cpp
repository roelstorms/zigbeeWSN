#include "XML.h"
#include <utility>

int main(int argc, char* argv[])
{
	XML XMLParser;


	std::vector<std::pair<std::string, std::string>> aListOfFields;
	aListOfFields.push_back(std::pair<std::string, std::string>(std::string("namefield2"), std::string("decimal_ps_")));
	aListOfFields.push_back(std::pair<std::string, std::string>(std::string("namefield1"), std::string("float_n_")));
	std::cout << XMLParser.createNewType(std::string("aName"), aListOfFields) << std::endl;		
	return 0;	
}

