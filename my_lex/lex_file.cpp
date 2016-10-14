/*************************************************************************
	> File Name: my_lex.cpp
	> Author: 
	> Mail: 
	> Created Time: 2016年10月10日 星期一 17时04分21秒
 ************************************************************************/

#include<iostream>
#include<stdio.h>
#include<fstream>
#include"./lex_file.h"
using namespace std;

ifstream input_file;
ofstream write_file;


int open_file(std::string  file_name){


    input_file.open(file_name.c_str());   
    if(!input_file.is_open()){
    
        std::cout << "system error : open file failed! " << file_name << std::endl;

    }

    return 0;
    

    
}

int open_wfile(std::string file_name){
    
    write_file.open("yy.lex.c");
    if(!write_file.is_open()){
            
        std::cout << "system error : open file failed! " << file_name << std::endl;

    }
    
    return 0;

}


int write_infile(std::string file_name,char * buf,int length){  
    
    write_file << buf << endl;
    
    return 0;
    

}


int read_file(std::string file_name,char* buf,int length){
    
    input_file.getline(buf,length);

}

int read_all_file(std::string file_name,char *buf,int length){

    input_file.read(buf,length);

}



