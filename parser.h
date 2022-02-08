#ifndef PARSER_H
#define PARSER_H

#include "ast.h"

extern "C" void dfs(struct Value *v, int level);
extern "C" struct Value *parse(char *str, int len);

#endif