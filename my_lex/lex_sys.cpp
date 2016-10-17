/*************************************************************************
	> File Name: lex_sys.cpp
	> Author: 
	> Mail: 
	> Created Time: 2016年10月14日 星期五 14时50分47秒
 ************************************************************************/

#include<iostream>
#include<stack>
#include"./lex_file.h"
#include"./lex_more.h"
#include"./lex_sys.h"


using namespace std;

extern lex_word word_table[LEX_TABLE];

int lex_sys(){
    
    lex_word_enum();   /*构造yy.l.c 的词法定义表*/
    lex_RE();


}



int lex_word_enum(){
    
    char buf[30];
    memset(buf,0,30);
    std::string name("");
    const char * eum = "enum Token \n { \n";
    memcpy(buf,eum,17);
    write_infile(name,buf,17);
    lex_word * temp;
    temp = word_table[0].next;
    while(temp != NULL){
        char word_file[20];
        memset(word_file,0,20);
        memcpy(word_file,temp->val_word,temp->length);
        write_infile_all(word_file,temp->length);
        write_infile_ch(',');
        temp = temp->next;
      
    }
    char temp_buf[10];
    memcpy(temp_buf,"END",3);
    write_infile_all(temp_buf,3);
    memcpy(temp_buf,"\n};\n",3);
    write_infile(name,temp_buf,3);
    
}


int lex_RE(){
    
    lex_word *temp;
    temp = word_table[1].next;
    while(temp != NULL){
    
        //std::cout << temp->val_word << std::endl;
        get_RE_tree(temp);
        
        temp = temp->next;
    }
    //test_list();
}

stack<tree_node*> S_data ;
stack<tree_node*> S_opera;

int get_RE_tree(lex_word * temp){

    int i = 0;
    char re_RE[100];
    char re_WORD[100];
    memset(re_RE,0,100);
    memset(re_WORD,0,100);
    //std::cout << "the token " << temp->Token << std::endl;
    memcpy(re_RE,temp->val_word,temp->val_length);
    memcpy(re_WORD,temp->key_word,temp->length);
    
    
    char buf[100];
    memset(buf,0,100);
    int index = 0;
    char forward;
    char start;
    char last ;
    
    for(index = 0;index < temp->val_length ;index++){
        
        start   = re_RE[index];
        forward = re_RE[index + 1];
        last    = re_RE[index - 1];
        buf[i] = start;
        if(((start == '}') && (forward == '(')) || (start == '*') || (start == '?') 
             ||((start == '+') && (forward == '(') ) ){
            
            i++;
            buf[i] = '_';

        }else if(last == '\\'){
            i++;
            buf[i] = '_';

        }else if((start == '+' || start == '?' || start == '*') && (index + 1 >= temp->val_length)){
            i++;
            buf[i] = '_';
        }
        //std::cout << start << ":" << std::endl;
        i++;

    }
    buf[i] = '#';
    
    
    std::cout << buf << std::endl;
    if(temp->Token == CHLIST){
        
        tree_node * root ;
        root = (tree_node *)malloc(sizeof(tree_node));
        temp->root = root;
        root->right = NULL;
        root->left  = NULL;
        root->node_length = 1;
        char c_start    = 0;
        char c_forward  = 0;
        char c_last     = 0;
        int flag = 0;
        while(1){
            
            c_start = buf[flag];
            c_forward = buf[flag + 1];
            c_last    = buf[flag - 1];
            if(c_start == ']'){
                
                return 0;
            }
            
            if(c_start == '-'){
                char begin = c_last;
                char end   = c_forward;
                int  num   = c_forward - c_last;
                flag += 2;
                for(int i = 0;i <=num ;i++){
                    tree_node * elum;
                    elum = (tree_node *)malloc(sizeof(tree_node));
                    elum->buf[0] = begin + i;
                    elum->node_length = 1;
                    elum->right  = NULL;
                    elum->left   = NULL;
                    
                    if(root->node_length == 1){
                        root->right = elum;
                        root->left  = elum;
                        root->node_length = 0;
                    }else{
                        
                        root->left->right = elum;
                        root->left         = elum;
                    
                    }
                    
                }
                
            }else if(c_start == '\\'){
                
                tree_node * node ;
                node = (tree_node *)malloc(sizeof(tree_node));
                node->node_length = 2;
                node->buf[0] = c_start;
                node->buf[1] = c_forward;
                node->left   = NULL;
                node->right  = NULL;
                if(root->node_length == 1){
                        root->right = node;
                        root->left  = node;
                        root->node_length = 0;
                }else{
                    root->left->right = node;
                    root->left        = node;
                    
                }
                flag+=2;            
            }
            flag++;
        }  
    
    }

    if(temp->Token == RREEX){
        char start   = 0;
        char forward = 0;
        char last    = 0;
        int num = i;
        std::cout << "hello   world" << std::endl;
        //std::cout << buf << std::endl;
        for(int index = 0;index <= num ;index++){
            start = buf[index];
            forward = buf[index + 1];
            int in_bracket = 0;
            if(start == '{'){
                
                char name[10];
                int h = 0;
                memset(name,0,10);
                index++;
                while(1){
                    char obj = buf[index + h];
                    if(obj == '}'){
                        break;
                    }
                    name[h] = buf[index + h];
                    h++;
                }
                std::cout << "*" <<name << std::endl;
                index += h;
                tree_node * data;
                data = (tree_node *)malloc(sizeof(tree_node));
                memcpy(data->buf,name,h);
                data->node_length = h;
                data->left = NULL;
                data->right = NULL;
                S_data.push(data);  

            }else if(start == '_' || start == '?' || start == '*' || start == '+' || start == ')' || start == '(' 
                    ||  start == '|' || start == '\\'){
         
                if(S_opera.empty()){
                    tree_node * node;
                    node = (tree_node *)malloc(sizeof(tree_node));
                    node->node_length = 1;
                    node->left = NULL;
                    node->right = NULL;
                    node->buf[0] = start;
                    S_opera.push(node);
                }else{
                    
                    while(1){
                        char op;
                        if(S_opera.empty()){

                            tree_node *node = (tree_node *)malloc(sizeof(tree_node));
                            node->buf[0] = start;
                            node->node_length = 0;
                            node->right = NULL;
                            node->left  = NULL;
                            S_opera.push(node);
                            break;
                        }
                        tree_node *top = S_opera.top();
                        if(is_bigger(start,top->buf[0]) < 0){  
                            tree_node * node = (tree_node *)malloc(sizeof(tree_node));
                            node->node_length = 1;
                            node->buf[0] = start;
                            node->left = NULL;
                            node->right = NULL;
                            S_opera.push(node);
                            break;
                        }else if(is_bigger(start,top->buf[0]) > 0){
                            
                            do_oper(start,forward);
                            break;

                        }else if(is_bigger(start,top->buf[0]) == 0){
                            tree_node *top_node;
                            top_node = S_opera.top();
                            S_opera.pop();
                            do_oper(top_node->buf[0],start);
                        }
                        
                    }
                           
                }
                
            }else{ /* '#' and other letter*/      
                tree_node *node = (tree_node *)malloc(sizeof(tree_node));
                node->buf[0] = start;
                node->node_length = 0;
                node->right = NULL;
                node->left  = NULL;
                S_data.push(node);
                
            }
        }
        while(!S_opera.empty()){
            
            tree_node * node ;
            node = (tree_node *)malloc(sizeof(tree_node));
            node = S_opera.top();
            S_opera.pop();
            
            do_oper(node->buf[0],' ');

        }
        //std::cout << "do" << std::endl;
        temp->root = S_data.top();
        //std::cout << "done" << std::endl;
        S_data.pop();
        test_tree();
    }
    
        
}

int test_list(){
    lex_word *node;
    node = word_table[1].next;
    while(node != NULL){      
        tree_node * temp;
        temp = node->root;
        int i = 0;
        while(temp != NULL){
            i = temp->node_length;
            for(int j = 0;j < i;j++){       
                std::cout << temp->buf[j]<< std::endl;
            }
            temp = temp->right;
        }
        node = node->next;
    }
}

int is_bigger(char new_char,char top_char){

    int level_new = 0;
    int level_top = 0;
    
    level_new = get_level(new_char);
    level_top = get_level(top_char);

    return (level_new - level_top);

}

int get_level(char ch){
    
    if((ch == '\\')){
        return 5;
    }
    if((ch == '(') || (ch == ')') || (ch == '[') || (ch == ']')){
        return 4;
    }
    if((ch == '*') || (ch == '+') || (ch == '_') || (ch == '?')){
        return 3;
    }
    if((ch == '^') || (ch == '$')){
        return 2;
    }
    if((ch == '|')){
        return 1;
    }
}

int do_oper(char ch,char forward){
    
    if(ch == '+'){
        tree_node *node ;
        node = (tree_node *)malloc(sizeof(tree_node));
        tree_node *obj;
        obj = S_data.top();
        S_data.pop();
        node->node_length = 1;
        node->buf[0] = '+';
        node->left   = obj;
        S_data.push(node);

    }else if(ch == '_'){
        tree_node *left  = NULL;
        tree_node *right = NULL;
        left = S_data.top();
        S_data.pop();
        if(!S_data.empty()){  
            right = S_data.top();
            S_data.pop();
        }
        tree_node * node = (tree_node *)malloc(sizeof(tree_node));
        node->node_length = 1;
        node->buf[0] = '_';
        node->left = left;
        node->right = right;
        S_data.push(node);
    }else if(ch == '\\'){
        tree_node *node;
        node = (tree_node *)malloc(sizeof(tree_node));
        node->node_length = 1;
        node->buf[0] = forward;
        S_data.push(node);

    }else if(ch == '*'){
        tree_node *node;
        node = (tree_node *)malloc(sizeof(tree_node));
        tree_node *left;
        left = S_data.top();
        S_data.pop();
        node->buf[0] = '*';
        node->node_length = 1;
        node->left = left;
        node->right = NULL;
        S_data.push(left);

    }else if(ch == '('){
        tree_node *node;
        node = (tree_node *)malloc(sizeof(tree_node));
        node->node_length = 0;
        node->buf[0] = '(';
        S_opera.push(node);
    }else if(ch == ')'){
        while(1){
            tree_node * node;
            node = S_opera.top();
            S_opera.pop();
            if(node->buf[0] == '('){
                break;
            }
            
            do_oper(node->buf[0],0);
            
        }    
            
            
    }else if(ch == '|'){
        
        tree_node *left = NULL;
        tree_node *right = NULL;
        tree_node *node ;
        node = (tree_node *)malloc(sizeof(tree_node));
        left = S_data.top();
        S_data.pop();
        if(S_data.empty()){
            right = S_data.top();
            S_data.pop();
        }
        node->buf[0] = '|';
        node->node_length = 1;
        node->right = right;
        node->left  = left;
        S_data.push(node);
    
    }else{
    

    }

}

int test_tree(){
        
    lex_word * node;
    node = word_table[1].next;
    while(node != NULL){
        
        if(node->Token == RREEX){
            find_tree(node->root);    
        }
        node = node->next;
        
    }
    

}
int find_tree(tree_node *node){
    
    std::cout << "left: " <<  node->left->buf << std::endl;
    std::cout << "right: " <<  node->right->buf << std::endl;
    std::cout << "mid: " <<  node->buf << std::endl;


}
