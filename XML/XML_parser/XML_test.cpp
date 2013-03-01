#include "XML.h"
#include <utility>

int main(int argc, char* argv[])
{
	XML XMLParser;

//	std::pair<std::string, double> pair;
//	pair.first = std::string("type");
//	pair.second = 0;
//	std::vector<std::pair<std::string, double>> input;
//	input.push_back(pair);
//	pair.first = std::string("type2");
//	pair.second = 0.6;
//	input.push_back(pair);
//	XMLParser.uploadData(std::string("type"), input);

//	XMLParser.login(std::string("roel"), std::string("roel"));

//	std::cout << XMLParser.analyzeLoginReply(std::string("../../Curl/HTTP/log.txt")) << std::endl; 

	std::cout << XMLParser.createNewInstallation(std::string("name"), std::string("description"), std::string("True"));

//	XMLParser.createNewType(std::string("name"), std::string("newType"));
	return 0;	
}

