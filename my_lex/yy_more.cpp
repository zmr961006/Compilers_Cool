/*************************************************************************
	> File Name: yy_more.cpp
	> Author: 
	> Mail: 
	> Created Time: 2016年10月10日 星期一 19时54分48秒
 ************************************************************************/

#include<iostream>
#include<stack>
#include"./my_lex.h"
#include"./yy_more.h"
using namespace std;

/*两个缓冲区1 */
 


sys_buf *sys_buf1;

extern ifstream input_file;
extern ofstream write_file;

class tree_node * root;

char *RE;   /*Regular Expression*/



int init_RE(char *buf){          /*init RE buf*/
    
    RE = (char *)malloc(sizeof(char) * RE_LIMIT);
    if(!RE){
        printf("error alloc bad!");
    }
    memset(RE,0,RE_LIMIT);
    memcpy(RE,buf,strlen(buf));
    ex_re();
}

int ex_re(){

    char buf[RE_LIMIT];
    memset(buf,0,RE_LIMIT);
    memcpy(buf,RE,RE_LIMIT);
    int length = strlen(buf);
    
    /*char forward = ' ';
    int  index = 0;
    for(int i = 0;i < length;i++){
        
        forward = buf[i + 1];
        RE[index] = buf[i];
        
        if(buf[i] == '+'){     /aa*暂时使用& 代替正则表达式的语法中的加号
            buf[i] = '&';
        }

        if( ((buf[i] >= 'a' && buf[i] <= 'z') || (buf[i] >= 'A' && buf[i] <= 'Z') )
            && ( (forward >= 'a' && forward <= 'z') || (forward >= 'A' && forward <= 'Z') ) ){
            RE[index + 1] = '+';
            index++;
        }else if( (buf[i] == ')') && (forward == '(') ){
            RE[index + 1] = '+';
            index++;
        }else if( (buf[i] == '*') 
                && ( (forward >= 'a' && forward <= 'z') 
                || (forward >= 'A' && forward <= 'Z') ) ){
            RE[index + 1] = '+';
            index++;
        }

        index++;
        
    }*/
    char finally = '#';
    strcat(RE,&finally);
}



int init_buf(){

    sys_buf1 = (sys_buf*)malloc(sizeof(sys_buf));

    sys_buf1->chunk = 1;


}

int read_buf(){
    
    std::string file(" ");
    memset(sys_buf1,0,sizeof(sys_buf));
    read_all_file(file,sys_buf1->sys_buffer,sizeof(sys_buf1->sys_buffer));
    sys_buf1->chunk = 0;


} 


int  RE_to_tree(){   /*根据正则表达式创建抽象语法树*/

    root = new tree_node();

    stack<tree_node *> oper;
    stack<tree_node *> data;

    char forward;
    int i = 0;
  
}


int lexyy(int argc, char **argv){
    
    std::string filename(argv[1]);  /*set lex_file */
    std::string filename2("yy.lex.c");
    std::cout << "open lex file : " << filename << std::endl; 
    init_buf();
    
    open_file(filename);
    open_wfile(filename2);

    lex_ansylse();


}

int lex_ansylse(){
    
    int status = 1;

    char ch;
    read_buf();
    //std::cout << sys_buf1->sys_buffer << std::endl;
    if(status == 1){
        char start = 0;
        int index  = 0;
        char word[10];
        int i = 0;
        while(1){
            
            if(index >= buf_length ){
                read_buf();
                index  = 0;
            }
            if(start == '}'){
                status = 2;
                break;
            }
            start = sys_buf1->sys_buffer[index];
            //std::cout << start << "," ;
            if(start == '%' || start == '{' || start == ' '){
                index++;
                continue;
            }
            if(start != ','){
                word[i] = start;
                i++;
                index++;
                continue;
            }else if(start == ','){
                std::cout << word  <<std::endl;
                bzero(word,10);
                index++;
                i = 0;
                continue;
            }

        }  
            

    }
    
    if(status == 2){
            


    }
    
    if(status == 3){

            

    }



}
    








