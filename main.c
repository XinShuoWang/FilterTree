#include <stdio.h>
#include <stdlib.h>

#include "ast.h"
#include "filter.tab.h"

typedef struct yy_buffer_state *YY_BUFFER_STATE;
extern int yyparse();
extern YY_BUFFER_STATE yy_scan_string(char *str);
extern void yy_delete_buffer(YY_BUFFER_STATE buffer);

struct Value *val;

void dfs(struct Value *v)
{
	//printf("v is %p\n", (void*)v);
	if(v == NULL) return;
	switch (v->type_)
	{
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
	if(v->child_num_ == 0) return;
	for(int i = 0; i < v->child_num_; ++i)
	{
		dfs(v->child_[i]);
	}
}

int main()
{
	char string[] = "and(equals(toYear(LO_ORDERDATE), 1993), and(greaterOrEquals(LO_DISCOUNT, 1), "
					"lessOrEquals(LO_DISCOUNT, 3.1), less(LO_QUANTITY, 25)))";
	YY_BUFFER_STATE buffer = yy_scan_string(string);
	yyparse();
	yy_delete_buffer(buffer);
	printf("-----------------------\n");
	printf("%s\n", string);
	dfs(val);
	return 0;
}