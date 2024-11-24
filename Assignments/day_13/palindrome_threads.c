/* DESCRIPTION : Program to count palindromes and non-palindromes using threads
   Date : 2024-11-23
   Name : pothineedi saraswathi
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

// Global variables
int is_palindrome = 0;
int not_palindrome = 0;
pthread_mutex_t mutex;

// Thread function to check for palindrome
void *check_palindrome(void *arg) {
    char *input = (char *)arg;
    int len = strlen(input);
    int palindrome = 1;

    for (int i = 0; i < len / 2; i++) {
        if (input[i] != input[len - i - 1]) {
            palindrome = 0;
            break;
        }
    }

    char *message = (char *)malloc(100);  // Allocate memory for the return message
    if (palindrome) {
        pthread_mutex_lock(&mutex);
        is_palindrome++;
        pthread_mutex_unlock(&mutex);
        sprintf(message, "%s is a palindrome", input);
    } else {
        pthread_mutex_lock(&mutex);
        not_palindrome++;
        pthread_mutex_unlock(&mutex);
        sprintf(message, "%s is not a palindrome", input);
    }
    return message;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <string1> <string2> ... <stringN>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int n = argc - 1;
    pthread_t threads[n];
    pthread_mutex_init(&mutex, NULL);

    // Create threads
    for (int i = 0; i < n; i++) {
        if (pthread_create(&threads[i], NULL, check_palindrome, argv[i + 1]) != 0) {
            perror("Failed to create thread");
            return EXIT_FAILURE;
        }
    }

    // Join threads and display their messages
    for (int i = 0; i < n; i++) {
        char *result;
        if (pthread_join(threads[i], (void **)&result) != 0) {
            perror("Failed to join thread");
            return EXIT_FAILURE;
        }
        printf("%s\n", result);
        free(result);  // Free memory allocated in thread
    }

    printf("\nTotal palindromes: %d\n", is_palindrome);
    printf("Total non-palindromes: %d\n", not_palindrome);

    pthread_mutex_destroy(&mutex);
    return EXIT_SUCCESS;
}
