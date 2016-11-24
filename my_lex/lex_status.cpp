/*************************************************************************
	> File Name: lex_status.cpp
	> Author: 
	> Mail: 
	> Created Time: 2016年10月24日 星期一 16时28分39秒
 ************************************************************************/

#include<iostream>
#include"./lex_status.h"
using namespace std;


extern lex_word word_table[LEX_TABLE];

Status  *start ;


int create_status_table(tree_node * node){      /*初始化表相关信息*/

    init_status(node);


}

Status * init_status_node(Status *node){       /*初始化基准状态节点*/
    
    if(node == NULL){
        Status * pos = (Status *)malloc(sizeof(Status));
        pos->status = 0;
        pos->node = NULL;
        pos->next   = NULL;
        pos->num_status = 0;
        return pos;

    }else{
        node = (Status *)malloc(sizeof(Status));
        node->status = 0;
        node->node = NULL;
        node->next = NULL;
        node->num_status = 0;
        return node;
    }

}



int init_status(tree_node *node){      /*创建基准状态集A B C D....*/

    if(node == NULL){

        printf("error no start status\n");
        exit(0);

    }
    start = init_status_node(NULL);     /*初始化头结点*/
    set * pos;
    pos = node->firstpos;
    while(pos != NULL){
        Status *begin = init_status_node(NULL);
        begin->status = 1;
        begin->node = pos->node;
        insert_status(start,begin);  
        pos = pos->next;
    }

}


int insert_status(Status *start,Status *elem){
    
    Status * temp = start;
    if(temp->num_status == 0){
        temp->next = elem;
        temp->num_status++;
    }else{
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = elem;
        start->num_status++;    
    }

}


