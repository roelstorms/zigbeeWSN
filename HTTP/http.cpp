#include "http.h"

Http::Http(std::string urlBase): urlBase(urlBase)
{
	std::cout << "Http constructor" << std::endl;
  	curl = curl_easy_init();
}

Http::~Http()
{

	std::cout << "Http destructor" << std::endl;
	curl_easy_cleanup(curl);
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
	
	return output;
}

std::string Http::generateCode(std::string url)
{
	
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
    

	//printf("\nsha encoded: %x\n", output);
	//std::cout << "sha encoded: " <<  std::setw(2) << std::setfill('0') << std::hex << output << std::endl;
	std::cout << "sendPost" << std::endl;

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
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, Http::write_data); 
	//curl_easy_setopt(curl, CURLOPT_WRITEDATA, &internal_struct); 
	/* Perform the request, res will get the return code */
	result = curl_easy_perform(curl);
	/* Check for errors */
	if(result != CURLE_OK)
	fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(result));

	/* always cleanup */
	}
}

void Http::sendPost(std::string urlAddition, std::string data)
{
	CURLcode result;
	std::string url("http://ipsum.groept.be");
	url.append(urlAddition);	
	std::cout << "string used:" << std::endl << url << std::endl << std::endl;
	std::cout << "data sent: " << std::endl << data << std::endl << std::endl;
    	if(curl) {
	curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
	
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, Http::write_data); 

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
