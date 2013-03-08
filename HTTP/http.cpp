#include "http.h"

Http::Http(std::string urlBase): urlBase(urlBase)
{
	std::cout << "Http constructor" << std::endl;
	curl = curl_easy_init();
	//token = nullptr;
}

Http::~Http()
{

	std::cout << "Http destructor" << std::endl;
	curl_easy_cleanup(curl);
	//token = nullptr;
}

size_t Http::read_data( void *ptr, size_t size, size_t nmemb, void *userdata)
{

	return size * nmemb;
}

size_t Http::write_data(void *buffer, size_t size, size_t nmemb, void *userp)
{
	std::ofstream myfile;
	myfile.open ("log.txt");
	myfile << std::string((char *)buffer);
	return size * nmemb;
}

size_t Http::loginReply(void *buffer, size_t size, size_t nmemb, void *userp)
{
	XML XMLParser;
	std::cout << "login reply is ready" << std::endl;	
	std::ofstream myfile;
	myfile.open ("loginReply");
	myfile << std::string((char *)buffer);
	std::cout << std::endl << "myfile: "  << myfile << std::endl;
	myfile.close();
	token = XMLParser.analyzeLoginReply("loginReply");
	return size * nmemb;
}

std::string Http::getCurrentTimestamp()
{
	std::string output;
	// formate: 2013-03-03T18:28:02
	boost::posix_time::ptime t(boost::posix_time::second_clock::universal_time());
	std::cout << "boost time" << boost::posix_time::to_iso_extended_string(t) << std::endl;	

	return output;
}

std::string Http::calculateDestination(int userID, int installationID, int sensorGroupID, int sensorID)
{
	std::string output;
	output.append(std::to_string(userID));
	output.append(":");
	output.append(std::to_string(installationID));
	output.append(":");
	output.append(std::to_string(sensorGroupID));
	output.append(":");
	output.append(std::to_string(sensorID));
	output.append(":");

	unsigned long int sec = time(NULL);
	std::cout << "time: " << std::endl << std::string(std::to_string(sec)) << std::endl;

	output.append(std::to_string(sec));
	output.append(":");

	int checksum = userID + installationID + sensorGroupID + sensorID + sec;
	std::string stringChecksum(std::to_string(checksum));
	std::cout << "long checksum:" << std::endl << stringChecksum << std::endl;
	std::string shortChecksum(stringChecksum.end()-6, stringChecksum.end());
	output.append(shortChecksum);

	std::string output2 = toBase64(output);
	std::cout << "destination base64 2:" << output2 << std::endl;
	return output2;
}


std::string Http::toBase64(std::string input)
{
	using namespace boost::archive::iterators;
	using namespace std;

	typedef transform_width< binary_from_base64<remove_whitespace<string::const_iterator> >, 8, 6 > it_binary_t;
	typedef insert_linebreaks<base64_from_binary<transform_width<string::const_iterator,6,8> >, 72 > it_base64_t;
	cout << "Your string is: '"<<input<<"'"<<endl;
	
	// Encode
	unsigned int writePaddChars = (3-input.length()%3)%3;
	string base64(it_base64_t(input.begin()),it_base64_t(input.end()));
	base64.append(writePaddChars,'=');

	cout << "Base64 representation: " << base64 << endl;

	return base64;
}

std::string Http::generateCode(std::string url)
{

	std::cout << std::endl << "generating code from url: " << std::endl << url << std::endl << std::endl;

	const unsigned char * input = (const unsigned char*) url.c_str();
	unsigned char * output =  (unsigned char *) malloc(sizeof(unsigned char) * 20);
	SHA1(input, url.size(), output);
	std::string code;
	char temp[20];
	for (int i = 0; i < 20; i++) 
	{
		//printf("%02x ", output[i]);
		sprintf(temp, "%02x", output[i]);
		code.append(temp);	

	}
	std::cout << std::endl << "code: " << code << std::endl;

	return code;
}

void Http::sendGet(std::string urlAddition)
{
	CURLcode result;
	std::string url("http://ipsum.groept.be");
	url.append(urlAddition);	
	std::cout << "string used:" << std::endl << url << std::endl << std::endl;
	if(curl) {
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		/* example.com is redirected, so we tell libcurl to follow redirection */
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
		curl_easy_setopt(curl, CURLOPT_HEADER, 0);
		curl_easy_setopt(curl, CURLOPT_VERBOSE, 0);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &Http::write_data); 
		//curl_easy_setopt(curl, CURLOPT_WRITEDATA, &internal_struct); 
		/* Perform the request, res will get the return code */
		result = curl_easy_perform(curl);
		/* Check for errors */
		if(result != CURLE_OK)
			fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(result));

		/* always cleanup */
	}
}

void Http::sendPost(std::string urlAddition, std::string data, size_t (Http::*callback) (void *, size_t, size_t, void *))
{
	CURLcode result;
	std::string url("http://ipsum.groept.be");
	url.append(urlAddition);	
	std::cout << "string used:" << std::endl << url << std::endl << std::endl;
	std::cout << "data sent: " << std::endl << data << std::endl << std::endl;
	if(curl) {
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());

		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, this->callback); 

		//curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
		//curl_easy_setopt(curl, CURLOPT_HEADER, 0);
		//curl_easy_setopt(curl, CURLOPT_VERBOSE, 0);

		/* Perform the request, res will get the return code */
		result = curl_easy_perform(curl);
		/* Check for errors */
		if(result != CURLE_OK)
			fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(result));

		/* always cleanup */
	}
}


void Http::uploadData(float data)
{
	std::string url;
	std::string temp;

	url.clear();
	url.append("/upload");
	url.append("/");
	url.append(calculateDestination(21, 31, 320, 2041));
	url.append("/");
	temp.clear();
	temp.append(url);
	temp.append("a31dd4f1-9169-4475-b316-764e1e737653");
	url.append(generateCode(temp));

	std::pair<std::string, double> pair;
	pair.first = std::string("intensity");
	pair.second = data;
	std::vector<std::pair<std::string, double>> input;
	input.push_back(pair);
	XML XMLParser;
	sendPost(url, XMLParser.uploadData(std::string("lightSensor"), input), &Http::write_data);

}

bool Http::login()
{
	std::string url("/auth/");
	std::string temp;
	temp.append(url);
	url.append(generateCode(temp.append("a31dd4f1-9169-4475-b316-764e1e737653")));
	
	XML XMLParser;
	sendPost(url, XMLParser.login(std::string("roel"), std::string("roel")), &Http::loginReply);

	return true;
}

std::string Http::getEntity(std::string destinationBase64)
{
/*	std::string url;
	std::string temp;

	url.clear();
	url.append("/entity");
	url.append("/");
	url.append(destinationBase64);
	url.append("/");
	temp.clear();
	temp.append(url);
	temp.append("a31dd4f1-9169-4475-b316-764e1e737653");
	url.append(generateCode(temp));

	std::pair<std::string, double> pair;
	pair.first = std::string("intensity");
	pair.second = data;
	std::vector<std::pair<std::string, double>> input;
	input.push_back(pair);

	sendPost(url, XMLParser.uploadData(std::string("lightSensor"), input));
*/
	std::string output;

	return output;	


}

void Http::setToken(std::string aToken)
{
	token = aToken;
}

