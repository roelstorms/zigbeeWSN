#include "http.h"

int main(int argc, char * argv[])
{
	Http socket(std::string(""));
	
	//socket.sendGet(std::string("sample/login"));	i
	std::string url("auth/");
	url.append(socket.generateCode(std::string("/auth/a31dd4f1-9169-4475-b316-764e1e737653")));

	socket.sendPost(url, std::string("<UserLogin><username>roel</username><password>roel</password></UserLogin>"));
	return 0;
}
