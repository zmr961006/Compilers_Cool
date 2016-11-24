/*************************************************************************
	> File Name: lex_status.h
	> Author: 
	> Mail: 
	> Created Time: 2016年10月24日 星期一 16时28分45秒
 ************************************************************************/

#ifndef _LEX_STATUS_H
#define _LEX_STATUS_H

#include"./lex_file.h"
#include"./lex_status.h"
#include"./lex_table.h"
#include"./lex_more.h"


typedef struct Status{    /*典型状态的总体统计信息*/
 
    int status;           /*状态标记，在生成最终的转移表生成*/
    int num_status;
    tree_node *node;      /*状态包含的节点*/
    struct Status *next;  /*下一个状态*/


}Status;


typedef struct Change{    /*转换结构，为转换函数作用*/
    
    Status *now ;         /*当前状态*/
    Status *next;         /*下一个状态*/
    CHARS  *GO  ;         /*导致变化的原因*/
    int    fun  ;         /*处理函数*/
    
}Change;


typedef struct CHARS{     /*输入符号集合*/
    
    struct CHARS *next;   /*下一个输入符号*/
    int number;           /**/
    char input_buf[number];

}CHARS;



int create_status_table(tree_node *node);

Status * init_status_node(Status * node);

int init_status(tree_node * node);


int insert_status(Status *start,Status *elem);


#endif
