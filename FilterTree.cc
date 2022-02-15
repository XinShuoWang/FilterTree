#include "FilterTree.h"

FilterTree::FilterTree(std::string &str)
{
    str_ = str;
    root_ = nullptr;
}

void FilterTree::Recursive(TreeNode node)
{
    dfs(node.get(), 1);
}

TreeNode FilterTree::Parse()
{
    if (root_ == nullptr)
    {
        Value *p = parse(const_cast<char *>(str_.c_str()), str_.length());
        root_ = std::shared_ptr<Value>(p, [](Value *v)
                                       { delete_value(v); });
    }
    return root_;
}

bool FilterTree::operator==(FilterTree &tree)
{
    return str_.length() == tree.str_.length() && (memcmp(str_.c_str(), tree.str_.c_str(), str_.length()) == 0);
}

bool FilterTree::operator<(FilterTree &tree)
{
    auto x = this->Parse(), y = tree.Parse();
    
}

bool FilterTree::operator>(FilterTree &tree)
{
    return true;
}

bool FilterTree::operator<=(FilterTree &tree)
{
    return *this == tree || *this < tree;
}

bool FilterTree::operator>=(FilterTree &tree)
{
    return *this == tree || *this > tree;
}