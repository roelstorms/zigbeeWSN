#include "webservice.h"

// This function will be called by mongoose on every new request.
int Webservice::beginRequestHandlerWrapper(struct mg_connection *conn)
{
	const struct mg_request_info *request_info = mg_get_request_info(conn);
	
	return static_cast<Webservice*>(request_info->user_data)->beginRequestHandler(conn);
}

int Webservice::beginRequestHandler(struct mg_connection *conn)
{
	const struct mg_request_info *request_info = mg_get_request_info(conn);

	char content[500];
	int post_data_len;
	char post_data[1024] = "";

	// Prepare the message we're going to send
	post_data_len = mg_read(conn, post_data, sizeof(post_data));

	int content_length = snprintf(content, sizeof(content),	"<error>false</error>",request_info->uri, post_data);
	printf("%s: %d\n", post_data, content_length);
	
	// Send HTTP reply to the client
	mg_printf(conn,
			"HTTP/1.1 200 OK\r\n"
			"Content-Type: text/plain\r\n"
			"Content-Length: %d\r\n"        // Always set Content-Length
			"\r\n"
			"%s",
			content_length, content);

	// Returning non-zero tells mongoose that our function has replied to
	// the client, and mongoose should not send client any more data.
	return 1;

}



Webservice::Webservice(PacketQueue * aWSQueue, std::condition_variable * aWSConditionVariable, std::mutex * aWSConditionVariableMutex) : wsQueue(aWSQueue), wsConditionVariable(aWSConditionVariable), wsConditionVariableMutex(aWSConditionVariableMutex)
{
	const char *options[] = {"listening_ports", "8080", "error_log_file", "./webservice_error.txt", NULL};

	// Prepare callbacks structure. We have only one callback, the rest are NULL.
	memset(&callbacks, 0, sizeof(callbacks));
	callbacks.begin_request = &Webservice::beginRequestHandlerWrapper;

	// Start the web server.
	ctx = mg_start(&callbacks, (void*) this, options);
}

Webservice::~Webservice()
{
	// Stop the server.
	mg_stop(ctx);

}
