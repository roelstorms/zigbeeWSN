all:	sql
	g++ sqlTest.cpp -o sqlTest.out sql.o sqlite3.o -std=c++11 -g -lpthread -ldl
sql:
	g++ -c sql.cpp -o sql.o -std=c++11
sqlite3:
	gcc -c sqlite3.c -o sqlite3.o 
