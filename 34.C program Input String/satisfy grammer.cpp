#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

const char *input; 
int pos = 0;        
int E();  
int T();  
int F();  
void error(); 
int match(char expected) {
    if (input[pos] == expected) {
        pos++;
        return 1;
    }
    return 0;
}
int num() {
    int start = pos;
    while (isdigit(input[pos])) pos++;  
    return pos > start;  
}
int F() {
    if (match('(')) {
        if (!E()) error();
        if (!match(')')) error();
        return 1;
    }
    if (num()) return 1;
    error();
    return 0;
}
int T() {
    if (!F()) return 0;
    while (input[pos] == '*' || input[pos] == '/') {
        pos++;
        if (!F()) error();
    }
    return 1;
}

int E() {
    if (!T()) return 0;
    while (input[pos] == '+' || input[pos] == '-') {
        pos++;
        if (!T()) error();
    }
    return 1;
}

void error() {
    printf("Syntax error at position %d\n", pos);
    exit(1);
}

int main() {
    char expr[100];
    printf("Enter an expression: ");
    fgets(expr, sizeof(expr), stdin);
    expr[strcspn(expr, "\n")] = '\0';  
    
    input = expr;  
    pos = 0;     
    if (E() && input[pos] == '\0') {
        printf("The expression is valid according to the grammar.\n");
    } else {
        printf("The expression is invalid according to the grammar.\n");
    }

    return 0;
}

