#include <stdio.h>
#include <string.h>
int main() {
    char nonTerminal;
    char alpha[10], beta[10];
    printf("Enter the non-terminal");
    scanf(" %c", &nonTerminal);
    printf("Enter the recursive part (alpha):");
    scanf("%s", alpha);
    printf("Enter the non-recursive part (beta):");
    scanf("%s", beta);
    printf("\nOriginal Production: %c -> %c%c | %s\n", nonTerminal, nonTerminal, alpha[0], beta);
    printf("After removing left recursion:\n");
    printf("%c -> %s%c'\n", nonTerminal, beta, nonTerminal);
    printf("%c' -> %s%c' | e\n", nonTerminal, alpha, nonTerminal);
    return 0;
}
