/*************************************************************************
	> File Name: 2_5_3.c
	> Author: 
	> Mail: 
	> Created Time: 2016年09月08日 星期四 20时46分03秒
    > 极简单翻译器和改进的翻译器
 ************************************************************************/

#include<stdio.h>


void expr(){   /*实现expr->term rest*/
    
    term();
    rest();

}

void rest(){

    if(lookhead == '+'){
        match('+');
        term();
        print('+');
        rest();
    }else if(lookhead == '-'){
        match('-');
        term();
        print('-');
        rest();
    }else{

        //
    }

}

void term(){
    
    if(lookhead.dig() == ture){
        t = lookhead;
        match(lookhead);
        print(t);
    }else{
        print("sytax error");
    }

}

/*_______________________________________________________________________________________________________________*/

void rest(){
    
    while(true){
        if(lookhead == '+'){
            match('+');
            term();
            print('+');
            continue;
        }else if(lookhead == '-'){
            match('-');
            term();
            print('-');
            continue;
        }
        break;
        
    }

}
