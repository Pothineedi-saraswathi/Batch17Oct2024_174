/****************************************************************************
 * 
 * FILE NAME:     header.h
 * 
 * DESCRIPTION:   All declarations of the queue functions and data structures
 *
 * DATE           NAME            REFERENCE       REASON
 *
 ***************************************************************************/

/***************************************************************************
 *                       Header Files                                      *
 ***************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/***************************************************************************
 *                       Macro Declarations                                *
 ***************************************************************************/
#define SUCCESS 1
#define FAILURE 0
#define END -1
#define MAX_QUEUE_SIZE 5 // Configurable size for the queue

/***************************************************************************
 *                       Data Type for Queue ADT                          *
 ***************************************************************************/
typedef struct queue {
    char **data;   // Array of strings
    int front;     // Front index
    int rear;      // Rear index
} queue_t;

/***************************************************************************
 *                       Function Declarations                             *
 ***************************************************************************/
void init_queue(queue_t *q);
int check_empty(queue_t *q);
int check_full(queue_t *q);
int enqueue(queue_t *q, char *str);
int dequeue(queue_t *q, char **str);
void display(queue_t *q);
void clean_queue(queue_t *q);
