%option noyywrap

%{
#include "filter.tab.h"
%}

%%

[ \t]	                   ; // ignore all whitespace
[0-9]+\.[0-9]+ 	           {yylval.fval = atof(yytext); return T_FLOAT;}
-?[0-9]+		               {yylval.ival = atoi(yytext); return T_INT;}

"("		                   {return T_LEFT_BRACKET;}
")"		                   {return T_RIGHT_BRACKET;}
","                        {return T_COMMA;}
"'"                        {return T_COLON;}

"and"                      {return T_AND;}
"or"                       {return T_OR;}

"less"                     {return T_LESS;}
"lessOrEquals"             {return T_LESS_OR_EQUAL;}
"equals"                   {return T_EQUAL;}
"notEquals"                {return T_NOT_EQUAL;}
"greater"                  {return T_GREATER;}
"greaterOrEquals"          {return T_GREATER_OR_EQUAL;}

"toYear"                   {return T_TO_YEAR;}
"length"                   {return T_LENGTH;}

[[:alnum:]_]+              {yylval.sval = strdup(yytext); return T_PARAMETER;}

%%