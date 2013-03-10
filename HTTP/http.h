#ifndef HTTP_H
#define HTTP_H

#include <curl/curl.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <openssl/sha.h>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <iterator>
#include <stdlib.h>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/local_time/local_time.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>

#include <boost/archive/iterators/base64_from_binary.hpp>
#include <boost/archive/iterators/binary_from_base64.hpp>
#include <boost/archive/iterators/insert_linebreaks.hpp>
#include <boost/archive/iterators/transform_width.hpp>
#include <boost/archive/iterators/ostream_iterator.hpp>

#include <boost/archive/iterators/base64_from_binary.hpp>
#include <boost/archive/iterators/binary_from_base64.hpp>
#include <boost/archive/iterators/transform_width.hpp>
#include <boost/archive/iterators/insert_linebreaks.hpp>
#include <boost/archive/iterators/remove_whitespace.hpp>
#include <iostream>
#include <string>

#include <sstream>

#include <unistd.h>

#include "../XML/XML.h"

#include "httperror.h"
class Http
{

	private:
		CURL *curl;	
		std::string urlBase;
		std::string personalKey;
		std::string token;
		std::string curlReply;
	public: 
		Http(std::string urlBase);
		~Http();

		size_t read_data( void *ptr, size_t size, size_t nmemb);	//Currently not used nor implemented correctly (to send data you just pass a pointer to the data to Curl
		static size_t loginReplyWrapper(void *buffer, size_t size, size_t nmemb, void *obj);
		size_t loginReply(void *buffer, size_t size, size_t nmemb);
		static size_t standardReplyWrapper(void *buffer, size_t size, size_t nmemb, void *obj);
		size_t write_data(void *buffer, size_t size, size_t nmemb);
		static size_t headerHandlerWrapper(void *buffer, size_t size, size_t nmemb, void *obj);
		size_t headerHandler(void *buffer, size_t size, size_t nmemb);

	
		std::string sendGet(std::string urlAddition, size_t (*callback) (void*, size_t, size_t, void*)) throw (HttpError);
		std::string sendPost(std::string urlAddition, std::string data, size_t (*callback) (void *, size_t, size_t, void *)) throw (HttpError);

		std::string generateCode(std::string url);
		std::string calculateDestination(int userID, int installationID = -1, int sensorGroupID = -1, int sensorID = -1);
		std::string toBase64(std::string input);

		void uploadData(float data);
		bool login();
		void setUserRights(std::string entity, int userID, int rights);
		std::string getEntity(std::string destinationBase64);	
		void setToken(std::string aToken);
		std::string selectData(std::string destinationBase64, std::vector<std::string> fields);
		std::string testQuery();
};	

#endif	
