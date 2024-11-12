#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char input[100];
int tempVarCount = 1;

void newTemp(char *temp) {
    sprintf(temp, "t%d", tempVarCount++);
}

int generateTAC(char *expr, int start, int end, char *result) {
    int parenDepth = 0;
    int opPos = -1;

    for (int i = start; i <= end; i++) {
        if (expr[i] == '(') parenDepth++;
        else if (expr[i] == ')') parenDepth--;
        
        if (parenDepth == 0) {
            if (expr[i] == '+' || expr[i] == '-') opPos = i;
            else if ((expr[i] == '*' || expr[i] == '/') && opPos == -1) opPos = i;
        }
    }

    if (opPos == -1) {
        if (expr[start] == '(' && expr[end] == ')') {
            return generateTAC(expr, start + 1, end - 1, result);
        } else {
            strncpy(result, expr + start, end - start + 1);
            result[end - start + 1] = '\0';
            return 0;
        }
    }

    char left[20], right[20], temp[20];
    generateTAC(expr, start, opPos - 1, left);
    generateTAC(expr, opPos + 1, end, right);

    newTemp(temp);
    printf("%s = %s %c %s\n", temp, left, expr[opPos], right);

    strcpy(result, temp);
    return 0;
}

int main() {
    printf("Enter an arithmetic expression: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';

    char result[20];
    
    if (strchr(input, '=')) {
        char left[20];
        int i = 0;
        while (input[i] != '=' && input[i] != '\0') {
            left[i] = input[i];
            i++;
        }
        left[i] = '\0';
        
        generateTAC(input, i + 1, strlen(input) - 1, result);

        printf("%s = %s\n", left, result);
    } else {
        printf("No assignment found in the expression.\n");
    }

    return 0;
}

