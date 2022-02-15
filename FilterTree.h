#ifndef FILTER_TREE_H
#define FILTER_TREE_H

#include "parser.h"
#include "ast.h"

#include <string>
#include <memory>

typedef std::shared_ptr<Value> TreeNode;

class FilterTree
{
public:
    FilterTree(std::string &str);
    void Recursive(TreeNode node);
    TreeNode Parse();
    bool operator==(FilterTree &tree);
    bool operator<(FilterTree &tree);
    bool operator>(FilterTree &tree);
    bool operator<=(FilterTree &tree);
    bool operator>=(FilterTree &tree);

private:
    std::string str_;
    TreeNode root_;
};

#endif