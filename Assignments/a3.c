#include <stdio.h>

// Function to find the nth number made of prime digits 2, 3, 5, and 7
int findNthPrimeDigitNumber(int n) {
    int primes[] = {2, 3, 5, 7};
    int result = 0;
    int base = 1;

    while (n > 0) {
        result += primes[(n - 1) % 4] * base;
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
        int nthNumber = findNthPrimeDigitNumber(N);
        printf("The %dth number is: %d\n", N, nthNumber);
    }

    return 0;
}