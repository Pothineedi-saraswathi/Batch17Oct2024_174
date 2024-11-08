5)
#include <stdio.h>

void printAlphabetTriangle(int n) {
    for (int i = 0; i < n; i++) {
        // Print leading spaces
        for (int j = 0; j < n - i - 1; j++) {
            printf(" ");
        }
        // Print increasing part of the pattern
        for (int j = 0; j <= i; j++) {
            printf("%c", 'A' + j);
        }
        // Print decreasing part of the pattern
        for (int j = i - 1; j >= 0; j--) {
            printf("%c", 'A' + j);
        }
        // Move to the next line
        printf("\n");
    }
}

int main() {
    int n;
    printf("Enter the number of rows: ");
    scanf("%d", &n);
    printAlphabetTriangle(n);
    return 0;
}


