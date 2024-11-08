1)#include <stdio.h>


int is_prime(int n) {
    if (n <= 1) return 0;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return 0;
    }
    return 1;
}


void find_primes(int num, int primes[], int *prime_count) {
    *prime_count = 0;
    for (int i = 2; i <= num; i++) {
        if (is_prime(i)) {
            primes[(*prime_count)++] = i;
        }
    }
}


void find_prime_pairs(int num, int primes[], int prime_count) {
    int count = 0;
    for (int i = 0; i < prime_count; i++) {
        for (int j = i; j < prime_count; j++) {
            if (primes[i] + primes[j] == num) {
                printf("%d = %d + %d\n", num, primes[i], primes[j]);
                count++;
            }
        }
    }
    if (count > 0) {
        printf("NoofWays = %d\n", count);
    } else {
        printf("NoofWays = -1\n");
    }
}

int main() {
    int num;
    printf("Enter a positive integer: ");
    scanf("%d", &num);

    int primes[num]; 
    int prime_count; 

    find_primes(num, primes, &prime_count);
    find_prime_pairs(num, primes, prime_count);

    return 0;
}

