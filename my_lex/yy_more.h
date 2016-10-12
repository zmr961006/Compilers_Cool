/*************************************************************************
	> File Name: yy_more.h
	> Author: 
	> Mail: 
	> Created Time: 2016年10月10日 星期一 20时50分33秒
 ************************************************************************/

#ifndef _YY_MORE_H
#define _YY_MORE_H

int read_buf(sys_buf *buf);
int init_buf();
int ex_re();
int init_RE(char *buf);
int RE_to_tree();


int lexyy(int argc,char **argv);
int lex_ansylse();

int is_letter(char c);
int is_digit(char c);
int is_sysntx(char c);



#endif
