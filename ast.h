#ifndef AST_H
#define AST_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

enum ValueType
{
    NONE,
    /*Logic*/
    AND,
    OR,
    /*compare*/
    LESS,
    LESS_OR_EQUAL,
    EQUAL,
    NOT_EQUAL,
    GREATER,
    GREATER_OR_EQUAL,
    /*function*/
    TO_YEAR,
    /*parameter*/
    STR_PARAM,
    INT_PARAM,
    FLOAT_PARAM
};

struct Value
{
    enum ValueType type_;
    void* data_;
    int child_num_;
    struct Value **child_;
};

struct Value *new_value(enum ValueType type);
struct Value *new_int_value(int val);
struct Value *new_float_value(float val);
struct Value *new_string_value(char *str, int len);
void delete_value(struct Value *val);
void append_child(struct Value *val, struct Value *child);

#endif