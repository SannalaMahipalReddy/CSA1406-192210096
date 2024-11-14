#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_IDENTIFIER_LENGTH 50

int is_valid_identifier(const char *str) {
    // Check if the first character is a valid starting character (alphabet or '_')
    if (!(isalpha(str[0]) || str[0] == '_')) {
        return 0;  // Invalid starting character
    }

    // Check the rest of the characters (must be alphanumeric or '_')
    for (int i = 1; str[i] != '\0'; i++) {
        if (!(isalnum(str[i]) || str[i] == '_')) {
            return 0;  // Invalid character found
        }
    }

    return 1;  // Valid identifier
}

int main() {
    FILE *input = fopen("identifiervalidation.txt", "r");
    if (!input) {
        perror("Failed to open input file");
        return 1;
    }

    char word[MAX_IDENTIFIER_LENGTH + 1];  // Buffer to store words from the input
    int ch;
    int index = 0;

    while ((ch = fgetc(input)) != EOF) {
        if (isalnum(ch) || ch == '_') {
            // Add character to the word
            if (index < MAX_IDENTIFIER_LENGTH) {
                word[index++] = ch;
            } else {
                // Skip characters if the identifier is too long
                while ((ch = fgetc(input)) != EOF && (isalnum(ch) || ch == '_'));
                index = 0;  // Reset for the next word
                printf("Invalid identifier (too long)\n");
                continue;
            }
        } else {
            if (index > 0) {
                word[index] = '\0';  // Null-terminate the word
                // Check if the word is a valid identifier
                if (is_valid_identifier(word)) {
                    printf("Valid identifier: %s\n", word);
                } else {
                    printf("Invalid identifier: %s\n", word);
                }
                index = 0;  // Reset for the next word
            }
        }
    }

    // In case the last word ends at EOF without a non-alphanumeric character
    if (index > 0) {
        word[index] = '\0';
        if (is_valid_identifier(word)) {
            printf("Valid identifier: %s\n", word);
        } else {
            printf("Invalid identifier: %s\n", word);
        }
    }

    fclose(input);
    return 0;
}

