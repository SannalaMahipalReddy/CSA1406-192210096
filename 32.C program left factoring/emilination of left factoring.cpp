#include <stdio.h>
#include <string.h>
int main() {
    char nonTerminal;
    char commonPrefix[10], option1[10], option2[10];
    printf("Enter the non-terminal: ");
    scanf(" %c", &nonTerminal);
    printf("Enter the common prefix: ");
    scanf("%s", commonPrefix);
    printf("Enter the first option after the prefix: ");
    scanf("%s", option1);
    printf("Enter the second option after the prefix: ");
    scanf("%s", option2);
    printf("\nOriginal production: %c -> %s%s | %s%s\n", nonTerminal, commonPrefix, option1, commonPrefix, option2);
    printf("After eliminating left factoring:\n");
    printf("%c -> %s%c'\n", nonTerminal, commonPrefix, nonTerminal);
    printf("%c' -> %s | %s\n", nonTerminal, option1, option2);
    return 0;
}
