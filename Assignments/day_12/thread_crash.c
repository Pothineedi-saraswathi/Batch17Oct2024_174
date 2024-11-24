
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

#define SUCCESS 0
#define FAILURE 1
#define MAX 100

void *write_to_file(void *arg);  // Forward declaration of write function

// Thread function to read from file f1.txt
void *read_from_file(void *arg)
{
    FILE *fptr1;
    pthread_t tid2;
    int ret = 0;
    char str[MAX];

    fptr1 = fopen((char *)arg, "r");
    if (fptr1 == NULL) {
        perror("Error opening f1.txt");
        exit(1);
    }

    // Read each line from f1.txt and create a new thread for each line
    while (fgets(str, MAX, fptr1) != NULL) {
        int len = strlen(str);
        // Remove newline character if present
        if (str[len - 1] == '\n') {
            str[len - 1] = '\0';
        }

        // Create a new thread to handle each line
        ret = pthread_create(&tid2, NULL, write_to_file, (void *)str);
        if (ret != 0) {
            fprintf(stderr, "Thread creation failed.");
            exit(1);
        }

        // Wait for the thread to finish
        ret = pthread_join(tid2, NULL);
        if (ret != 0) {
            fprintf(stderr, "Thread join failed.");
            exit(1);
        }
    }

    fclose(fptr1);
    return NULL;
}

// Thread function to write a line to f2.txt
void *write_to_file(void *arg)
{
    FILE *fptr2;
    int len = 0;

    // Open the output file in append mode so it doesn't get overwritten
    fptr2 = fopen("f2.txt", "a");
    if (fptr2 == NULL) {
        perror("Error opening f2.txt");
        exit(1);
    }

    // Get the length of the line and write it to the output file
    len = strlen((char *)arg);
    fprintf(fptr2, "%d:%s\n", len, (char *)arg);

    fclose(fptr2);
    return NULL;
}

int main()
{
    pthread_t tid;
    int ret = 0;

    // Create the first thread to read from f1.txt
    ret = pthread_create(&tid, NULL, read_from_file, "f1.txt");
    if (ret != 0) {
        fprintf(stderr, "Thread creation failed.");
        exit(1);
    }

    // Wait for the first thread to finish
    ret = pthread_join(tid, NULL);
    if (ret != 0) {
        fprintf(stderr, "Thread join failed.");
        exit(1);
    }

    return SUCCESS;
}
