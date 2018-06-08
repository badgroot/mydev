#include <iostream>
#include "database.h"
#include <jsoncpp/json/json.h>

Json::Reader reader;
Json::Value root;
Json::StyledStreamWriter writer;

inline std::string to_string(const Json::Value &val, bool beautify = false) {
  if (beautify)
    return std::move(val.toStyledString());
  else {
    Json::FastWriter fw;
    fw.omitEndingLineFeed();
    return std::move(fw.write(val));
  }
}

int main()
{	char buffer[1000];
	 std::string query="CREATE TABLE IF NOT EXISTS demo (name JSON, age INTEGER);";
	 database db("json.db");
	 db.exec(query);
	 db.exec("CREATE TABLE IF NOT EXISTS demo2(INSERT_TIME DATETIME NOT NULL default CURRENT_TIMESTAMP ,MESSAGE JSON);");
	 //db.exec("insert into demo values(\"HIMASHU\",24)");
	std::string text="{\"AB\":\"CD\",\"VALUE\":12}";

	int parseSuccess=reader.parse(text,root,false);
	if(!parseSuccess)
	{
	std::cout<<"could not parse data\n";
	}
	else {
	std::cout<<"parsed\n";
		}
root["NAME"]="HIMASHU";
root["LASTNAME"]="PACHAURI";

sprintf(buffer,"insert into demo values('%s',5000);",to_string(root).c_str());
//std::cout<<buffer<<std::endl;

//std::cout<<db.exec(buffer);
///std::cout<<root.toStyledString()<<std::endl;

///std::cout<<db.exec("insert into  demo2 VALUES(\"\",'"+ to_string(root)+"';");
db.exec("insert into demo2(MESSAGE) VALUES('"+ to_string(root)+"')");
}