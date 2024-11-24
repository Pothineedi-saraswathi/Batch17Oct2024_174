/*
 * A simple program that creates a thread, passes a parameter to it,
 * and returns the value in thread function
 * A memory leak is fixed
 */
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define MAX_THREADS 4
#define LOOP_COUNT 10

void * thread_proc(void * th_p)
{
    uint *pinput = (uint *)(th_p);

    int i = 0;
    while (i++ < LOOP_COUNT)
    {
        (*pinput)++;
        printf("\n Thread id %lu: val:%u", pthread_self(), *pinput);
    }
    free(th_p); // freeing memory allocated for the thread argument
    pthread_exit(NULL);
}

int main()
{
    int retVal = 0;
    uint th_inp = 20;
    pthread_t th_arr[MAX_THREADS];
    pthread_attr_t attr;

    pthread_attr_init(&attr);
    pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);

    for (int i = 0; i < MAX_THREADS; i++)
    {
        uint *val = (uint *) malloc(sizeof(uint));
        if (val == NULL)
        {
            printf("Failed to allocate memory\n");
            return -1;
        }

        *val = th_inp + i;
        retVal = pthread_create(&th_arr[i], NULL, thread_proc, (void *) val);
        if (retVal != 0)
        {
            printf("Thread creation failed\n");
            free(val);
            return -1;
        }
    }

    for (int i = 0; i < MAX_THREADS; i++)
    {
        pthread_join(th_arr[i], NULL);
    }

    return 0;
}
