#include "FilterTree.h"

#include <iostream>
#include <string>
#include <cassert>

int main(int argc, char **argv)
{
    {
        std::cout << "TEST 1" << std::endl;
        std::string str = "and(equals(toYear(LO_ORDERDATE), 1993), and(greaterOrEquals(LO_DISCOUNT, 1), "
                          "lessOrEquals(LO_DISCOUNT, 3.1), less(LO_QUANTITY, 25)))";
        FilterTree tree(str);
        Value *ans = tree.Parse();
        tree.Recursive();
    }
    {
        std::cout << "TEST 2" << std::endl;
        std::string str1 = "and(greaterOrEquals(LO_DISCOUNT, 1), equals(toYear(LO_ORDERDATE), 1993))";
        std::string str2 = "and(equals(toYear(LO_ORDERDATE), 1993))";
        FilterTree tree1(str1), tree2(str2);
        if (tree1.Contain(tree2))
            printf("tree1 contain tree2\n");
        if (tree2.Contain(tree1))
            printf("tree2 contain tree1\n");
        assert(tree2.Contain(tree1));
    }
    {
        std::cout << "TEST 3" << std::endl;
        std::string str1 = "and(less(toYear(LO_ORDERDATE), 1993))";
        std::string str2 = "and(less(toYear(LO_ORDERDATE), 1992))";
        FilterTree tree1(str1), tree2(str2);
        if (tree1.Contain(tree2))
            printf("tree1 contain tree2\n");
        if (tree2.Contain(tree1))
            printf("tree2 contain tree1\n");
        assert(tree1.Contain(tree2));
    }
    {
        std::cout << "TEST 4" << std::endl;
        std::string str1 = "and(less(toYear(LO_ORDERDATE), 1992))";
        std::string str2 = "and(less(toYear(LO_ORDERDATE), 1993))";
        FilterTree tree1(str1), tree2(str2);
        if (tree1.Contain(tree2))
            printf("tree1 contain tree2\n");
        if (tree2.Contain(tree1))
            printf("tree2 contain tree1\n");
        assert(tree2.Contain(tree1));
    }
    {
        std::cout << "TEST 5" << std::endl;
        std::string str1 = "and(less(LO_ORDERDATE, 1993), greater(LO_ORDERDATE, 1993))";
        std::string str2 = "and(less(LO_ORDERDATE, 1992), greater(LO_ORDERDATE, 1994))";
        FilterTree tree1(str1), tree2(str2);
        if (tree1.Contain(tree2))
            printf("tree1 contain tree2\n");
        if (tree2.Contain(tree1))
            printf("tree2 contain tree1\n");
        assert(tree1.Contain(tree2));
    }
    {
        std::cout << "TEST 6" << std::endl;
        std::string str1 = "and(less(LO_ORDERDATE, 1992), greater(LO_ORDERDATE, 1994))";
        std::string str2 = "and(less(LO_ORDERDATE, 1993), greater(LO_ORDERDATE, 1993))";
        FilterTree tree1(str1), tree2(str2);
        if (tree1.Contain(tree2))
            printf("tree1 contain tree2\n");
        if (tree2.Contain(tree1))
            printf("tree2 contain tree1\n");
        assert(tree2.Contain(tree1));
    }
    {
        std::cout << "TEST 7" << std::endl;
        std::string str1 = "and(equals(LO_ORDERDATE, 1993), greaterOrEquals(LO_DISCOUNT, 1), "
                           "lessOrEquals(LO_DISCOUNT, 3))";
        std::string str2 = "and(equals(LO_ORDERDATE, 1993), greaterOrEquals(LO_DISCOUNT, 1), "
                           "lessOrEquals(LO_DISCOUNT, 3), less(LO_QUANTITY, 24))";
        FilterTree tree1(str1), tree2(str2);
        if (tree1.Contain(tree2))
            printf("tree1 contain tree2\n");
        if (tree2.Contain(tree1))
            printf("tree2 contain tree1\n");
        assert(tree1.Contain(tree2));
    }
    {
        std::cout << "TEST 8" << std::endl;
        std::string str1 = "and(equals(toYear(LO_ORDERDATE), 1993), and(greaterOrEquals(LO_DISCOUNT, 1), "
                           "lessOrEquals(LO_DISCOUNT, 3.1), less(LO_QUANTITY, 29)))";
        std::string str2 = "and(equals(toYear(LO_ORDERDATE), 1993), and(greaterOrEquals(LO_DISCOUNT, 1), "
                           "lessOrEquals(LO_DISCOUNT, 3.1), less(LO_QUANTITY, 27)))";
        FilterTree tree1(str1), tree2(str2);
        if (tree1.Contain(tree2))
            printf("tree1 contain tree2\n");
        if (tree2.Contain(tree1))
            printf("tree2 contain tree1\n");
        assert(tree1.Contain(tree2));
    }
    {
        std::cout << "TEST 9" << std::endl;
        std::string str1 = "and(equals(toYear(LO_ORDERDATE), 1993), and(greaterOrEquals(LO_DISCOUNT, 1), "
                           "lessOrEquals(LO_DISCOUNT, 3.1), less(LO_QUANTITY, 25)))";
        std::string str2 = "and(equals(toYear(LO_ORDERDATE), 1993), and(greaterOrEquals(LO_DISCOUNT, 1), "
                           "lessOrEquals(LO_DISCOUNT, 3.1), less(LO_QUANTITY, 27)))";
        FilterTree tree1(str1), tree2(str2);
        if (tree1.Contain(tree2))
            printf("tree1 contain tree2\n");
        if (tree2.Contain(tree1))
            printf("tree2 contain tree1\n");
        assert(tree2.Contain(tree1));
    }

    return 0;
}