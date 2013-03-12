all:	test 

test:	XML
	g++ XML_test.cpp -o XML_test.out XML.o -g -lxerces-c -lboost_thread -lboost_date_time -g -std=c++11
XML:
	g++ -c XML.cpp -o XML.o -g -std=c++11
clean :
	rm XML.o
