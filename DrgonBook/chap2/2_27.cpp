/*************************************************************************
	> File Name: 2_27.cpp
	> Author: 
	> Mail: 
	> Created Time: 2016年09月08日 星期四 21时26分30秒
    > 简单翻译器
 ************************************************************************/

#include<iostream>
using namespace std;

class Parser{

    int lookahead;
    int index;
    std::string mood;

    public:
        void Parser(std::string obj){
            mood(obj);
            lookhead = mood[0];
            index = 1;

        } 

        void expr(){
            
            term();
            while(true){
                if(lookahead == '+'){
                    match('+');
                    term();
                    std::cout << '+' ;
                }else if(lookahead == '-'){
                    match('-');
                    term();
                    std::cout << '-' ;
                }else{

                    return ;

                }   
                
            
            }
            
        }

    int isdig(int a){

        if( a >= 0 && a <= 9){

            return 1;

        }else{

            return 0;
        }


    }

    void term(){

        if(isdig(lookahead) == true){ 

            std::cout.setf(ios::showbase | ios::uppercase);
            std::cout << lookahead ;
            std::cout.unsetf(ios::showbase | ios::uppercase);

        }else{
            
            std::cout << "syntx error" << std::endl;
            exit();
            
        }
        
        
    }
    
    void match(int t){
        if(lookahead == t){
         
            lookahead = next_sync();

        }else{
            
            std::cout << "syntx error";

        }


    }

    int next_sync(){
        
        return mood[index];

    }

}



