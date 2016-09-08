/*************************************************************************
	> File Name: 2_4_6.c
	> Author: 
	> Mail: 
	> Created Time: 2016年09月08日 星期四 20时01分06秒
    预测分析例子
 ************************************************************************/

#include<stdio.h>

void stmt(){

    switch(lookhead){
            case "+":
                match("+");
                s();
                s();
                break;
            case "-":
                match("-");
                s();
                s();
                break;
            case "a":
                match("a");
                break;
            default:
                syntax_error();
                break;
    }

}



void stmt(){
    
    switch(lookhead){

            case "(":
                S();
                match("(");
                S();
                match(")");
                S();
                break;

    }

}


stmt -> S();

void stmt(){
    
    switch(lookhead){
            case "0":
                match(0);
                S();
                match(1);
                break;
            case "1":
                break;
    }

}
