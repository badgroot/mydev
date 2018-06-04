#ifndef __DATABASE_H__
#define __DATABASE_H__
#include <iostream>
#include <sqlite3.h>
#include <string.h>
#include <string>
class database
{
public:
	database(const std::string );
 	database(const char *);
	bool isOpen();	
	bool isReady();
	bool exec(const std::string &);
	bool exec(const char *);
	void close();
	bool prepare(const char * );
	bool step();
	~database();
private :
void errormsg();
std::string _dbname;
sqlite3* _db;
sqlite3_stmt* stmt;
bool _isOpen;
bool _isReady;
};
#endif