#include "ast.h"

void *alloc(int size)
{
    void *ans = malloc(size);
    memset(ans, 0, size);
    return ans;
}

struct Value *new_value(enum ValueType type)
{
    struct Value *p = (struct Value *)alloc(sizeof(struct Value));
    // type
    p->type_ = type;
    return p;
}

struct Value *new_int_value(int val)
{
    struct Value *p = (struct Value *)alloc(sizeof(struct Value));
    // type
    p->type_ = INT_PARAM;
    // parameter
    p->data_ = alloc(sizeof(int));
    memcpy(p->data_, &val, sizeof(int));
    return p;
}

struct Value *new_float_value(float val)
{
    struct Value *p = (struct Value *)alloc(sizeof(struct Value));
    // type
    p->type_ = FLOAT_PARAM;
    // parameter
    p->data_ = alloc(sizeof(float));
    memcpy(p->data_, &val, sizeof(float));
    return p;
}

struct Value *new_string_value(char *str, int len)
{
    struct Value *p = (struct Value *)alloc(sizeof(struct Value));
    // type
    p->type_ = STR_PARAM;
    // parameter
    p->data_ = alloc(len);
    memcpy(p->data_, str, len);
    return p;
}

void delete_value(struct Value *val)
{
    if (val->type_ == INT_PARAM || val->type_ == FLOAT_PARAM || val->type_ == STR_PARAM)
        free(val->data_);
    free(val);
}

void append_child(struct Value *val, struct Value *child)
{
    if (val->child_num_ == 0)
    {
        struct Value **p = (struct Value **)alloc(sizeof(struct Value *));
        p[val->child_num_] = child;
        val->child_ = p;
        val->child_num_ = 1;
    }
    else
    {
        struct Value **p = (struct Value **)alloc((val->child_num_ + 1) * sizeof(struct Value *));
        memcpy(p, val->child_, sizeof(struct Value *) * val->child_num_);
        p[val->child_num_] = child;
        free(val->child_);
        val->child_ = p;
        val->child_num_++;
    }
}