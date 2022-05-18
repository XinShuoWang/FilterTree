#include "FilterTree.h"

#include <cassert>

// treat p and q as node, is p contain q?
static bool node_contain(Value *p, Value *q, Value *p_father, Value *q_father)
{
    if (p->type_ != q->type_)
    {
        //printf("node_contain p->type_ != q->type_\n");
        return false;
    }

    switch (p->type_)
    {
    case NONE:
    case AND:
    case OR:
    case LESS:
    case LESS_OR_EQUAL:
    case EQUAL:
    case NOT_EQUAL:
    case GREATER:
    case GREATER_OR_EQUAL:
    case TO_YEAR:
        return true;
    case STR_PARAM:
    {
        if (p->data_size_ != q->data_size_)
            return false;
        return memcmp(p->data_, q->data_, p->data_size_) == 0;
    }
    case INT_PARAM:
    {
        //printf("INT_PARAM\n");
        //printf("p->data: %d, q->data: %d\n", *((int *)p->data_), *((int *)q->data_));
        if (p_father->type_ != q_father->type_)
            return false;
        switch (p_father->type_)
        {
        case LESS:
        case LESS_OR_EQUAL:
            return *((int *)p->data_) <= *((int *)q->data_);
        case EQUAL:
        case NOT_EQUAL:
            return *((int *)p->data_) == *((int *)q->data_);
        case GREATER:
        case GREATER_OR_EQUAL:
            return *((int *)p->data_) >= *((int *)q->data_);
        default:
            exit(1);
        }
    }
    case FLOAT_PARAM:
    {
        if (p_father->type_ != q_father->type_)
            return false;
        switch (p_father->type_)
        {
        case LESS:
        case LESS_OR_EQUAL:
            return *((float *)p->data_) <= *((float *)q->data_);
        case EQUAL:
        case NOT_EQUAL:
            return *((float *)p->data_) == *((float *)q->data_);
        case GREATER:
        case GREATER_OR_EQUAL:
            return *((float *)p->data_) >= *((float *)q->data_);
        default:
            exit(1);
        }
    }
    default:
        exit(1);
    }
}

// p > q (from data structure)
// treat p and q as tree, is p contain q from data structure?
static bool contain(Value *p, Value *q, Value *p_father, Value *q_father)
{
    if (p == nullptr && q == nullptr)
    {
        return true;
    }
    else if (p == nullptr && q != nullptr)
    {
        return false;
    }
    else if (p != nullptr && q == nullptr)
    {
        return true;
    }
    else if (p != nullptr && q != nullptr)
    {
        if (!node_contain(p, q, p_father, q_father))
            return false;
        for (int i = 0; i < q->child_num_; ++i)
        {
            bool exist = false;
            for (int j = 0; j < p->child_num_; ++j)
            {
                if (contain(p->child_[j], q->child_[i], p, q))
                {
                    exist = true;
                    break;
                }
            }
            if (!exist)
                return false;
        }
        return true;
    }
    return false;
}

FilterTree::FilterTree(std::string &str)
{
    str_ = str;
    root_ = parse(const_cast<char *>(str_.c_str()), str_.length());
}

FilterTree::~FilterTree()
{
    delete_value(root_);
}

void FilterTree::Recursive()
{
    dfs(root_, 1);
}

Value *FilterTree::Parse()
{
    return root_;
}

// 返回的结果代表：两棵树所代表的的结果集是否有包含关系
// this的结果集是否包含tree所代表的的结果集
bool FilterTree::Contain(FilterTree &tree)
{
    if (str_.length() == tree.str_.length() && memcmp(str_.c_str(), tree.str_.c_str(), str_.length()) == 0)
        return true;
    Value *x = Parse();
    Value *y = tree.Parse();
    return contain(y, x, nullptr, nullptr);
}
