%{
    
    LT,LE,EQ,NE,GT,GE,
    IF,THEN,ELSE,ID,NUMBER,RELOP,
    INT,DOUBLE,FLOAT,BREAK,RETURN,
    LK.LLK.RK,RRK,FEN,DOU,KEYWORD

%}

delim    [\t\n]
letter   [A-Za-z]
digit    [0-9]
id       {letter}({letter}|{digit})*;
number   {digit}+(\.{digit}+)?(E?{digit}+)?;

%%

{ws}     {}
if       {return (IF);}
then     {return (THEN);}
else     {return (ELSE);}
int      {yylval = INT;return (INT);}
double   {yylval = DOUBLE;return (DOUBLE);}
float    {yylval = FLOAT;return (DOUBLE);}
{id}     {yylval = (int) installID();return (ID);}
{number} {yylval = (int) installNum();return (NUMBER);}
"<"      {yylval = LT;return (RELOP);}
"<="     {yylval = LE;return (RELOP);}
"="      {yylval = EQ;return (RELOP);}
"<>"     {yylval = NE;return (RELOP);}
">"      {yylval = GT;return (RELOP);}
">="     {yylval = GE;return (RELOP);}
"("      {yylval = LK;return (RELOP);}
")"      {yylval = RK;return (RELOP);}
"{"      {yylval = LLK;return (RELOP);}
"}"      {yylval = RRK;return (RELOP);}
";"      {yylval = FEN;return (RELOP);}
","      {yylval = DOU;return (RELOP);}
%%

int installID(){  }

int installNum(){  }


