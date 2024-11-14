#include <stdio.h>

void process_comments(FILE *input) {
    int ch, next_ch;

    while ((ch = fgetc(input)) != EOF) {
        if (ch == '/') {
            next_ch = fgetc(input);
            if (next_ch == '/') {
                // Detected a single-line comment
                printf("SINGLE-LINE COMMENT: //");
                while ((ch = fgetc(input)) != '\n' && ch != EOF) {
                    putchar(ch);
                }
                putchar('\n');  // End of single-line comment
            } else if (next_ch == '*') {
                // Detected a multi-line comment
                printf("MULTI-LINE COMMENT: /*");
                while ((ch = fgetc(input)) != EOF) {
                    if (ch == '*' && (next_ch = fgetc(input)) == '/') {
                        // Closing sequence of multi-line comment
                        printf("*/\n");
                        break;
                    } else {
                        putchar(ch); // Print character within the multi-line comment
                        if (ch == '*') {
                            ungetc(next_ch, input);  // Restore if not the end of comment
                        }
                    }
                }
            } else {
                ungetc(next_ch, input);  // Not a comment, push back
            }
        }
    }
}

int main() {
    FILE *input = fopen("commentlineprint.txt", "r");
    if (!input) {
        perror("Failed to open input file");
        return 1;
    }

    process_comments(input);

    fclose(input);
    return 0;
}

