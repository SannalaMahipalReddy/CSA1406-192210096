
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define MAX_EXPR_LEN 100

int evaluate_expression(const char *expr, int *index);
int parse_number(const char *expr, int *index);
int parse_term(const char *expr, int *index);
int parse_factor(const char *expr, int *index);
int evaluate_expression(const char *expr, int *index) {
    int result = parse_term(expr, index);
    
    while (expr[*index] != '\0') {
        char op = expr[*index];
        
        if (op == '+' || op == '-') {
            (*index)++;
            int next_term = parse_term(expr, index);
            if (op == '+') {
                result += next_term;
            } else {
                result -= next_term;
            }
        } else {
            break;
        }
    }
    
    return result;
}
int parse_term(const char *expr, int *index) {
    int result = parse_factor(expr, index);
    
    while (expr[*index] != '\0') {
        char op = expr[*index];
        
        if (op == '*' || op == '/') {
            (*index)++;
            int next_factor = parse_factor(expr, index);
            if (op == '*') {
                result *= next_factor;
            } else if (op == '/') {
                result /= next_factor;
            }
        } else {
            break;
        }
    }
    
    return result;
}
int parse_factor(const char *expr, int *index) {
    int result;
    
    if (expr[*index] == '(') {
        (*index)++; 
        result = evaluate_expression(expr, index);
        (*index)++; 
    } else {
        result = parse_number(expr, index);
    }
    if (expr[*index] == '^') {
        (*index)++;
        int exponent = parse_factor(expr, index);
        result = (int)pow(result, exponent);
    }
    
    return result;
}
int parse_number(const char *expr, int *index) {
    int result = 0;
    
    while (isdigit(expr[*index])) {
        result = result * 10 + (expr[*index] - '0');
        (*index)++;
    }
    
    return result;
}

int main() {
    char expression[MAX_EXPR_LEN];
    int index = 0;
    
    printf("Enter a mathematical expression: ");
    fgets(expression, MAX_EXPR_LEN, stdin);
    
    int result = evaluate_expression(expression, &index);
    printf("Result of the expression: %d\n", result);
    
    return 0;
}

