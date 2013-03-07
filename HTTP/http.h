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

#include "../XML/XML.h"
class Http
{

	private:
	  	CURL *curl;	
		std::string urlBase;
		std::string personalKey;
		std::string token;
	public: 
		Http(std::string urlBase);
		~Http();
		std::string calculateDestination(int userID, int installationID, int sensorGroupID, int sensorID);
		size_t read_data( void *ptr, size_t size, size_t nmemb, void *userdata);
		size_t write_data(void *buffer, size_t size, size_t nmemb, void *userp);
		void sendGet(std::string urlAddition);
		void sendPost(std::string urlAddition, std::string data, size_t (Http::*callback) (void *, size_t, size_t, void *));
		size_t loginReply(void *buffer, size_t size, size_t nmemb, void *userp);
		std::string generateCode(std::string url);
		std::string getCurrentTimestamp();
		void uploadData(float data);
		std::string toBase64(std::string input);
		bool login();
		std::string getEntity(std::string destinationBase64);	
		void setToken(std::string aToken);
};	

#endif
