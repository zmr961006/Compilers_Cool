/*************************************************************************
	> File Name: yy_more.cpp
	> Author: 
	> Mail: 
	> Created Time: 2016年10月10日 星期一 19时54分48秒
 ************************************************************************/

#include<iostream>
#include<stack>
#include"./lex_file.h"
#include"./lex_more.h"
#include"./lex_table.h"
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
    
    init_word_table();
    lex_ansylse();


}

int lex_ansylse(){
    
    int status = 1;
    int index = 0;
    char ch;
    read_buf();
    
    if(status == 1){     /*anasyle  the  def status*/
        char start = 0;
        char word[30];
        int i = 0;
        while(1){
            
            if(index >= buf_length ){
                read_buf();
                index  = 0;
            }
            if(start == '}'){
                status = 2;
                index++;
                break;
            }
            start = sys_buf1->sys_buffer[index];
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
                insert_def_word(word,30);
                bzero(word,10);
                index++;
                i = 0;
                continue;
            }

        }  
            

    }
    
    if(status == 2){
        
        char start   = 0;
        int forward = 0;
        int flag    = 0;
        int i       = 0;
        char word_buffer[100] ;
        int order = 0;    
        while(1){
              
            start = sys_buf1->sys_buffer[index];
            
            
            if(index >= buf_length){
                read_buf();
                index = 0;
            }
            if(start == '%'){
        
                status = 3;
                break;
            }
            
            char fforward = sys_buf1->sys_buffer[index + 2];
            forward = sys_buf1->sys_buffer[index + 1];
            if(start == ' ' || start == '\n'){
                index++;
                continue;
            }else{
                
                word_buffer[i] = start;
                i++;
                index++;
                if(forward == ' ' || forward == '%' || forward == ';' ){
                    insert_RE(word_buffer,100,(order%2));
                    memset(word_buffer,0,sizeof(word_buffer));
                    i  = 0;
                    order++;
                    index++;
                }
                continue;
            }
            
        }



    }
    
    if(status == 3){
        test_RE();
	    char start   = 0;
        char forward = 0;
        int flag    = 0;
        int i       = 0;
        char word_buffer[100] ;
        index += 2;
        
        while(1){
            
            start = sys_buf1->sys_buffer[index];
            
            if(index >= buf_length){
                read_buf();
                index = 0;
            }
            if(start == '%'){
                status = 4;
                break;
            }
            forward = sys_buf1->sys_buffer[index + 1];
            
            if(start == ' '){
                index++;
                continue;
            }else{
                if(start == '{'){
                    while(1){
                        word_buffer[i] =  start;
                        index++;
                        start = sys_buf1->sys_buffer[index];
                        i++;
                        if(start == '}'){
                            word_buffer[i] = start;
                            std::cout << word_buffer << std::endl;
                            bzero(word_buffer,100);
                            i = 0;
                            break;
                        }
                        
                    }
                }else if(start == '"'){
                    while(1){  
                        word_buffer[i] = start;
                        index++;
                        start = sys_buf1->sys_buffer[index];
                        i++;
                        if(start == '"'){
                            word_buffer[i] = start;
                            std::cout << word_buffer << std::endl;
                            bzero(word_buffer,100);
                            i  = 0;
                            break;
                        }
                    }
                }else if(is_letter(start)){
		            while(1){  
                        word_buffer[i] = start;
                        index++;
                        start = sys_buf1->sys_buffer[index];
                        forward = sys_buf1->sys_buffer[index + 1 ];
                        i++;
                        if(forward == ' '){
                            word_buffer[i] = start;
                            std::cout << word_buffer << std::endl;
                            bzero(word_buffer,100);
                            i  = 0;
                            break;
                        }
                    }
		        }
                index++;
                continue;
            }
            
        
        }

    if(status == 4){
        char buf_temp[buf_length];
        memset(buf_temp,0,buf_length);
        int j = 0;
        for(int temp = index;temp <= buf_length; temp++,j++){
            
            buf_temp[j] = sys_buf1->sys_buffer[index];
            index++;
        }
        std::cout << buf_temp << std::endl;
        while(1){
            int flag = 0;
            memset(buf_temp,0,buf_length);
            flag = read_buf();
            
            if(flag > 0){
                memcpy(buf_temp,sys_buf1->sys_buffer,buf_length);
            }else{
                break;
            }
            

        }

        
    }


 }

}
    

int is_letter(char c){
      
    if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||(c == '_')){
        return 1;   
    }
    return 0;

}


int is_digit(char c){
    
    if((c >= '0') && (c <= '9')){
        return 1;
    }
    return 0;

}


int is_sysntx(char c){
    
    if((c == '{') || ( c == '}') || ( c == '(') || ( c == ')' ) || (c == '[') || (c == ']') ){
        return 1;
    }
    
    return 0;

}

int is_RE(char c){
    
    
    if((c == '{') || ( c == '(') || (c == '[') ){
        return 1;
    }
    return 0;
}

