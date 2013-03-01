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
	url.append("/addType/");
	url.append(token);
	url.append("/");
	temp.clear();
	temp.append(url);
	temp.append("a31dd4f1-9169-4475-b316-764e1e737653");
	url.append(socket.generateCode(temp));
	//socket.sendPost(url, XMLParser.createNewInstallation(std::string("GroepT"), std::string("a test installation to see if this request works"), std::string ("True")));
	
	//socket.sendPost(url, XMLParser.createNewSensorGroup(std::string("31"), std::string("Module 14"), std::string("a test sensor groep to see if this request works"), std::string ("True")));

	//socket.sendPost(url, XMLParser.createNewSensor(std::string("320"), std::string("LightSens1"), std::string("a test sensor to see if this request works"), std::string ("True")));

	socket.sendPost(url, XMLParser.createNewType(std::string("lightSensor2"), std::string("lightSensorName2")));
	return 0;
}
