#include "FilterTree.h"

#include <iostream>
#include <string>

int main()
{
    std::string str = "and(equals(toYear(LO_ORDERDATE), 1993), and(greaterOrEquals(LO_DISCOUNT, 1), "
                      "lessOrEquals(LO_DISCOUNT, 3.1), less(LO_QUANTITY, 25)))";
    {
        FilterTree tree(str);
        TreeNode ans = tree.Parse();
        tree.Recursive(ans);
    }
    {
        FilterTree tree1(str), tree2(str);
        if (tree1 == tree2)
            std::cout << "tree1 == tree2" << std::endl;
        if (tree1 < tree2)
            std::cout << "tree1 < tree2" << std::endl;
        if (tree1 > tree2)
            std::cout << "tree1 > tree2" << std::endl;
    }
    return 0;
}