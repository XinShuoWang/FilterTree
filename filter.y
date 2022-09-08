%{
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "ast.h"
#include "debug.h"

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
%token T_TO_YEAR T_LENGTH


%type<val> filter hyper logic judge func param


%start  filter

%union {
	int ival;
	float fval;
      char* sval;
      struct Value* val;
}


%%

filter : logic
      {
            val = $1;
      }
      ;


logic : T_AND T_LEFT_BRACKET hyper T_RIGHT_BRACKET
       {
            struct Value* p = new_value(AND);
            p->child_num_ = $3->child_num_;
            p->child_ = $3->child_;
            free($3);
            $$ = p;
            INFO("and filter \n");
       }
       | T_OR T_LEFT_BRACKET hyper T_RIGHT_BRACKET
       {
            struct Value* p = new_value(OR);
            p->child_num_ = $3->child_num_;
            p->child_ = $3->child_;
            free($3);
            $$ = p;
            INFO("or filter \n");
       }
       ;

/*这里的过程类似于DFS到底，然后返回的场景。*/
hyper : hyper T_COMMA judge
      {
            append_child($1, $3);
            $$ = $1;
      }
      | hyper T_COMMA logic
      {
            append_child($1, $3);
            $$ = $1;
      }
      | judge
      {
            struct Value* p = new_value(NONE);
            append_child(p, $1);
            $$ = p;
      }
      | logic
      {
            struct Value* p = new_value(NONE);
            append_child(p, $1);
            $$ = p;
      }


judge : T_LESS T_LEFT_BRACKET func T_COMMA func T_RIGHT_BRACKET
      {
            struct Value* p = new_value(LESS);
            append_child(p, $3);
            append_child(p, $5);
            $$ = p;
            INFO("less \n");
      }
      | T_LESS_OR_EQUAL T_LEFT_BRACKET func T_COMMA func T_RIGHT_BRACKET
      {
            struct Value* p = new_value(LESS_OR_EQUAL);
            append_child(p, $3);
            append_child(p, $5);
            $$ = p;
            INFO("less or equal \n");
      }
      | T_EQUAL T_LEFT_BRACKET func T_COMMA func T_RIGHT_BRACKET
      {
            struct Value* p = new_value(EQUAL);
            append_child(p, $3);
            append_child(p, $5);
            $$ = p;
            INFO("equal \n");
      }
      | T_NOT_EQUAL T_LEFT_BRACKET func T_COMMA func T_RIGHT_BRACKET
      {
            struct Value* p = new_value(NOT_EQUAL);
            append_child(p, $3);
            append_child(p, $5);
            $$ = p;
            INFO("not equal \n");
      }
      | T_GREATER T_LEFT_BRACKET func T_COMMA func T_RIGHT_BRACKET
      {
            struct Value* p = new_value(GREATER);
            append_child(p, $3);
            append_child(p, $5);
            $$ = p;
            INFO("greater \n");
      }
      | T_GREATER_OR_EQUAL T_LEFT_BRACKET func T_COMMA func T_RIGHT_BRACKET
      {
            struct Value* p = new_value(GREATER_OR_EQUAL);
            append_child(p, $3);
            append_child(p, $5);
            $$ = p;
            INFO("greater or equal \n");
      }
      ;


func : T_TO_YEAR T_LEFT_BRACKET param T_RIGHT_BRACKET
      {
            struct Value* p = new_value(TO_YEAR);
            append_child(p, $3);
            $$ = p;
            INFO("toyear \n");
      }
      | T_LENGTH T_LEFT_BRACKET param T_RIGHT_BRACKET
      {
            struct Value* p = new_value(LENGTH);
            append_child(p, $3);
            $$ = p;
            INFO("length \n"); 
      }
      | param
      {
            $$ = $1;
            INFO("param \n");
      }
      ;


param : T_INT
     {
           struct Value* p = new_int_value($1);
           $$ = p;
           INFO("int %d \n", $1);
     }
     | T_FLOAT
     {
           struct Value* p = new_float_value($1);
           $$ = p;
           INFO("float %f \n", $1);
     }
     | T_PARAMETER
     {
           struct Value* p = new_string_value($1, strlen($1));
           $$ = p;
           INFO("col name %s \n", $1);
     }
     ;

%%