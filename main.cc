#include "parser.h"
#include "ast.h"

#include <string>

typedef Value* TreeNode;

class FilterTree 
{
public:
    FilterTree(std::string& str)
    {
        str_ = str;
    }

    static void Recursive(TreeNode node)
    {
        dfs(node, 1);
    }

    TreeNode Parse()
    {
        return parse(const_cast<char*>(str_.c_str()), str_.length());
    }

private:
    std::string str_;
};


int main()
{
    std::string str = "and(equals(toYear(LO_ORDERDATE), 1993), and(greaterOrEquals(LO_DISCOUNT, 1), "
                      "lessOrEquals(LO_DISCOUNT, 3.1), less(LO_QUANTITY, 25)))";
    FilterTree tree(str);
    TreeNode ans = tree.Parse();
    FilterTree::Recursive(ans);
    return 0;
}