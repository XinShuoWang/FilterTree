#ifndef PARSER_H
#define PARSER_H

#include "ast.h"

void dfs(struct Value *v, int level);
struct Value *parse(char *str, int len);

#endif