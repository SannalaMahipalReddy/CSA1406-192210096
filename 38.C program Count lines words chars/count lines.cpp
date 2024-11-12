#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
void analyzeFile(FILE *file, int *characterCount, int *wordCount, int *lineCount) {
    char ch;
    int inWord = 0;
    while ((ch = fgetc(file)) != EOF) {
        (*characterCount)++;
        if (ch == '\n') {
            (*lineCount)++;
        }
        if (isspace(ch)) {
            inWord = 0;
        } else if (!inWord) {
            inWord = 1;
            (*wordCount)++;
        }
    }
    if (ch != '\n' && *characterCount > 0) {
        (*lineCount)++;
    }
}
int main() {
    char filename[100];
    int characters = 0, words = 0, lines = 0;
    printf("Enter the filename to analyze: ");
    scanf("%s", filename);
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Could not open file %s\n", filename);
        return 1;
    }
    analyzeFile(file, &characters, &words, &lines);
    fclose(file);
    printf("File Analysis:\n");
    printf("Characters: %d\n", characters);
    printf("Words: %d\n", words);
    printf("Lines: %d\n", lines);
    return 0;
}
