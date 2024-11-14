#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_IDENTIFIER_LENGTH 50

const char *keywords[] = {
    "int", "float", "char", "if", "else", "while", "for", "return",
    "void", "break", "continue", "switch", "case"
};
#define NUM_KEYWORDS (sizeof(keywords) / sizeof(keywords[0]))

// Function to check if a word is a keyword
int is_keyword(const char *word) {
    for (int i = 0; i < NUM_KEYWORDS; i++) {
        if (strcmp(word, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

// Function to classify and print each token
void classify_token(const char *token) {
    if (is_keyword(token)) {
        printf("KEYWORD: %s\n", token);
    } else if (isalpha(token[0]) || token[0] == '_') {
        if (strlen(token) > MAX_IDENTIFIER_LENGTH) {
            printf("IDENTIFIER (too long): %s\n", token);
        } else {
            printf("IDENTIFIER: %s\n", token);
        }
    } else if (isdigit(token[0])) {
        printf("CONSTANT: %s\n", token);
    } else if (strchr("+-*/%=<>!&|^", token[0]) && token[1] == '\0') {
        printf("OPERATOR: %s\n", token);
    } else if (strchr(";,(){}", token[0]) && token[1] == '\0') {
        printf("PUNCTUATION: %s\n", token);
    } else {
        printf("UNKNOWN: %s\n", token);
    }
}

// Function to process each character and extract tokens
void process_input(FILE *input) {
    char token[100];
    int i = 0;
    char ch;

    while ((ch = fgetc(input)) != EOF) {
        if (isspace(ch)) {
            if (i > 0) {  // End of a token
                token[i] = '\0';
                classify_token(token);
                i = 0;
            }
        } else if (ch == '/' && (ch = fgetc(input)) == '/') {  // Single-line comment
            while ((ch = fgetc(input)) != '\n' && ch != EOF);
        } else if (ch == '/' && (ch = fgetc(input)) == '*') {  // Multi-line comment
            while ((ch = fgetc(input)) != EOF) {
                if (ch == '*' && (ch = fgetc(input)) == '/') break;
            }
        } else if (strchr(";,(){}", ch) || strchr("+-*/%=<>!&|^", ch)) {
            if (i > 0) {  // Process previous token
                token[i] = '\0';
                classify_token(token);
                i = 0;
            }
            token[0] = ch;
            token[1] = '\0';
            classify_token(token);  // Process single char token
        } else {
            token[i++] = ch;
        }
    }
    if (i > 0) {  // Process the last token if any
        token[i] = '\0';
        classify_token(token);
    }
}

int main() {
    FILE *input = fopen("recogconstidoperator.txt", "r");
    if (!input) {
        perror("Failed to open input file");
        return 1;
    }

    process_input(input);

    fclose(input);
    return 0;
}

