
/*******************************************
Author:HIMANSHU PACHAURI
DATE:[2018-06-04 02:21]
Project:
Filename:
*******************************************/

#include "database.h"

database::database(std::string name)
{
	database(name.c_str());
}
database::database(const char *name)
{int rc=sqlite3_open(name,&_db);
	if(rc!=SQLITE_OK){
	errormsg();

	}
_isOpen=true;

}
database::~database()
{
	close();
}
void database::close()
{_isOpen=false;
_isReady=false;
	sqlite3_close(_db);
	sqlite3_finalize(stmt);
}

bool database::exec(const std::string &query)
{bool status=false;
	if(prepare(query.c_str())){
		if(step()){
		status=true;		
		}
	

}
return status;
}

bool database::prepare( const char *str){
sqlite3_prepare_v2(_db,str,strlen(str),&stmt,NULL);
return true;
}

bool database::step()
{
	int rc=sqlite3_step(stmt);
if(rc!=SQLITE_DONE)
{//sqlite3_errmsg(_db);
	errormsg();

std::cout<<"error found"<<std::endl;
	return false;
}
return true;
}
void database::errormsg()
{
sqlite3_errmsg(_db);
}
bool database::exec(const char *str)
{
bool status=false;
	if(prepare(str)){
		if(step()){
		status=true;		
		}
	

return true;

}
}