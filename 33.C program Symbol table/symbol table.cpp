
#include <stdio.h>
#include <string.h>
#define MAX 100
struct Symbol { char name[20], type[10]; int size; } symbolTable[MAX];
int count = 0;
void insertSymbol(char name[], char type[], int size) {
    if (count >= MAX) { printf("Table full!\n"); return; }
    for (int i = 0; i < count; i++) if (!strcmp(symbolTable[i].name, name)) {
        printf("Symbol %s exists.\n", name); return;
    }
    strcpy(symbolTable[count].name, name);
    strcpy(symbolTable[count].type, type);
    symbolTable[count++].size = size;
    printf("Inserted %s.\n", name);
}
int searchSymbol(char name[]) {
    for (int i = 0; i < count; i++) if (!strcmp(symbolTable[i].name, name)) return i;
    return -1;
}
void displaySymbolTable() {
    if (count == 0) { printf("Empty table.\n"); return; }
    printf("\nName\tType\tSize\n");
    for (int i = 0; i < count; i++) printf("%s\t%s\t%d\n", symbolTable[i].name, symbolTable[i].type, symbolTable[i].size);
}
int main() {
    int choice, size, index;
    char name[20], type[10];
    while (1) {
        printf("\n1.Insert 2.Search 3.Display 4.Exit\nChoice: ");
        scanf("%d", &choice);
        if (choice == 1) { printf("Name Type Size: "); scanf("%s %s %d", name, type, &size); insertSymbol(name, type, size); }
        else if (choice == 2) { printf("Enter name: "); scanf("%s", name); index = searchSymbol(name); printf(index != -1 ? "Found: %s, %s, %d\n" : "Not found.\n", symbolTable[index].name, symbolTable[index].type, symbolTable[index].size); }
        else if (choice == 3) displaySymbolTable();
        else if (choice == 4) break;
        else printf("Invalid choice.\n");
    }
    return 0;
}

