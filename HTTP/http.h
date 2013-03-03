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
class Http
{

	private:
	  	CURL *curl;	
		std::string urlBase;
		std::string personalKey;
	public: 
		Http(std::string urlBase);
		~Http();
		std::string calculateDestination(int userID, int installationID, int sensorGroupID, int sensorID);
		size_t read_data( void *ptr, size_t size, size_t nmemb, void *userdata);
		static size_t write_data(void *buffer, size_t size, size_t nmemb, void *userp);
		void sendGet(std::string urlAddition);
		void sendPost(std::string urlAddition, std::string data);
		std::string generateCode(std::string url);
		std::string getCurrentTimestamp();
};

#endif
