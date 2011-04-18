%{
#include "Error.h"
#include "Type.h"
#include "Expr.h"
#include "Symbol.h"
#include "Func.h"
#include <string>
#include <map>
#include <cstdlib>
#include "fturtlec.tab.hpp" // created via bison -d fturtlec.ypp
using namespace std;
map<string,string*> namePool;
%}

%%
[0-9]+                  {return yylval.i = atoi(yytext); INT_LIT;}
[0-9]+\.[0-9]+          {return yylval.f = atof(yytext); FLOAT_LIT;}
false                   {return yylval.b = false; BOOL_LIT;}
true                    {return yylval.b = true; BOOL_LIT;}
bool                    {return BOOL;}
int                     {return INT;}
float                   {return FLOAT;}
if                      {return IF;}
else                    {return ELSE;}
let                     {return LET;}
or                      {return OR;}
and                     {return AND;}
not                     {return NOT;}
length                  {return LENGTH;}
"="                     {return yytext[0];}
"=="                    {return EQ;}
"!="                    {return NE;}
"<"                     {return yytext[0];}
"<="                    {return LE;}
">"                     {return yytext[0];}
">="                    {return GE;}
"+"                     {return yytext[0];}
"-"                     {return yytext[0];}
"*"                     {return yytext[0];}
"/"                     {return yytext[0];}
"%"                     {return yytext[0];}
"("                     {return yytext[0];}
")"                     {return yytext[0];}
"{"                     {return yytext[0];}
"}"                     {return yytext[0];}
"["                     {return yytext[0];}
"]"                     {return yytext[0];}
","                     {return yytext[0];}
";"                     {return yytext[0];}
[a-zA-Z_][a-zA-Z_0-9]*  {string name(yytext);
                         map<string,string*>::iterator iter = 
                               namePool.find(name);
                         if (iter == namePool.end())
                           yylval.s = namePool[name] = new string(name);
                         else
                           yylval.s = iter->second;;
                         return ID;}
[ \t\r\f]+              { ; }
#.*                     { ; }
"\n"                    {yylineno++;}
%%


