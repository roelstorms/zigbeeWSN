#include "http.h"

Http::Http(std::string urlBase): urlBase(urlBase)
{
	std::cout << "Http constructor" << std::endl;
	curl_global_init(CURL_GLOBAL_ALL);
	token = std::string();
	httpError = -1;
}

Http::~Http()
{
	curl_global_cleanup();
	std::cout << "Http destructor" << std::endl;
}

//Currently not in use
size_t Http::read_data( void *ptr, size_t size, size_t nmemb)
{

	return size * nmemb;
}

size_t Http::loginReplyWrapper(void *buffer, size_t size, size_t nmemb, void *obj)
{
	std::cout << "loginReplyWrapper" << std::endl;
	return static_cast<Http*>(obj)->loginReply(buffer, size, nmemb);
}

size_t Http::loginReply(void *buffer, size_t size, size_t nmemb)
{
	curlReply = std::string((char *)buffer);
	return size * nmemb;
}

size_t Http::standardReplyWrapper(void *buffer, size_t size, size_t nmemb, void *obj)
{
	std::cout << "standardReplyWrapper" << std::endl;
	return static_cast<Http*>(obj)->write_data(buffer, size, nmemb);
}

size_t Http::write_data(void *buffer, size_t size, size_t nmemb)
{
	std::cout << "write_data" << std::endl;
	curlReply = std::string((char *)buffer);

	return size * nmemb;
}

size_t Http::headerHandlerWrapper(void *buffer, size_t size, size_t nmemb, void *obj)
{
	std::cout << "Http::headerHandlerWrapper" << std::endl << std::endl;
	return static_cast<Http*>(obj)->headerHandler(buffer, size, nmemb);
}

size_t Http::headerHandler(void *buffer, size_t size, size_t nmemb)
{
	std::string header((char *) buffer);
	if(header.find(std::string("HTTP/1.1 ")) != std::string::npos)
	{
		httpError = boost::lexical_cast<int>(header.substr(header.find(std::string("HTTP/1.1 ")) + 9, 3));
	}
	return size * nmemb;
}



std::string Http::sendGet(std::string urlAddition, size_t (*callback) (void*, size_t, size_t, void*)) throw (HttpError)
{
	curl = curl_easy_init();

	std::cout << "sendGet" << std::endl;

	CURLcode result;
	std::string url(urlBase);
	url.append(urlAddition);	
	std::cout << "string used:" << std::endl << url << std::endl << std::endl;
	if(curl) {
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		/* example.com is redirected, so we tell libcurl to follow redirection */
		//curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
		
		curl_easy_setopt(curl, CURLOPT_HEADER, 1);			// Enables the output of header information
		curl_easy_setopt(curl, CURLOPT_WRITEHEADER, this);		// Give this as a paramater to the HEADERFUNCTION
 		curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, headerHandlerWrapper);		// set headerHandlerWrapper as a callbackfunction to parse header information

		curl_easy_setopt(curl, CURLOPT_VERBOSE, 0);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, this);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback); 
		/* Perform the request, res will get the return code */
		result = curl_easy_perform(curl);
		/* Check for errors */
		if(result != CURLE_OK)
		{
			fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(result));
			throw HttpError();
		}		
		/* always cleanup */
	}
	curl_easy_cleanup(curl);
	return curlReply;
}

std::string Http::sendPost(std::string urlAddition, std::string data, size_t (*callback) (void *, size_t, size_t, void *)) throw (HttpError)
{
	curl = curl_easy_init();

	std::cout << "sendPost" << std::endl;
	CURLcode result;
	std::string url(urlBase);
	url.append(urlAddition);	
	std::cout << "string used:" << std::endl << url << std::endl << std::endl;
	std::cout << "data sent: " << std::endl << data << std::endl << std::endl;
	if(curl) {
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());

		curl_easy_setopt(curl, CURLOPT_WRITEDATA, this);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);
		
		curl_easy_setopt(curl, CURLOPT_HEADER, 1);			// Enables the output of header information
		curl_easy_setopt(curl, CURLOPT_WRITEHEADER, this);		// Give this as a paramater to the HEADERFUNCTION
 		curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, headerHandlerWrapper);		// set headerHandlerWrapper as a callbackfunction to parse header information

		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
		curl_easy_setopt(curl, CURLOPT_VERBOSE, 0);

		/* Perform the request, res will get the return code */

		result = curl_easy_perform(curl);
		/* Check for errors */
		if(result != CURLE_OK)
		{	
			fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(result));
			throw HttpError();
		}
		/* always cleanup */
	}
	std::cout << "end of sendpost" << std::endl;
	curl_easy_cleanup(curl);

	return curlReply;

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
	delete output;
	return code;
}


std::string Http::calculateDestination(int userID, int installationID, int sensorGroupID, int sensorID)
{
	std::string output;
	output.append(std::to_string(userID));

	int checksum = userID;

	if(installationID != -1)
	{
		output.append(":");
		output.append(std::to_string(installationID));
		checksum += installationID;
	}

	if(sensorGroupID != -1)
	{
		output.append(":");
		output.append(std::to_string(sensorGroupID));
		checksum += sensorGroupID;
	}

	if(sensorID != -1)
	{
		output.append(":");
		output.append(std::to_string(sensorID));
		checksum += sensorID;
	}
	output.append(":");

	unsigned long int sec = time(NULL);
	std::cout << "time: " << std::endl << std::string(std::to_string(sec)) << std::endl;
	checksum += sec;
	output.append(std::to_string(sec));
	output.append(":");

	std::string stringChecksum(std::to_string(checksum));
	std::cout << "long checksum:" << std::endl << stringChecksum << std::endl;
	std::string shortChecksum(stringChecksum.end()-6, stringChecksum.end());
	std::cout << "short checksum" << std::endl << shortChecksum << std::endl;
	output.append(shortChecksum);

	std::string output2 = toBase64(output);
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




void Http::uploadData(std::string aSensorType, std::string destinationBase64, std::vector<std::pair<std::string, double>> input) throw (HttpError)
{
	std::string url;
	std::string temp;
	std::cout << "Http::uploadData" << std::endl;

	login();

	url.clear();
	url.append("/upload");
	url.append("/");
	url.append(destinationBase64);
	url.append("/");
	temp.clear();
	temp.append(url);
	temp.append("a31dd4f1-9169-4475-b316-764e1e737653");
	url.append(generateCode(temp));
	
	XML XMLParser;
	httpError = -1;
	sendPost(url, XMLParser.uploadData(aSensorType, input), &Http::standardReplyWrapper);
	if(httpError != 200)
	{
		throw HttpError();
	}
}

bool Http::login() throw (HttpError, InvalidLogin)
{
	if(token.empty() || tokenExpireTime <= boost::posix_time::second_clock::universal_time())
	{
		std::string url("/auth/");
		std::string temp;
		temp.append(url);
		url.append(generateCode(temp.append("a31dd4f1-9169-4475-b316-764e1e737653")));

		XML XMLParser;
		httpError = -1;	
		std::ofstream myfile;
		myfile.open ("loginReply");
		myfile << sendPost(url, XMLParser.login(std::string("roel"), std::string("roel")), &Http::loginReplyWrapper);
		myfile.close();
		if(httpError != 200)
		{
			throw HttpError();
		}

		token = XMLParser.analyzeLoginReply("loginReply");
		std::cout << "token calculated from login reply:  " << token << std::endl;

		if (token.empty())
		{
			std::cerr << "Login failed, reply contained error = true" << std::endl;
			throw InvalidLogin();
			return false;
		}
		else
		{
			tokenExpireTime = boost::posix_time::ptime (boost::posix_time::second_clock::universal_time() + boost::posix_time::minutes(30));
			std::cout << "tokenExpireTime: " << boost::posix_time::to_simple_string(tokenExpireTime) << std::endl;
		}
	}
	return true;
}
void Http::setUserRights(std::string entity, int userID, int rights) throw (HttpError)
{
	std::cout << "Http::setUserRights" << std::endl;
	
	login();
	
	std::string url;
	std::string temp;
	
	// url format for entity: entity/{token}/{destination}/{code}
	url.clear();
	url.append("/setUser/");
	url.append(std::to_string(userID) );
	url.append(":");
	url.append(std::to_string(rights));
	url.append("/");
	url.append(token);		
	url.append("/");
	temp.clear();
	temp.append(url);
	temp.append("a31dd4f1-9169-4475-b316-764e1e737653");
	url.append(generateCode(temp));
	sendPost(url, entity, &Http::standardReplyWrapper);

}

std::string Http::getEntity(std::string destinationBase64) throw (HttpError)
{

	std::cout << "Http::getEntity" << std::endl;
	XML XMLParser;

	login();
	
	std::string url;
	std::string temp;
	
	// url format for entity: entity/{token}/{destination}/{code}
	url.clear();
	url.append("/entity/");
	url.append(token);		
	url.append("/");
	url.append(destinationBase64);
	url.append("/");
	temp.clear();
	temp.append(url);
	temp.append("a31dd4f1-9169-4475-b316-764e1e737653");
	url.append(generateCode(temp));
	return sendGet(url, &Http::standardReplyWrapper);
	

}

void Http::setToken(std::string aToken)
{
	token = aToken;
}

std::string Http::selectData(std::string destinationBase64, std::vector<std::string> fields) throw (HttpError)

{

	std::cout << std::endl << "Http::selectData" << std::endl << std::endl;
	XML XMLParser;

	login();

	std::string url;
	std::string temp;
	
	// url format for entity: select/{token}/{destination}/{code}
	url.clear();
	url.append("/select/");
	url.append(token);		
	url.append("/");
	
	url.append(destinationBase64);

	url.append("/");
	temp.clear();
	temp.append(url);
	temp.append("a31dd4f1-9169-4475-b316-764e1e737653");
	url.append(generateCode(temp));

	
	return sendPost(url, XMLParser.selectData(fields,  XMLParser.getTimestamp(1, 0, 0, 1, 3, 2013), XMLParser.getCurrentTimestamp()), &Http::standardReplyWrapper);
	//sendPost(url, "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n<get>\n<start>2012-01-01T00:00:00</start>\n<end>9999-12-31T23:59:59</end>\n<select>\n<field>\n<name>intensity</name>\n</field>\n</select>\n</get>", &Http::standardReplyWrapper);



}


std::string Http::testQuery() throw (HttpError)

{
	std::string url, temp;
	// url format for entity: entity/{token}/{destination}/{code}
	url.append("/SecureEcho/");
	url.append(calculateDestination(21, 31));//, 320, 2041));
	url.append("/");
	temp.clear();
	temp.append(url);
	temp.append("a31dd4f1-9169-4475-b316-764e1e737653");
	url.append(generateCode(temp));

	
	//sendPost(url, XMLParser.selectData(fields), &Http::standardReplyWrapper);
	sendPost(url, "<get><start>2012-01-01T00:00:00</start><end>9999-12-31T23:59:59</end><select><field><function></function><name>intensity</name></field><operation></operation><as></as></select></get>", &Http::standardReplyWrapper);




	std::string output;
	return output;
}

std::string Http::ipsumInfo() throw (HttpError)
{
	std::string url;
	url.append("/info");

	return sendGet(url, &Http::standardReplyWrapper);
}

std::string Http::createNewSensor(std::string sensorGroupIDValue, std::string nameValue, std::string dataNameValue, std::string descriptionValue, std::string inuseValue) throw (HttpError)
{
	XML XMLParser;
	
	login();

	std::string url;
	std::string temp;
	
	// url format for addSensor:  addSensor/{token}/{code}
	url.clear();
	url.append("/addSensor/");
	url.append(token);		
	url.append("/");
	temp.clear();
	temp.append(url);
	temp.append("a31dd4f1-9169-4475-b316-764e1e737653");
	url.append(generateCode(temp));

	return sendPost(url, XMLParser.createNewSensor(sensorGroupIDValue, nameValue, dataNameValue, descriptionValue, inuseValue), &Http::standardReplyWrapper);
}

std::string Http::createNewType(std::string aName, std::vector<std::pair<std::string, std::string>> aListOfFields) throw (HttpError)

{
	XML XMLParser;
	
	login();

	std::string url;
	std::string temp;
	
	// url format for addSensor:  addSensor/{token}/{code}
	url.clear();
	url.append("/addType/");
	url.append(token);		
	url.append("/");
	
	temp.clear();
	temp.append(url);
	temp.append("a31dd4f1-9169-4475-b316-764e1e737653");
	url.append(generateCode(temp));

	return sendPost(url, XMLParser.createNewType(aName, aListOfFields), &Http::standardReplyWrapper);
}

std::string Http::createNewSensorGroup(const std::string& installationIDValue, const std::string& nameValue, const std::string& descriptionValue, const std::string& inuseValue)
{
	XML XMLParser;
	
	login();

	std::string url;
	std::string temp;
	
	// url format for entity: select/{token}/{destination}/{code}
	url.clear();
	url.append("/addGroup/");
	url.append(token);		
	url.append("/");
	
	temp.clear();
	temp.append(url);
	temp.append("a31dd4f1-9169-4475-b316-764e1e737653");
	url.append(generateCode(temp));

	return sendPost(url, XMLParser.createNewSensor(nstallationIDValue, nameValue, descriptionValue, inuseValue);
, &Http::standardReplyWrapper);



}

