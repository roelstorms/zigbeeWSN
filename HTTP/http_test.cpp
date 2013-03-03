#include "http.h"
#include "../XML/XML.h"

int main(int argc, char * argv[])
{
	Http socket(std::string(""));
	XML XMLParser;
	//socket.sendGet(std::string("sample/login"));	i
	std::string url("/auth/");
	std::string temp;
	temp.append(url);
	url.append(socket.generateCode(temp.append("a31dd4f1-9169-4475-b316-764e1e737653")));

	socket.sendPost(url, XMLParser.login(std::string("roel"), std::string("roel")));
      	std::string token = XMLParser.analyzeLoginReply("./log.txt");	
//	socket.sendPost(url, std::string("<UserLogin><username>roel</username><password>roel</password></UserLogin>"));
	url.clear();
	//url.append("/addInstall/");
	//url.append("/addGroup/");
	//url.append("/addSensor/");
	//url.append("/addType/");
	url.append("/upload");
	//url.append(token);
	url.append("/");
	url.append(socket.calculateDestination(21, 31, 320, 2029));
	url.append("/");

	temp.clear();
	temp.append(url);
	temp.append("a31dd4f1-9169-4475-b316-764e1e737653");
	url.append(socket.generateCode(temp));
	//socket.sendPost(url, XMLParser.createNewInstallation(std::string("GroepT"), std::string("a test installation to see if this request works"), std::string ("True")));
	
	//socket.sendPost(url, XMLParser.createNewSensorGroup(std::string("31"), std::string("Module 14"), std::string("a test sensor groep to see if this request works"), std::string ("True")));

	//socket.sendPost(url, XMLParser.createNewSensor(std::string("320"), std::string("LightSens1"), std::string("a test sensor to see if this request works"), std::string ("True")));

	//socket.sendPost(url, XMLParser.createNewType(std::string("lightSensor2"), std::string("lightSensorName2")));

	std::pair<std::string, double> pair;
	pair.first = std::string("field1");
	pair.second = 1.1;
	std::vector<std::pair<std::string, double>> input;
	input.push_back(pair);
	//pair.first = std::string("type2");
	//pair.second = 0.6;
	//input.push_back(pair);

	socket.sendPost(url, XMLParser.uploadData(std::string("ddd89535f0ea3489cb23d1417f7c8eeca"), input));
	


	return 0;
}
