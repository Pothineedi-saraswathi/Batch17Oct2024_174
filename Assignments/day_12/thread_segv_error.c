/*
 * A program where a thread manipulates a global variable, 
 * checks boundary issues and returns a result. This fixes memory leaks.
 */

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define MAX_THREADS 4

pthread_attr_t th_attr[MAX_THREADS];
pthread_t th_arr[MAX_THREADS];

void * thread_proc1(void *th_p)
{
    char *dnsname = (char *) malloc(64);
    if (dnsname == NULL)
    {
        printf("Memory allocation failed\n");
        pthread_exit(NULL);
    }

    snprintf(dnsname, 64, "Hello from thread");
    printf("Thread with dnsname: %s\n", dnsname);
    free(dnsname);  // free memory after usage

    pthread_exit(NULL);
}

int main()
{
    int retVal = 0;

    for (int i = 0; i < MAX_THREADS; i++)
    {
        retVal = pthread_create(&th_arr[i], NULL, thread_proc1, NULL);
        if (retVal != 0)
        {
            printf("Thread creation failed\n");
            return -1;
        }
    }

    for (int i = 0; i < MAX_THREADS; i++)
    {
        pthread_join(th_arr[i], NULL);
    }

    return 0;
}
