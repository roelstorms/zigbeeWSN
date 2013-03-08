#include "http.h"
#include "../XML/XML.h"



int main(int argc, char * argv[])
{

	Http socket(std::string(""));
	socket.login();
	//socket.getEntity(socket.calculateDestination(21, 31, 320, 2029));
	socket.setUserRights("<?xml version=\"1.0\" encoding=\"utf-16\"?><Sensor><location></location><sensorgroupid>320</sensorgroupid><frequency>5</frequency><dataname>d7b2e54076c9249a4b4df8fa10be90d78</dataname><id>2029</id><name>LightSens1</name><description>a test sensor to see if this request works</description><inuse>True</inuse><infoname></infoname></Sensor>",21, 255);
	//socket.uploadData(2.1);
	/*	
		XML XMLParser;
		std::string url("/auth/");
		std::string temp;
		temp.append(url);
		url.append(socket.generateCode(temp.append("a31dd4f1-9169-4475-b316-764e1e737653")));

		socket.sendPost(url, XMLParser.login(std::string("roel"), std::string("roel")), &Http::loginReplyWrapper);
		std::string token = XMLParser.analyzeLoginReply("./log.txt");	
		url.clear();
	//url.append("/addInstall/");
	//url.append("/addGroup/");
	url.append("/addSensor/");
	//url.append("/addType/");
	//url.append("/upload");
	//url.append("/query/");
	url.append(token);
	url.append("/");
	//url.append(socket.calculateDestination(21, 31, 320, 2029));
	//url.append("/");

	temp.clear();
	temp.append(url);
	temp.append("a31dd4f1-9169-4475-b316-764e1e737653");
	url.append(socket.generateCode(temp));

	//socket.sendPost(url, XMLParser.createNewInstallation(std::string("GroepT"), std::string("a test installation to see if this request works"), std::string ("True")));

	//socket.sendPost(url, XMLParser.createNewSensorGroup(std::string("31"), std::string("Module 14"), std::string("a test sensor groep to see if this request works"), std::string ("True")));

	socket.sendPost(url, XMLParser.createNewSensor(std::string("320"), std::string("Module4LightSens"), std::string("d3bae7e83c3fd4165b90570163927da19"), std::string("a test sensor to see if this request works"), std::string ("True")), &Http::standardReplyWrapper);

	//socket.sendPost(url, XMLParser.createNewType(std::string("lightSensor"), std::string("intensity")));

	//std::pair<std::string, double> pair;
	//pair.first = std::string("field");
	//pair.second = 1.1;
	//std::vector<std::pair<std::string, double>> input;
	//input.push_back(pair);
	//pair.first = std::string("type2");
	//pair.second = 0.6;
	//input.push_back(pair);


	//socket.sendPost(url, XMLParser.uploadData(std::string("lightSensorRoel"), input));


	//std::string xml("<?xml version=\"1.0\" encoding=\"utf-8\"?><get><start>2012-01-01T00:00:00</start><end>9999-12-31T23:59:59</end><select><field><name>temperature</name></field></select></get>")*/;
	//socket.sendPost(url, xml);
	return 0;
}
