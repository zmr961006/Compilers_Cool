/*************************************************************************
	> File Name: 2_19.c
	> Author: 
	> Mail: 
	> Created Time: 2016年09月07日 星期三 22时38分39秒
 ************************************************************************/

#include<stdio.h>


void stmt(){
    
    switch(lookahead){
        case expr:
            match(expr);
            match(';');
            break;
        case if:
            match(if);
            macth('(');
            match(expr);
            match(')');
            stmt();
            break;
        case for:
            match(for);
            match('(');
            optexpr();
            match(';');
            optexpr();
            match(';');
            optexpr();
            match(')');
            stmt();
            break;
        case othres:
            match(other);
            break;
        default:
            report("syntax error");
    }

}


void optexpr(){
    
    if(lookahead == expr){
        match(expr);
    }

}

void match(terminal t){
    
    if(lookahead == t){
        lookahead = nextTerminal;
    }else{
        report("syntax error");
    }

}


