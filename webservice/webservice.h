#ifndef WEBSERVICE_H
#define WEBSERVICE_H

#include <stdio.h>
#include <string.h>
#include "mongoose.h"
#include "webservicerequest.h"
#include <boost/thread/mutex.hpp>
#include <queue>


class Webservice
{
	private:
	struct mg_context *ctx;
	struct mg_callbacks callbacks;
	std::queue<WebserviceRequest> * webserviceRequestQueue;
	boost::mutex * webserviceRequestMutex;
		// List of options. Last element must be NULL.
	


	public:
	Webservice(std::queue<WebserviceRequest> * aWebserviceRequestQueue, boost::mutex * aWebserviceRequestMutex);
	~Webservice();
	
	static int beginRequestHandlerWrapper(struct mg_connection *conn);
	int beginRequestHandler(struct mg_connection *conn);

};

#endif