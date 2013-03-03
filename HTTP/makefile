all:	test

test: http
	g++ http_test.cpp -o http_test.out http.o ../XML/XML.o -lcurl -lxerces-c -lboost_thread -lboost_date_time -g -std=c++11
http:
	g++ -c http.cpp -o http.o -lcurl -lboost_thread -lboost_date_time -std=c++11
clean:
	rm http.o
