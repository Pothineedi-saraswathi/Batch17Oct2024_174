/*
 * A simple program creating multiple threads,
 * which updates a passed argument,
 * fixed number of times and finally returns to the main thread
 * Main thread waits for child threads to terminate and returns
 * Issue - Program has a memory leak fixed
 */

#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define MAX_THREADS 3
#define LOOP_COUNT 10
#define FAILURE 1
#define SUCCESS 0

#define  FREE(x) \
{ \
    if ( x != NULL) \
    { \
        free(x); \
        x = NULL; \
    } \
}

//thread proc function receiving a uint value
void *thread_proc(void * thr_p)
{   
    uint *pinput = (uint *)(thr_p);
    int i = 0;
    int *retval = (int *)malloc(sizeof(int));
    if (retval == NULL)
    {
        pthread_exit((void*)retval);
    }

    printf("threadproc  threadid : %lu\n", pthread_self());
    if (*pinput)
    {
        while (*pinput > 0)
        {
            (*pinput)++;

            //shall decrement at regular intervals
            sleep(1);

            printf("\n Thread id %d: val:%u", (uint)pthread_self(), *pinput);

            if (++i >= LOOP_COUNT)
                break;
        }
    }
    printf("\n Thread id %d: val:%u",(uint) pthread_self(), *pinput);
    *retval = *pinput;
    pthread_exit ((void *)retval );
}

/*
main creates two threads and waits for them to exit
Each child  thread is passed with an integer value and is updated
a fixed number of times at regular intervals.
The final updated value is returned to the main thread
*/
int main(int argc, char *argv[])
{
    int retval;
    pthread_t *th_arr[MAX_THREADS] = {0};
    pthread_attr_t *th_attr[MAX_THREADS] = {0};
    int i = 0;
    uint startval = 10;
    int retVal = 0;
    int max_thread_cnt = 0;
    for (i = 0; i < MAX_THREADS; i++)
    {
        th_attr[i] = (pthread_attr_t *) malloc(sizeof(pthread_attr_t));
        if (th_attr[i] == NULL)
        {
            printf("\n Malloc failure");
            break;
        }
        pthread_attr_init(th_attr[i]); /* initialize attr with default attribute */
        pthread_attr_setscope(th_attr[i],PTHREAD_SCOPE_SYSTEM); 

        uint *val = (uint*) malloc(sizeof(uint) );
        if (val)
        {
            *val = startval + (i * 2);
         
            th_arr[i] = (pthread_t*) malloc(sizeof(pthread_t));
            if (th_arr[i] == NULL)
            {
                printf("\n Malloc failure");
                FREE(th_attr[i])
                break;
            }
            retVal = pthread_create(th_arr[i], NULL, thread_proc, (void*)(val));
            if (0 != retVal)
            {
                printf("thread creation failed");
                FREE(th_attr[i])

                break;
            }         
            max_thread_cnt++;
        }
    }
    /* Joining the threads and releasing the memory held by both threads */
    for (i=0; i < max_thread_cnt; i++)
    {
        uint *th_out = NULL;  
        
        retval = pthread_join(*th_arr[i], (void**)&th_out);
        printf("thread %d output return %d\n",i,  *th_out);
        if (0 != retval)
        {
            printf("thread join failed\n");
        }
    }

    //FREE allocated memory
    for (i = 0; i < max_thread_cnt; i++)
    {
        FREE(th_attr[i]);
        FREE(th_arr[i]);
    }
    return 0;
}


