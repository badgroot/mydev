/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: user
 *
 * Created on 16 May, 2018, 12:30 PM
 */

#include <cstdlib>
#include <jsoncpp/json/json.h>
#include <fstream>
#include <iostream>
#include <string>
#define NEWLINE std::cout<<"\n";
using namespace std;
Json::Reader reader;
Json::StyledStreamWriter writer;
Json::Value root;
std::string infile="in.json";
std::string outfile="out.json";

/*
 * 
 */
void printer(std::string line)
{
    std::cout<<line<<std::endl;
}
void printer(char * p)
{
    printf("%s",p);
}

int main(int argc, char** argv) {
    std::fstream file;
    bool parseSuccess;
    file.open(infile);
    std::string text="{\"AB\":\"CD\",\"VALUE\":12}";
    if(!file)
    {
        std::cerr<<infile<<" not opened"<<std::endl;
        std::exit(0);
    }
    else printer("FileOpend");
    parseSuccess=reader.parse(file,root,false);
    file.close();
    if(!parseSuccess)
    {std::cout << reader.getFormattedErrorMessages();
        printer("Not parsed " +infile);
    }
    else printer("Parse successfully");
    root["LASTNAME"]="HIMANSHU2";
    root["AGE2"]=123;
    if(root.isArray())
    {
        std::cout<<"root is array!";
        NEWLINE;
    
    
    }
    if(root.empty())
    {
        printer("root is empty");
    }
    if(root["FNAME"].isString())
    {
        printer("root[FNAME] is string");
        printer(root["FNAME"].asString());
    }
    if(root["LNAME"].isString())
    {
        printer("root[LNAME] is a string");
        printer(root["LNAME"].asString());
    }
    if(root["AGE"].isInt())
    {
        printer("root[Age] is string");
       
        printer("root[Age]=" + std::to_string(root["AGE"].asInt()));
    }
    file.open(outfile);
    if(!file)
    {
        printer("file not opened ,"+ outfile);
        std::exit(1);
    }
    
    
    else printer("File opened~~~"+ outfile);
    root.removeMember("LNAME");
    writer.write(file,root);
    file.close();
    
std::string vab=root.toStyledString();
printer("HIMANSHU");
printer(vab);
printer("HIMANSHU2");
printer(vab.c_str());

NEWLINE
        NEWLINE
        NEWLINE
        NEWLINE NEWLINE NEWLINE
        NEWLINE

if(root.isMember("characters"))
{
const Json::Value &getArrayobj =root["characters"];
for(int i=0;i<getArrayobj.size();i++)
{
    std::cout<<" name "<<getArrayobj[i]["name"].asString();NEWLINE
            std::cout<<" chapter "<<getArrayobj[i]["chapter"].asString();NEWLINE
}




        root.clear();
if(reader.parse(text,root,false))
{
    printer("parse Successfully");
}
else {
    printer("Not Parsed");
}
std::cout<<root.toStyledString()<<std::endl;

file.open(outfile,ios::app);
if(!file)
{
    std::cout<<"File is not opened"<<__FILE__<<__LINE__<<__func__<<std::endl;

std::exit(0);    
}
else{std::cout<<"File opened!!!"<<std::endl;}
writer.write(file,root);
file.close();






return 0;
}}

