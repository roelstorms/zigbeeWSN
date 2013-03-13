#include "XML.h"
#include <utility>

int main(int argc, char* argv[])
{
	XML XMLParser;

	std::vector<std::string> fields;
	fields.push_back(std::string("field1"));
	fields.push_back(std::string("field2"));
	XMLParser.selectData(fields, XMLParser.getCurrentTimestamp() , XMLParser.getCurrentTimestamp());
	std::cout << XMLParser.getTimestamp(10, 30, 20, 2, 12, 1989) << std::endl;


	return 0;	
}

