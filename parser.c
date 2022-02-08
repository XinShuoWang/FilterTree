#include <stdio.h>
#include <stdlib.h>

#include "ast.h"
#include "parser.h"
#include "filter.tab.h"
#include "filter.yy.h"

struct Value *val;

void dfs(struct Value *v, int level)
{
	if (v == NULL)
		return;
	printf("Level is %d.", level);
	switch (v->type_)
	{
	case NONE:
		printf("None \n");
		break;
	case AND:
		printf("AND \n");
		break;
	case OR:
		printf("OR \n");
		break;
	case LESS:
		printf("LESS \n");
		break;
	case LESS_OR_EQUAL:
		printf("LESS_OR_EQUAL \n");
		break;
	case EQUAL:
		printf("EQUAL \n");
		break;
	case NOT_EQUAL:
		printf("NOT_EQUAL \n");
		break;
	case GREATER:
		printf("GREATER \n");
		break;
	case GREATER_OR_EQUAL:
		printf("GREATER_OR_EQUAL \n");
		break;
	case TO_YEAR:
		printf("TO_YEAR \n");
		break;
	case STR_PARAM:
		printf("STR_PARAM %s\n", (char *)v->data_);
		break;
	case INT_PARAM:
		printf("INT_PARAM %d\n", *((int *)v->data_));
		break;
	case FLOAT_PARAM:
		printf("FLOAT_PARAM %f\n", *((float *)v->data_));
		break;
	}
	if (v->child_num_ == 0)
		return;
	for (int i = 0; i < v->child_num_; ++i)
	{
		dfs(v->child_[i], level + 1);
	}
}

struct Value *parse(char *str, int len)
{
	struct yy_buffer_state * buffer = yy_scan_string(str);
	yyparse();
	yy_delete_buffer(buffer);
	return val;
}