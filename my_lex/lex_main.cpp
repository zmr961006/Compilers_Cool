/*************************************************************************
	> File Name: lex_main.cpp
	> Author: 
	> Mail: 
	> Created Time: 2016年10月10日 星期一 20时52分15秒
 ************************************************************************/

#include<iostream>
#include<stdio.h>
#include<fstream>
#include"./lex_file.h"
#include"./lex_more.h"

using namespace std;

extern sys_buf *sys_buf1;
extern sys_buf *sys_buf2; 

extern char * RE;

extern ifstream input_file;
extern ofstream write_file;

int chunk_pre(int argc);

int main(int argc,char **argv){
    
    chunk_pre(argc);
    
    lexyy(argc,argv);


    input_file.close();
    write_file.close();
    
    
    return 0;

}


int chunk_pre(int argc){
    
    if(argc < 2){
        
        std::cout << "please set the args \n" ;
        
        exit(0);

    }


}
