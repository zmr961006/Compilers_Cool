/*************************************************************************
	> File Name: lex_table.cpp
	> Author: 
	> Mail: 
	> Created Time: 2016年10月13日 星期四 20时05分33秒
 ************************************************************************/

#include<iostream>
#include"./lex_table.h"
#include"./lex_file.h"
#include"./lex_more.h"
using namespace std;

lex_word word_table[LEX_TABLE];

int init_word_table(){
    
    word_table[0].Token = RWORD;
    word_table[1].Token = REEX;
    word_table[3].Token = SYSTNX;
    word_table[4].Token = FUN;

    for(int i = 0;i < 4;i++){
        
        word_table[i].next = word_table[i].last = NULL;;
        memset(word_table[i].key_word,0,30);
        word_table[i].key_word[0] = 'F';
    }
    
    //std::cout << word_table[0].key_word[0]  << "****" << std::endl;
    return 0;
}



int insert_def_word(char *word,int word_length){

    lex_word  *head ;
    head =  (lex_word *)malloc(sizeof(lex_word));
    head->Token = 5;
    memcpy(head->key_word,word,word_length);
    head->val_word = NULL;
    head->action = NULL;
    head->next = NULL;
    head->last = NULL;

    
    if(word_table[0].key_word[0] == 'F'){
        
        word_table[0].next = head;
        word_table[0].last = head;
        word_table[0].key_word[0] = 'S';

    }else{
    
        word_table[0].last->next = head;
        word_table[0].last       = head;
        
    }
    
    return 0;
}

int test_def_word(){
    
    lex_word * temp;
    temp = word_table[0].next;
    while(temp != NULL){
        
        std::cout << temp->key_word << std::endl;
        temp = temp->next;
    }


}


int insert_RE(char * word_buffer,int word_length,int order){
    
    
    if(!order){
        
        lex_word * head;
        head = (lex_word *)malloc(sizeof(lex_word));
        head->Token = RREEX;
        memcpy(head->key_word,word_buffer,word_length);
        head->val_word = NULL;
        head->action   = NULL;
        head->next     = NULL;
        head->last     = NULL;

        if(word_table[1].key_word[0] == 'F'){
            
            word_table[1].next = head;
            word_table[1].last = head;
            word_table[1].key_word[0] = 'S';

        }else{
            
            word_table[1].last->next = head;
            word_table[1].last       = head;

        }

    }else{
        char * rex;
        rex = (char *)malloc(sizeof(char)*word_length);
        bzero(rex,word_length);
        memcpy(rex,word_buffer,word_length);
        word_table[1].last->val_word = rex;

    }


}

int test_RE(){
    
    lex_word * temp;
    temp  = word_table[1].next;
    while(temp != NULL){

        std::cout << "^ "<<temp->key_word << " :: " << temp->val_word << std::endl;
        temp = temp->next;

    }


}


