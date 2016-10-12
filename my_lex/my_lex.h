/*************************************************************************
	> File Name: my_lex.h
	> Author: 
	> Mail: 
	> Created Time: 2016年10月10日 星期一 19时55分21秒
 ************************************************************************/

#ifndef _MY_LEX_H
#define _MY_LEX_H

/*几个全局变量，主要包括文件的流和全局参数*/

#include<iostream>
#include<fstream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define buf_length      (1 << 11)

#define RE_LIMIT        (1 << 8)

#define DEF      1    /*宏定阶段*/
#define REEX     2    /*正则阶段*/
#define FUN      3    /*函数阶段*/


typedef struct sys_buf{    /*buf of lex*/

    char sys_buffer[buf_length];
    int chunk;  /*1:read,0:noread*/

}sys_buf;

//char *RE;   /*Regular Expression*/

class tree_node{    /*tree_node for RE_tree*/

public:

    tree_node *left ;
    tree_node *right;
    int        token;
    char     buf[10];

    tree_node(){
        left = NULL;
        right = NULL;
    }

};




int open_file(std::string file_name);
int open_wfile(std::string file_name);
int write_infile(std::string file_name,char * buf,int length);
int read_file(std::string file_name,char *buf,int length);
int read_all_file(std::string file_name,char *buf,int length);



#endif
