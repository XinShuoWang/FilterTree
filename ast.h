#ifndef AST_H
#define AST_H

enum ValueType
{
    OP,
    STR_PARAM,
    INT_PARAM,
    FLOAT_PARAM
};

struct Value
{
    enum ValueType type_;
    int op_size_;
    void *op_;
    int child_num_;
    struct Value* child_;
};

#endif