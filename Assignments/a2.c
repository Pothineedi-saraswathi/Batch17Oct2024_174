#include <stdio.h>
#include <math.h>

// Function to find the nth number made of digits 1, 4, 6, and 9
int findNthNumber(int n) {
    int digits[] = {1, 4, 6, 9};
    int result = 0;
    int base = 1;

    while (n > 0) {
        result += digits[(n - 1) % 4] * base;
        n = (n - 1) / 4;
        base *= 10;
    }

    return result;
}

int main() {
    int T, N;
    printf("Enter the number of test cases: ");
    scanf("%d", &T);

    while (T--) {
        printf("Enter the value of N: ");
        scanf("%d", &N);
        int nthNumber = findNthNumber(N);
        printf("The %dth number is: %d\n", N, nthNumber);
    }

    return 0;
}