#include <stdio.h>
#include <ctype.h>

void process_operators(FILE *input) {
    int ch;

    while ((ch = fgetc(input)) != EOF) {
        if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            // Print recognized operator
            printf("OPERATOR: %c\n", ch);
        }
    }
}

int main() {
    FILE *input = fopen("operatorprint.txt", "r");
    if (!input) {
        perror("Failed to open input file");
        return 1;
    }

    process_operators(input);

    fclose(input);
    return 0;
}

