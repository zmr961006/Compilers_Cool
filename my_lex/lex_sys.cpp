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
    //std::cout << "~~~~~~~~" << std::endl;
    test_tree();
}

stack<tree_node*> S_data ;
stack<tree_node*> S_opera;
stack<tree_node*> S_temp;

int get_RE_tree(lex_word * temp){

    int i = 0;
    char re_RE[100];
    char re_WORD[100];
    memset(re_RE,0,100);
    memset(re_WORD,0,100);
    //std::cout << "the token " << temp->Token << std::endl;
    memcpy(re_RE,temp->val_word,temp->val_length);
    memcpy(re_WORD,temp->key_word,temp->length);
    
    int postion = 1;   
    
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

        }else if((start == '+' || start == '?' || start == '*' || start == '}') && (index + 1 >= temp->val_length)){
            i++;
            buf[i] = '_';
        }else if((start == '}') && (forward == '{')){
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
        //std::cout << "hello   world" << std::endl;
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
                //std::cout << "*" <<name << std::endl;
                index += h;
                tree_node * data;
                data = (tree_node *)malloc(sizeof(tree_node));
                memcpy(data->buf,name,h);
                data->node_length = h;
                data->left = NULL;
                data->right = NULL;
                data->number = postion;
                data->firstpos = NULL;
                data->lastpos  = NULL;
                data->fellowpos = NULL;
                data->first_num = 0;
                data->last_num  = 0;
                data->operato = 0 ;
                postion++;
                S_data.push(data);  
                //std::cout << "push " << data->buf << std::endl;
            }else if(start == '_' || start == '?' || start == '*' || start == '+' || start == ')' || start == '(' 
                    ||  start == '|' || start == '\\'){
         
                if(S_opera.empty()){
                    tree_node * node;
                    node = (tree_node *)malloc(sizeof(tree_node));
                    node->node_length = 1;
                    node->left = NULL;
                    node->right = NULL;
                    node->buf[0] = start;
                    node->firstpos = NULL;
                    node->lastpos  = NULL;
                    node->fellowpos = NULL;
                    node->first_num = 0;
                    node->last_num = 0;
                    node->fellow_num = 0;
                    node->operato = 1;
                    S_opera.push(node);
                    //std::cout << "push " << node->buf << std::endl;
                }else{
                    
                    while(1){
                        char op;
                        //std::cout << "HHHHHHHHHHHHHHH" << std::endl;
                        if(S_opera.empty()){

                            tree_node *node = (tree_node *)malloc(sizeof(tree_node));
                            node->buf[0] = start;
                            node->node_length = 0;
                            node->right = NULL;
                            node->left  = NULL;
                            node->firstpos = NULL;
                            node->lastpos  = NULL;
                            node->fellowpos = NULL;
                            node->first_num = 0;
                            node->last_num = 0;
                            node->fellow_num = 0;
                            node->operato = 1;
                            S_opera.push(node);
                            //std::cout << "push " << node->buf << std::endl;
                            break;
                        }
                        tree_node *top = S_opera.top();
                        if(is_bigger(start,top->buf[0]) < 0){  
                            tree_node * node = (tree_node *)malloc(sizeof(tree_node));
                            node->node_length = 1;
                            node->buf[0] = start;
                            node->left = NULL;
                            node->right = NULL;
                            node->firstpos = NULL;
                    	    node->lastpos  = NULL;
                    	    node->fellowpos = NULL;
                    	    node->first_num = 0;
                    	    node->last_num = 0;
                    	    node->fellow_num = 0;
                            node->operato = 1;
                            S_opera.push(node);
                            //std::cout << "push " << node->buf << std::endl;
                            break;
                        }else if(is_bigger(start,top->buf[0]) > 0){
                            
                            do_oper(start,forward);
                            break;

                        }else if(is_bigger(start,top->buf[0]) == 0){
                            tree_node *top_node;
                            top_node = S_opera.top();
                            S_opera.pop();
                            //std::cout << "pop " << top_node->buf << std::endl ;
                            if(is_onepart(start,top_node->buf[0])){  
                                do_oper(top_node->buf[0],start);
                            }else{
                                S_opera.push(top_node);
                                do_oper(start,top_node->buf[0]);
                                break;
                            }
                            
                        }
                        /*if(start == '\\'){
                            std::cout << "next" << start << std::endl;
                            index++;
                        }*/
                        
                    }
                    if(start == '\\'){
                        //std::cout << "next" << start << std::endl;
                        index+=1;
                    }
                           
                }
                
            }else{ /* '#' and other letter*/      
                
                tree_node *node = (tree_node *)malloc(sizeof(tree_node));
                node->buf[0] = start;
                node->node_length = 0;
                node->right = NULL;
                node->left  = NULL;
                node->firstpos = NULL;
                node->lastpos  = NULL;
                node->fellowpos = NULL;
                node->first_num = 0;
                node->last_num = 0;
                node->fellow_num = 0;
                node->operato  = 0;
                //std::cout << node->buf << std::endl;
                node->number = postion;
                postion++;
                S_data.push(node);
                  //std::cout << "push " << node->buf << std::endl;
            }
        }
        while(!S_opera.empty()){
            
            tree_node * node ;
            node = (tree_node *)malloc(sizeof(tree_node));
            node = S_opera.top();
            S_opera.pop();
            //std::cout << "pop " << node->buf << std::endl;
            do_oper(node->buf[0],' ');

        }
        
        temp->root = S_data.top();
        
        S_data.pop();
        //std::cout << "pop " << temp->root->buf << std::endl;
        //test_tree();
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
                //std::cout << temp->buf[j]<< std::endl;
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
    if((ch == '*') || (ch == '+')  || (ch == '?') || (ch == '_')){
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
        //std::cout << "pop " << obj->buf << std::endl;
        node->node_length = 1;
        node->buf[0] = '+';
        node->left   = obj;
        node->right  = NULL;
        node->firstpos = NULL;
        node->lastpos  = NULL;
        node->fellowpos = NULL;
        node->first_num = 0;
        node->last_num = 0;
        node->fellow_num = 0;
        node->operato  = 1;
        S_data.push(node);
        //std::cout << "push " << node->buf << std::endl;
    }else if(ch == '_'){
        tree_node *left  = NULL;
        tree_node *right = NULL;
        left = S_data.top();
        S_data.pop();
        //std::cout << "left : pop " << left->buf << std::endl;
        if(!S_data.empty()){  
            right = S_data.top();
            //std::cout << "right :pop " << right->buf << std::endl;
            S_data.pop();
        }
        tree_node * node = (tree_node *)malloc(sizeof(tree_node));
        node->node_length = 1;
        node->buf[0] = '_';
        node->left = left;
        node->right = right;
        node->firstpos = NULL;
        node->lastpos  = NULL;
        node->fellowpos = NULL;
        node->first_num = 0;
        node->last_num = 0;
        node->fellow_num = 0;
        node->operato = 1;
        S_data.push(node);
        //std::cout << "push " << node->buf << std::endl;
    }else if(ch == '\\'){

        tree_node *node;
        node = (tree_node *)malloc(sizeof(tree_node));
        node->node_length = 1;
        node->buf[0] = forward;
        node->left = NULL;
        node->right = NULL;
        node->firstpos = NULL;
        node->lastpos  = NULL;
        node->fellowpos = NULL;
        node->first_num = 0;
        node->last_num = 0;
        node->fellow_num = 0;
        node->operato  = 0;
        S_data.push(node);
        //std::cout << "push " << node->buf << std::endl;

    }else if(ch == '*'){
        tree_node *node;
        node = (tree_node *)malloc(sizeof(tree_node));
        tree_node *left;
        left = S_data.top();
        S_data.pop();
        //std::cout << "pop " << left->buf << std::endl;
        node->buf[0] = '*';
        node->node_length = 1;
        node->left = left;
        node->right = NULL;
        node->firstpos = NULL;
        node->lastpos  = NULL;
        node->fellowpos = NULL;
        node->first_num = 0;
        node->last_num = 0;
        node->fellow_num = 0;
        node->operato = 1;
        S_data.push(node);
        //std::cout << "push " << node->buf << std::endl;
    }else if(ch == '('){
        tree_node *node;
        node = (tree_node *)malloc(sizeof(tree_node));
        node->node_length = 0;
        node->buf[0] = '(';
        node->right = NULL;
        node->left  = NULL;
        node->firstpos = NULL;
        node->lastpos  = NULL;
        node->fellowpos = NULL;
        node->first_num = 0;
        node->last_num = 0;
        node->fellow_num = 0;
        S_opera.push(node);
        //std::cout << "push " << node->buf << std::endl;
    }else if(ch == ')'){
        while(1){
            tree_node * node;
            node = S_opera.top();
            S_opera.pop();
          //  std::cout << " pop from s_opera " << node->buf << std::endl;
            if(node->buf[0] == '('){
                break;
            }
            S_temp.push(node);
            //std::cout << "push to S_temp " << node->buf << std::endl;
            //do_oper(node->buf[0],0);
        }    
        while(!S_temp.empty()){
            tree_node *node ;
            node = S_temp.top();
            S_temp.pop();
            //std::cout << "pop from s_temp " << node->buf << std::endl;
            do_oper(node->buf[0],' ');
        }    
            
    }else if(ch == '|'){
        
        tree_node *left = NULL;
        tree_node *right = NULL;
        tree_node *node ;
        node = (tree_node *)malloc(sizeof(tree_node));
        left = S_data.top();
        S_data.pop();
        //std::cout << "pop " << left->buf << std::endl;
        if(!S_data.empty()){
            right = S_data.top();
            S_data.pop();
           // std::cout << "pop " << right->buf << std::endl;
        }
        node->buf[0] = '|';
        node->node_length = 1;
        node->right = right;
        node->left  = left;
        node->firstpos = NULL;
        node->lastpos  = NULL;
        node->fellowpos = NULL;
        node->first_num = 0;
        node->last_num = 0;
        node->fellow_num = 0;
        node->operato = 1;
        S_data.push(node);
        //std::cout << "push " << node->buf << std::endl;
    }else if(ch == '?'){
        tree_node *node;
        node = (tree_node *)malloc(sizeof(tree_node));
        tree_node *left;
        left = S_data.top();
        S_data.pop();
        node->buf[0] = '?';
        node->node_length = 1;
        node->left = left;
        node->right = NULL;
        node->firstpos = NULL;
        node->lastpos  = NULL;
        node->fellowpos = NULL;
        node->first_num = 0;
        node->last_num = 0;
        node->fellow_num = 0;
        S_data.push(node);

    }

}

int test_tree(){
        
    lex_word * node;
    node = word_table[1].next;
    while(node != NULL){
        
        if(node->Token == RREEX){
            find_tree(node->root);  /*建立语法分析树*/
            find_fellow(node->root);
            test_fellowpos(node->root);
        }
        std::cout << "next tree" << std::endl;
        node = node->next;
        
    }
    

}
int find_tree(tree_node *node){
    

    if(node){
        
        find_tree(node->right);
        find_tree(node->left);
        
        get_pos(node);
        //test_pos(node->lastpos); 
    }

}

int find_fellow(tree_node * node){
    
    if(node){

        find_fellow(node->right);
        find_fellow(node->left);
        get_and_test_fellow(node);
        
    }

}


int is_onepart(char ch,char ch2){
    
    if(ch == ch2){
        return 1;
    }
    if((ch2 == '*') || (ch2 == '?') || (ch2 == '+') ){
        return 1;
    }
    if( (ch == '*') || (ch == '?') || (ch == '+') ){
        return 0;
    }

}


int get_pos(tree_node *node){
    
        
    get_firstpos(node,FIRSTPOS);
    get_lastpos(node,LASTPOS);
    

}



int get_firstpos(tree_node * node, int type){

    if((node->left == NULL) && (node->right == NULL)){   /*如果是叶子节点则first 就是自己*/
        set *one = (set *)malloc(sizeof(set));
        node->first_num = 1;
        one->buf[0] = node->buf[0];
        one->node = node;
    
        one->next = NULL;
        node->nullable = 0;
        node->firstpos = one;
        return 0;
    }
    
    if(node->buf[0] == '|' ){
        
        tree_node * left = node->left;
        tree_node * right = node->right;
        //std::cout << "the number " << node->left->first_num << " " << node->right->first_num << std::endl;
        set * temp = left->firstpos;
        while(temp != NULL){
            set * num;
            num = (set *)malloc(sizeof(set));
            num->buf[0] = temp->buf[0];
            //std::cout << "the left " << temp->buf[0] << std::endl;
            num->node   = temp->node;
            insert_set(node,num,FIRSTPOS);
            node->first_num++;
            temp = temp->next;
            
        }
        //std::cout << "the firsipos " << node->firstpos->buf[0] << std::endl;
        temp = right->firstpos;
        while(temp != NULL){
            set *num;
            num = (set *)malloc(sizeof(set));
            num->buf[0] = temp->buf[0];
            //std::cout << "the right " << temp->buf[0] << std::endl;
            num->node   = temp->node;
            insert_set(node,num,FIRSTPOS);
            node->first_num++;
            temp = temp->next;
        }
        node->nullable = ((left->nullable) | (right->nullable));

    }else if(node->buf[0] == '_'){
        
        if(node->right->nullable){     /*这里由于树的左右反掉了，所以我们就按照反方向对待*/
            tree_node * left = node->left;
            tree_node * right = node->right;
            set * temp = left->firstpos;
            while(temp != NULL){
            	set * num;
            	num = (set *)malloc(sizeof(set));
            	num->buf[0] = temp->buf[0];
                num->node   = temp->node;
            	insert_set(node,num,FIRSTPOS);
            	node->first_num++;
            	temp = temp->next;
            }
            temp = right->firstpos;
            while(temp != NULL){
            	set *num;
            	num = (set *)malloc(sizeof(set));
            	num->buf[0] = temp->buf[0];
                num->node   = temp->node;
            	insert_set(node,num,FIRSTPOS);
            	node->first_num++;
            	temp = temp->next;
            }
        }else{
            set_copy(node,node->right->firstpos,FIRSTPOS);
        }    

    }else if(node->buf[0] == '*'){
        
        node->nullable = 1;
        
        set_copy(node,node->left->firstpos,FIRSTPOS);
    }


}


int is_nullable(tree_node * node){
    
    if(node == NULL){
        return 1;
    }
    if((node->buf[0] == '*') || (node->buf[0] == '?')){
        return 1;
    }
        
    
}

int insert_set(tree_node *node,set *num,int type){
    
    set *temp;
    if(type == FIRSTPOS){  
        temp = node->firstpos;

        if(node->first_num == 0){
            node->firstpos = num;
            return 0;
        }
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = num;
        num->next = NULL;
    }else if(type == LASTPOS){
        temp = node->lastpos;
        if(node->last_num == 0){
            node->lastpos = num;
            return 0;
        }
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = num;
        num->next = NULL;

    }else if(type == FELLOWPOS){
        temp = node->fellowpos;
        if(node->fellow_num == 0){
            node->fellowpos = num;
            return 0;
        }
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = num;
        num->next = NULL;
    }
}


int set_copy(tree_node * node,set * num,int type){

    set * temp = num;
    if(type == FIRSTPOS){    
        while(temp != NULL){
            set * obj = (set *)malloc(sizeof(set));
            obj->buf[0] = temp->buf[0];
            obj->node = temp->node;
            insert_set(node,obj,FIRSTPOS);
            node->first_num++;
            temp = temp->next;
        }
    }else if(type == LASTPOS){
        while(temp != NULL){
            set *obj = (set *)malloc(sizeof(set));
            obj->buf[0] = temp->buf[0];
            obj->node = temp->node;
            insert_set(node,obj,LASTPOS);
            node->last_num++;
            temp = temp->next;
        }

    }else if(type == FELLOWPOS){
        
        while(temp != NULL){
            set *obj = (set *)malloc(sizeof(set));
            obj->buf[0] = temp->buf[0];
            obj->node = temp->node;
            insert_set(node,obj,FELLOWPOS);
            node->fellow_num++;
            temp = temp->next;
        }


    }
}

int test_pos(set * pos){
    
    set * temp;
    temp = pos;
    if(pos == NULL){
        /*符号节点没有fellow 集合，#就是最后的接受状态*/
        //std::cout << "the fellow is NULL" << std::endl;
    }
    while(temp != NULL){
        //std::cout << temp->buf[0] << std::endl;
        std::cout << temp->node->buf << std::endl;
        temp = temp->next;
    }
    
    std::cout << "~~~~~~~~" << std::endl;

}

int get_lastpos(tree_node * node, int type){

    if((node->left == NULL) && (node->right == NULL)){   /*如果是叶子节点则first 就是自己*/
        set *one = (set *)malloc(sizeof(set));
        node->last_num = 1;
        one->buf[0] = node->buf[0];
        one->node = node;
        one->next = NULL;
        node->nullable = 0;
        node->lastpos = one;
        return 0;
    }
    
    if(node->buf[0] == '|' ){
        
        tree_node * left = node->left;
        tree_node * right = node->right;
        //std::cout << "the number " << node->left->first_num << " " << node->right->first_num << std::endl;
        set * temp = left->lastpos;
        while(temp != NULL){
            set * num;
            num = (set *)malloc(sizeof(set));
            num->buf[0] = temp->buf[0];
            //std::cout << "the left " << temp->buf[0] << std::endl;
            num->node   = temp->node;
            insert_set(node,num,LASTPOS);
            node->last_num++;
            temp = temp->next;
            
        }
        //std::cout << "the firsipos " << node->firstpos->buf[0] << std::endl;
        temp = right->lastpos;
        while(temp != NULL){
            set *num;
            num = (set *)malloc(sizeof(set));
            num->buf[0] = temp->buf[0];
            //std::cout << "the right " << temp->buf[0] << std::endl;
            num->node   = temp->node;
            insert_set(node,num,LASTPOS);
            node->last_num++;
            temp = temp->next;
        }
        node->nullable = ((left->nullable) | (right->nullable));
        //std::cout << "the firsipos " << node->firstpos->next->buf[0] << std::endl;

    }else if(node->buf[0] == '_'){
        //std::cout << "the cat nullable is " << node->left->nullable << " ~ " << is_nullable(node->left) << std::endl; 
        if(node->left->nullable){     /*这里由于树的左右反掉了，所以我们就按照反方向对待*/
            tree_node * left = node->left;
            tree_node * right = node->right;
            set * temp = left->lastpos;
            while(temp != NULL){
            	set * num;
            	num = (set *)malloc(sizeof(set));
            	num->buf[0] = temp->buf[0];
                num->node   = temp->node;
            	insert_set(node,num,LASTPOS);
            	node->last_num++;
            	temp = temp->next;
            }
            temp = right->lastpos;
            while(temp != NULL){
            	set *num;
            	num = (set *)malloc(sizeof(set));
            	num->buf[0] = temp->buf[0];
                num->node   = temp->node;
            	insert_set(node,num,LASTPOS);
            	node->last_num++;
            	temp = temp->next;
            }
        }else{
            set_copy(node,node->left->lastpos,LASTPOS);
        }    

    }else if(node->buf[0] == '*'){
        
        node->nullable = 1;
        
        set_copy(node,node->left->lastpos,LASTPOS);
    }


}

int is_opera(tree_node * node){

    if(node->operato){
        
        return 1;

    }else{

        return 0;
    }

}

int get_fellow(tree_node *node,int type){

    char temp_buf = node->buf[0];
    //std::cout << "prove : " << is_opera(node) << std::endl; 
    if(is_opera(node) && (node->buf[0] == '*')){
        set * temp;
        temp = node->lastpos;
        
        while(temp != NULL){
            
            set_copy(temp->node,node->firstpos,FELLOWPOS);
            //std::cout << "ooooooooo" << std::endl;
            //test_pos(temp->node->fellowpos);

            //std::cout << "000000000" << std::endl;
            temp = temp->next;

        }
        
    }else if(is_opera(node) && (node->buf[0] == '_')){
        set * temp;
        temp = node->right->lastpos;
        while(temp != NULL){
            set_copy(temp->node,node->left->firstpos,FELLOWPOS);
            temp = temp->next;
        }
    
    }

}


int get_and_test_fellow(tree_node *node){

    get_fellow(node,FELLOWPOS);
    
}

int test_fellowpos(tree_node *node){
    
    if(node){

        test_fellowpos(node->right);
        test_fellowpos(node->left);

        test_pos(node->fellowpos);
    }

}


