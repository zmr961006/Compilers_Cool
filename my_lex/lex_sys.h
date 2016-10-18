/*************************************************************************
	> File Name: lex_sys.h
	> Author: 
	> Mail: 
	> Created Time: 2016年10月14日 星期五 14时50分05秒
 ************************************************************************/

#ifndef _LEX_SYS_H
#define _LEX_SYS_H


int lex_sys();

int lex_word_enum();

int lex_RE();

int lex_word_enum();

int get_RE_tree(lex_word * temp);

int test_list();

int is_bigger(char new_char,char top_char);

int get_level(char ch);

int do_oper(char ch,char forward);

int test_tree();

int find_tree(tree_node * node);

int is_onepart(char ch,char ch2);
#endif
