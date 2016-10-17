%{
    
    LT,LE,EQ,NE,GT,GE,
    IF,THEN,ELSE,ID,NUMBER,RELOP,
    INT,DOUBLE,FLOAT,BREAK,RETURN

%}


delim    [\t\n];
ws       {delim}+;
letter   [A-Za-z];
digit    [0-9];
id       {letter}({letter}|{digit})*;


%%

{ws}     {}
if       {return (IF);}
then     {return (THEN);}
else     {return (ELSE);}
{id}     {yylval = (int) installID();return (ID);}
{number} {yylval = (int) installNum();return (NUMBER);}
"<"      {yylval = LT;return (RELOP);}
"<="     {yylval = LE;return (RELOP);}
"="      {yylval = EQ;return (RELOP);}
"<>"     {yylval = NE;return (RELOP);}
">"      {yylval = GT;return (RELOP);}
">="     {yylval = GE;return (RELOP);}

%%

int installID(){  }

int installNum(){  }


