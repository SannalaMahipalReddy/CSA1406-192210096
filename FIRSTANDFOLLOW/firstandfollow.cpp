#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX 10

char productions[MAX][MAX];
char first[MAX][MAX];
char follow[MAX][MAX];
char non_terminals[MAX];
int num_productions;

void findFirst(char symbol, char result[]) {
    if (!isupper(symbol)) {
        strncat(result, &symbol, 1); // If terminal, add to result
        return;
    }

    for (int i = 0; i < num_productions; i++) {
        if (productions[i][0] == symbol) {
            // Look at the right-hand side of the production
            int j = 2;
            while (productions[i][j] != '\0') {
                if (productions[i][j] == symbol) break;
                
                findFirst(productions[i][j], result);
                
                if (!strchr(first[productions[i][j] - 'A'], 'e')) break;
                j++;
            }
        }
    }
}

void addFollow(char symbol, char result[]) {
    if (symbol == productions[0][0]) {
        strcat(result, "$"); // Add '$' for the start symbol
    }
    
    for (int i = 0; i < num_productions; i++) {
        for (int j = 2; productions[i][j] != '\0'; j++) {
            if (productions[i][j] == symbol) {
                if (productions[i][j + 1] != '\0') {
                    char firstResult[MAX] = "";
                    findFirst(productions[i][j + 1], firstResult);
                    strcat(result, firstResult);
                    if (strchr(firstResult, 'e')) {
                        addFollow(productions[i][0], result);
                    }
                } else if (productions[i][0] != symbol) {
                    addFollow(productions[i][0], result);
                }
            }
        }
    }
}

void removeDuplicates(char *str) {
    int index = 0;
    for (int i = 0; i < strlen(str); i++) {
        if (!strchr(str + i + 1, str[i])) {
            str[index++] = str[i];
        }
    }
    str[index] = '\0';
}

int main() {
    printf("Enter the number of productions: ");
    scanf("%d", &num_productions);

    printf("Enter the productions (e.g., S->AB):\n");
    for (int i = 0; i < num_productions; i++) {
        scanf("%s", productions[i]);
        non_terminals[i] = productions[i][0];
    }

    for (int i = 0; i < num_productions; i++) {
        char result[MAX] = "";
        findFirst(productions[i][0], result);
        strcpy(first[productions[i][0] - 'A'], result);
    }

    for (int i = 0; i < num_productions; i++) {
        char result[MAX] = "";
        addFollow(productions[i][0], result);
        removeDuplicates(result);
        strcpy(follow[productions[i][0] - 'A'], result);
    }

    printf("\nFIRST and FOLLOW Sets:\n");
    for (int i = 0; i < num_productions; i++) {
        printf("FIRST(%c) = { %s }\n", non_terminals[i], first[non_terminals[i] - 'A']);
        printf("FOLLOW(%c) = { %s }\n", non_terminals[i], follow[non_terminals[i] - 'A']);
    }

    return 0;
}
