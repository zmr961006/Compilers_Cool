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

#define LEX_TABLE       5

#define DEF      1    /*宏定义阶段*/
#define REEX     2    /*正则阶段*/
#define WORD     3    /*关键字操作阶段*/
#define FUN      4    /*用户自定义函数*/


#define RWORD     5    /*关键字类型token*/
#define RREEX     6    /*正则表达式token*/
#define SYSTNX    7    /*字符类型和操作token*/
#define FUNC      8    /*自定义函数token*/
#define CHLIST    9    /*字符列表变量*/

typedef struct sys_buf{    /*buf of lex*/

    char sys_buffer[buf_length];
    int chunk;  /*1:read,0:noread*/

}sys_buf;



typedef struct tree_node{    /*tree_node for RE_tree*/


    tree_node *left ;
    tree_node *right;
    int        token;
    char     buf[30];
    int      node_length;

}tree_node;

typedef struct  lex_word{   /*词法字符表结构，用于构造word字符表*/
    
    /*此处使用哈希表的效果更佳，此处暂时不优化*/
    int Token        ;      /*词的类型*/
    char key_word[100];      /*词的内容*/
    char *val_word   ;      /*词的解释*/
    char *action     ;      /*关键字相关操作*/
    int  length      ;
    int  val_length  ;         
    struct lex_word *next;  /*链表*/
    struct lex_word *last;
    struct tree_node *root;

}lex_word;

typedef struct  word_yy{   /*生成代码的字符表*/

    int Token;     /*词法大类编码*/
    int Tcode;     /*目标字符集的词编码*/
    char *code;    /*词的内容*/
    char *action;  /*词的动作*/
    int length;    /*字的长度*/

}word_yy;


int open_file(std::string file_name);
int open_wfile(std::string file_name);
int write_infile(std::string file_name,char * buf,int length);
int write_infile_index(std::string file_name,char * buf,int length);
int write_infile_ch(char);
int write_infile_all(char *buf,int length);


int read_file(std::string file_name,char *buf,int length);
int read_all_file(std::string file_name,char *buf,int length);



#endif
