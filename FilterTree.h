#ifndef FILTER_TREE_H
#define FILTER_TREE_H

#include "parser.h"
#include "ast.h"
#include "debug.h"

#include <string>
#include <memory>

class FilterTree
{
public:
    FilterTree(std::string &str);
    ~FilterTree();
    void Recursive();
    Value* Parse();
    bool Contain(FilterTree& tree);

private:
    std::string str_;
    Value* root_;
};

#endif