#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_EXPR_LEN 50
#define MAX_EXPR 100
typedef struct {
    char expression[MAX_EXPR_LEN];
    int tempVar;
} Expression;
Expression exprTable[MAX_EXPR];
int exprCount = 0;
int find_common_subexpression(char *expr) {
    for (int i = 0; i < exprCount; i++) {
        if (strcmp(exprTable[i].expression, expr) == 0) {
            return exprTable[i].tempVar; 
        }
    }
    return -1; 
}
int add_expression(char *expr) {
    strcpy(exprTable[exprCount].expression, expr);
    exprTable[exprCount].tempVar = exprCount + 1; 
    return exprTable[exprCount++].tempVar;
}
void eliminate_common_subexpressions(char expressions[][MAX_EXPR_LEN], int n) {
    printf("Optimized Code:\n");
    for (int i = 0; i < n; i++) {
        char *expr = expressions[i];
        int tempVar = find_common_subexpression(expr);
        
        if (tempVar == -1) {
            tempVar = add_expression(expr);
            printf("t%d = %s\n", tempVar, expr); 
        } else {
            printf("// Reusing common subexpression for %s\n", expr);
            printf("result = t%d\n", tempVar);
        }
    }
}
int main() {
    int n;
    char expressions[MAX_EXPR][MAX_EXPR_LEN];
    printf("Enter number of expressions: ");
    scanf("%d", &n);
    getchar();
    for (int i = 0; i < n; i++) {
        printf("Enter expression %d: ", i + 1);
        fgets(expressions[i], MAX_EXPR_LEN, stdin);
        expressions[i][strcspn(expressions[i], "\n")] = 0;
    }
    printf("\nOriginal Code:\n");
    for (int i = 0; i < n; i++) {
        printf("result = %s\n", expressions[i]);
    }

    printf("\n");
    eliminate_common_subexpressions(expressions, n);

    return 0;
}
