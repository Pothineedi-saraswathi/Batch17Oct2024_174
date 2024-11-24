/*
 * A simple program having three threads
 * startroutine1 is the entry point function of the first thread created by the main thread
 * startroutine2 is the entry point function of the second thread created by the main thread
 * This inturn creates an other thread which displays the lsb byte of  passed input
 * This program has a memory leak fixed
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include <pthread.h>

#define LOOPSZ 8

int t1retval = 2;

/*
startroutine1 takes an input and prints it after properly typecasting it
*/

void * startroutine1(void * thr_p) 
{
    int i = 0;
    int pinput = thr_p ? *((int *) thr_p) : 0;
    
    printf("startroutine1  threadid : %lu\n", pthread_self());

    while (i++ < LOOPSZ)
    {
        printf("startroutine1: %d %d\n", i, pinput);
        sleep(1);
        (pinput++);
    }
    return ((void *) &t1retval);
}

/*
thread proc function to extract and display the lsb of the input number
*/
void * displsb(void * thr_p)
{   
    uint *val = thr_p ? ((uint*) thr_p) : 0;

    if (val)
    {
        printf("LSB of %x is %x",(*val), (*val << 24 ) >> 24);
        free(val);
    }
    pthread_exit(NULL);
}

/*
startroutine2 creates N child thread  which finds the lsb of the
passed input value 
*/
void * startroutine2(void * thr_p)
{   
    uint pinput = thr_p ? *((uint *) thr_p) : 0;
    int ret = 0;
    pthread_t tarr[2];

    printf("startroutine2  threadid : %lu\n", pthread_self());

    if (pinput)
    {
        uint *inp = (uint *) malloc(sizeof(uint));
        if (inp)
        {
            *inp = pinput;
            int retval = 0;

            ret = pthread_create(&tarr[0], NULL, displsb, inp);
            if (0 == ret)
            {
                retval = pthread_join(tarr[0],(void**) NULL);
                if (retval != 0)
                {
                    printf("\n Failed to join");
                }
            }
        }
    }
    pthread_exit ((void *) NULL);
}

/*
main creates thread and within child thread an other thread is created
one of the thread is passed the address of an allocated variable defined in main whereas the other one is given a NULL parameter
*/
int main(int argc, char *argv[])
{
    int retval = 0;
    uint th_inp = 0xABCDEF01;
    int * pthreadoutput;
    int thread1input = 10;
    pthread_t tidOne;
    pthread_t tidTwo;
    pthread_attr_t attr;

    pthread_attr_init(&attr); /* initialize attr with default attribute */
    pthread_attr_setscope(&attr,PTHREAD_SCOPE_SYSTEM); 
    /* creating two threads */
    retval = pthread_create(&tidOne, NULL, startroutine1, (void *)(&thread1input));
    if (0 != retval)
    {
        printf("thread creation failed\n");
        return (-1);
    }
    printf("\n Thread 1:%lu\n", tidOne);

    retval = pthread_create(&tidTwo, NULL, startroutine2, (void *)(&th_inp));
    if (0 != retval)
    {
        printf("thread creation failed\n");
        return (-1);
    }
    
    /* Joining the threads and releasing the memory held by both threads */
    printf("\n Thread 2: %lu\n", tidTwo);
    retval = pthread_join(tidOne, (void**)&pthreadoutput);

    if (pthreadoutput)
    {
        printf("threadoutput %d\n", *pthreadoutput);
    }

    if (0 != retval)
    {
        printf("thread join failed\n");
        return (-1);
    }

    retval = pthread_join(tidTwo, (void**)&pthreadoutput);
    if (pthreadoutput)
    {
        printf("threadoutput %d\n", *pthreadoutput);
    }

    if (0 != retval)
    {
        printf("thread join failed\n");
        return (-1);
    }
    return 0;
}
