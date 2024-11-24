/* DESCRIPTION : program to validate email IDs
   Date : 2024-11-23
   Name : pothineedi saraswathi
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <ctype.h>

#define MAX_EMAILS 100
#define MAX_LENGTH 256

int validmail_count = 0;
pthread_mutex_t lock;

typedef struct {
    char email[MAX_LENGTH];
    char *result;
} ThreadData;

// Function to validate email
void* validate_email(void* arg) {
    ThreadData *data = (ThreadData*)arg;
    char *email = data->email;

    // Find the '@' symbol
    char *at_pos = strchr(email, '@');
    if (!at_pos) {
        data->result = NULL;
        pthread_exit(NULL);
    }

    // Split username and domain
    char username[MAX_LENGTH];
    char domain[MAX_LENGTH];
    strncpy(username, email, at_pos - email);
    username[at_pos - email] = '\0';
    strcpy(domain, at_pos + 1);

    // Extract domain extension
    char *dot_pos = strrchr(domain, '.');
    if (!dot_pos) {
        data->result = NULL;
        pthread_exit(NULL);
    }

    char extension[MAX_LENGTH];
    strcpy(extension, dot_pos + 1);

    // Validate username starts with alphabet
    if (!isalpha(username[0])) {
        data->result = NULL;
        pthread_exit(NULL);
    }

    // Validate domain extension is ".com" or ".edu"
    if (strcmp(extension, "com") != 0 && strcmp(extension, "edu") != 0) {
        data->result = NULL;
        pthread_exit(NULL);
    }

    // Valid email
    pthread_mutex_lock(&lock);
    validmail_count++;
    pthread_mutex_unlock(&lock);

    data->result = strdup(username); // Return the username
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <emails separated by ';'>\n", argv[0]);
        return 1;
    }

    char *emails = argv[1];
    char *token;
    pthread_t threads[MAX_EMAILS];
    ThreadData thread_data[MAX_EMAILS];
    int thread_count = 0;

    // Initialize mutex
    pthread_mutex_init(&lock, NULL);

    // Split emails by ';'
    token = strtok(emails, ";");
    while (token) {
        strncpy(thread_data[thread_count].email, token, MAX_LENGTH);
        pthread_create(&threads[thread_count], NULL, validate_email, &thread_data[thread_count]);
        thread_count++;
        token = strtok(NULL, ";");
    }

    // Wait for threads to complete and display results
    printf("Results:\n");
    for (int i = 0; i < thread_count; i++) {
        pthread_join(threads[i], NULL);
        if (thread_data[i].result) {
            printf("Thread %d: %s is valid, username: %s\n", i, thread_data[i].email, thread_data[i].result);
            free(thread_data[i].result);
        } else {
            printf("Thread %d: %s is invalid\n", i, thread_data[i].email);
        }
    }

    // Display valid email count
    printf("Total valid emails: %d\n", validmail_count);

    // Destroy mutex
    pthread_mutex_destroy(&lock);
    return 0;
}
