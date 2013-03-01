all:	test

test: http
	g++ http_test.cpp -o http_test.out http.o ../XML/XML.o -lcurl -lxerces-c -g -std=c++11
http:
	g++ -c http.cpp -o http.o -lcurl -std=c++11
clean:
	rm http.o
