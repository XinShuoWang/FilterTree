#include "FilterTree.h"

#include <iostream>
#include <string>
#include <cassert>

int main(int argc, char **argv)
{
    std::string str = "and(equals(length(sex), -3))";
    FilterTree tree(str);
    return 0;
}