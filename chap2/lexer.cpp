/*************************************************************************
	> File Name: lexer.cpp
	> Author: 
	> Mail: 
	> Created Time: 2016年09月11日 星期日 14时31分09秒
 ************************************************************************/

#include<iostream>
#include<fstream>

using namespace std;

class Token{

    public:
        int tag;
        Token(int i){ tag = i; }
};


class Num : Token{
    public :
        int value;
        Num(int i):Token(1){ value = i; }
};

class Word: Token{
    public:
        std::string word;
        Word(std::string a):Token(2){ word = a; }
};

class Lex{
    
    public:
        std::string buff;
        char buf[1000];
        
        Lex(){};
        int open_file();
        int do_lex();   


};

int Lex::open_file(){
    
    fstream file("1.c");
    if(file == NULL){

        std::cout << "open error" << std::endl;
        file.close();
        return -1;
    }
    
    char peek;
    while(!file.eof()){
        
        file.read(buf,1000); 
        std::cout << buf << std::endl;

    }
    
    return 0;
}

int Lex::do_lex(){
    char peek;
    for(int i = 0;i < 1000;i++){
        peek = buf[i];
        if(peek == ' ' || peek == '\n'){
            
            continue;

        }else if(peek == '/'){
            int j = i;
            j++;
            char temp = buf[j++];
            if(temp == '/' || temp == '*'){
                i++;
                continue;
            }
            
        }else if(peek == 'i' || peek == 'd' || peek == 'l'){
            char sytx[3];
            for(int index = 0;index < 3;index++){
                sytx[index] = buf[ i + index];
            }
            std::cout << "< ";
            for(int in = 0;in < 3;in++){
                std::cout << sytx[in];
            }   
            std::cout << ">";
            std::cout << std::endl;
        }else{

            continue;
        }



    }
    
}



int main(){
    
    Lex a;
    a.open_file();
    a.do_lex();

}

