/*************************************************************************
	> File Name: lex_main.cpp
	> Author: 
	> Mail: 
	> Created Time: 2016年10月10日 星期一 20时52分15秒
 ************************************************************************/

#include<iostream>
#include<stdio.h>
#include<fstream>
#include"./my_lex.h"
#include"./yy_more.h"

using namespace std;

extern sys_buf *sys_buf1;
extern sys_buf *sys_buf2; 
extern char * RE;
int main(int argc,char **argv){
    
    //char buf[100];
    //char *thing = "hello world\n   kasda*&^&*^&$& ()sksksk";
    //char *reex = "(a|b)*abb";
    //std::string name("1.l");
    //init_buf();
    //init_RE(reex);
    //RE_to_tree();
    //std::cout << reex << std::endl;
    //std::cout << RE << std::endl;
    lexyy(argc,argv);
    //std::string name2("yy.lex.c");
    //open_file(name);
    //open_wfile(name);
    //write_infile(name,thing,30);
    //read_all_file(name,buf,100);
    //std::cout << buf << std::endl;
    //read_buf(sys_buf1);
    //std::cout << " >>" << sys_buf1->sys_buffer << std::endl;

    //input_file.close();
    //write_file.close();
    return 0;



}
