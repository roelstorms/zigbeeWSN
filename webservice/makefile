all: mongoose webservice
	g++ webserviceTest.cpp -o webservice.out mongoose.o webservice.o webservicerequest.o -lpthread -ldl -std=c++11
webservice:
	g++ -c webservice.cpp -o webservice.o -std=c++11
wspacket.o:
	g++ -c wspacket.cpp -o wspacket.o -std=c++11
mongoose:
	gcc -c mongoose.c -o mongoose.o 
