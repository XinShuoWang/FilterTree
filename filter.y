%{
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "ast.h"

int yydebug=0;

extern int yylex();
extern struct Value* val;

void yyerror(const char* s) {
	fprintf(stderr, "Parse error: %s\n", s);
	exit(1);
}

%}

%token<ival> T_INT
%token<fval> T_FLOAT
%token<sval> T_PARAMETER

%token T_LEFT_BRACKET T_RIGHT_BRACKET T_COMMA T_COLON
%token T_AND T_OR
%token T_LESS T_LESS_OR_EQUAL T_EQUAL T_NOT_EQUAL T_GREATER T_GREATER_OR_EQUAL
%token T_TO_YEAR

%start  filter

%union {
	int ival;
	float fval;
      char* sval;
}


%%

filter : T_AND T_LEFT_BRACKET filter T_RIGHT_BRACKET
       {
            struct Value* p = (struct Value*)malloc(sizeof(struct Value));
            p->type_ = OP;
            p->op_size_ = 4;
            p->op_ = (char*)malloc(p->op_size_);
            memcpy(p->op_, "and\0", 3);
            val = p;
            printf("and filter \n");
       }
       | T_OR T_LEFT_BRACKET filter T_RIGHT_BRACKET
       {
            printf("or filter \n");
       }
       | judge T_COMMA filter
       {
            printf("judge filter \n");
       }
       | judge
       {
            printf("judge \n");
       }
       ;


judge : T_LESS T_LEFT_BRACKET func T_COMMA func T_RIGHT_BRACKET
      {
            printf("less \n");
      }
      | T_LESS_OR_EQUAL T_LEFT_BRACKET func T_COMMA func T_RIGHT_BRACKET
      {
            printf("less or equal \n");
      }
      | T_EQUAL T_LEFT_BRACKET func T_COMMA func T_RIGHT_BRACKET
      {
            printf("equal \n");
      }
      | T_NOT_EQUAL T_LEFT_BRACKET func T_COMMA func T_RIGHT_BRACKET
      {
            printf("not equal \n");
      }
      | T_GREATER T_LEFT_BRACKET func T_COMMA func T_RIGHT_BRACKET
      {
            printf("greater \n");
      }
      | T_GREATER_OR_EQUAL T_LEFT_BRACKET func T_COMMA func T_RIGHT_BRACKET
      {
            printf("greater or equal \n");
      }
      ;


func : T_TO_YEAR T_LEFT_BRACKET param T_RIGHT_BRACKET
      {
            printf("toyear \n");
      }
      | param
      {
            printf("param \n");
      }
      ;


param : T_INT
     {
           printf("int %d \n", $1);
     }
     | T_FLOAT
     {
           printf("float %f \n", $1);
     }
     | T_PARAMETER
     {
           printf("col name %s \n", $1);
     }
     ;

%%