#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_EXPR_LEN 100
#define MAX_TOKENS 50
#define MAX_CODE 200
typedef enum { OPERAND, OPERATOR } TokenType;

typedef struct {
    TokenType type;
    char value;
} Token;

typedef struct {
    char instr[10];
    char arg1[10];
    char arg2[10];
} CodeLine;

CodeLine code[MAX_CODE];
int codeCount = 0;
int tempVarCount = 1;
void add_code(const char *instr, const char *arg1, const char *arg2) {
    strcpy(code[codeCount].instr, instr);
    strcpy(code[codeCount].arg1, arg1);
    if (arg2) {
        strcpy(code[codeCount].arg2, arg2);
    } else {
        strcpy(code[codeCount].arg2, "");
    }
    codeCount++;
}
void generate_temp_var(char *tempVar) {
    sprintf(tempVar, "T%d", tempVarCount++);
}
int tokenize(const char *expr, Token tokens[]) {
    int index = 0;
    for (int i = 0; expr[i] != '\0'; i++) {
        if (isdigit(expr[i])) {
            tokens[index].type = OPERAND;
            tokens[index++].value = expr[i];
        } else if (strchr("+-*/", expr[i])) {
            tokens[index].type = OPERATOR;
            tokens[index++].value = expr[i];
        }
    }
    return index;
}
void generate_code(Token tokens[], int tokenCount) {
    char tempVar1[10], tempVar2[10], result[10];
    
    for (int i = 1; i < tokenCount; i += 2) {
        generate_temp_var(result);
        char op = tokens[i].value;

        if (i == 1) { 
            sprintf(tempVar1, "%c", tokens[i - 1].value);
            sprintf(tempVar2, "%c", tokens[i + 1].value);
        } else { 
            strcpy(tempVar1, result);
            sprintf(tempVar2, "%c", tokens[i + 1].value);
        }
        switch (op) {
            case '+': add_code("ADD", tempVar1, tempVar2); break;
            case '-': add_code("SUB", tempVar1, tempVar2); break;
            case '*': add_code("MUL", tempVar1, tempVar2); break;
            case '/': add_code("DIV", tempVar1, tempVar2); break;
        }
        add_code("STORE", result, NULL);
    }
}
void print_code() {
    printf("Generated Assembly-like Code:\n");
    for (int i = 0; i < codeCount; i++) {
        if (strcmp(code[i].arg2, "") != 0)
            printf("%s %s, %s\n", code[i].instr, code[i].arg1, code[i].arg2);
        else
            printf("%s %s\n", code[i].instr, code[i].arg1);
    }
}

int main() {
    char expression[MAX_EXPR_LEN];
    Token tokens[MAX_TOKENS];
    
    printf("Enter an arithmetic expression: ");
    fgets(expression, MAX_EXPR_LEN, stdin);
    expression[strcspn(expression, "\n")] = '\0';

    int tokenCount = tokenize(expression, tokens);
    generate_code(tokens, tokenCount);
    print_code();

    return 0;
}
