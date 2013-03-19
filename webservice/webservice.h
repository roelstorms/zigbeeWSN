#ifndef WEBSERVICE_H
#define WEBSERVICE_H

#include <stdio.h>
#include <string.h>
#include "mongoose.h"

class Webservice
{
	private:
	struct mg_context *ctx;
	struct mg_callbacks callbacks;

	// List of options. Last element must be NULL.
	


	public:
	Webservice();
	~Webservice();
	
	static int beginRequestHandlerWrapper(struct mg_connection *conn);
	int beginRequestHandler(struct mg_connection *conn);

};

#endif
