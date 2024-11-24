/*******************************************************************************
*
*     FILENAME       :    header.h
*
*     DESCRIPTION    :    This file defines the macros and the structure of the
*                       node used for the queue.
*
*******************************************************************************/

/********************** Header File Inclusions ********************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/********************** Macro definitions *************************************/
#define SUCCESS 1
#define FAILURE 0
#define MAX_STRING_LENGTH 80

/********************** Structure Definition **********************************/
typedef struct node_q
{
    int data;
    char *data_str; // String data for user input
    struct node_q *next;
} node;

/********************** Function Declaration **********************************/
void enqueue(node **, node **, int, char *);
int dequeue(node **, node **);
int isempty(node *);
void display(node *);
int free_queue(node *, node *);
