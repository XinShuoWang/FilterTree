#include <stdio.h>
#include <stdlib.h>

#include "ast.h"
#include "filter.tab.h"

typedef struct yy_buffer_state *YY_BUFFER_STATE;
extern int yyparse();
extern YY_BUFFER_STATE yy_scan_string(char *str);
extern void yy_delete_buffer(YY_BUFFER_STATE buffer);

struct Value *val;

int main()
{
	char string[] = "and(equals(toYear(LO_ORDERDATE), 1993), and(greaterOrEquals(LO_DISCOUNT, 1), "
					"lessOrEquals(LO_DISCOUNT, 3.1), less(LO_QUANTITY, 25)))";
	YY_BUFFER_STATE buffer = yy_scan_string(string);
	yyparse();
	yy_delete_buffer(buffer);
	printf("Value type is %d, op_size is %d, op is %s \n", val->type_, val->op_size_, (char*)val->op_);
	return 0;
}