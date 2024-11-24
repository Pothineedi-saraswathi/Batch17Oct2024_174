/****************************************************************************
 * *
 * * FILE NAME:     function.c
 * *
 * * DESCRIPTION:   Includes all the functions of queue 
 *
 * DATE            NAME            REFERENCE       REASON
 *
 ***************************************************************************/

/***************************************************************************
 *                       Header Files                                      *
 ***************************************************************************/
#include "header.h"

/**************************************************************************
 *        FUNCTION NAME:          init_queue
 *        DESCRIPTION:            Initialize queue to empty
 *        RETURNS:                None
 **************************************************************************/
void init_queue(queue_t *q) {
    q->front = END;
    q->rear = END;
    q->data = (char **)malloc(MAX_QUEUE_SIZE * sizeof(char *));
    for (int i = 0; i < MAX_QUEUE_SIZE; i++) {
        q->data[i] = NULL;
    }
}

/**************************************************************************
 *        FUNCTION NAME:          check_empty
 *        DESCRIPTION:            Check queue if empty
 *        RETURNS:                SUCCESS or FAILURE
 **************************************************************************/
int check_empty(queue_t *q) {
    return (q->front == END) ? SUCCESS : FAILURE;
}

/**************************************************************************
 *        FUNCTION NAME:          check_full
 *        DESCRIPTION:            Check queue if full
 *        RETURNS:                SUCCESS or FAILURE
 **************************************************************************/
int check_full(queue_t *q) {
    return (q->front == ((q->rear + 1) % MAX_QUEUE_SIZE)) ? SUCCESS : FAILURE;
}

/**************************************************************************
 *        FUNCTION NAME:          enqueue
 *        DESCRIPTION:            Insert a string into the queue
 *        RETURNS:                SUCCESS or FAILURE
 **************************************************************************/
int enqueue(queue_t *q, char *str) {
    if (check_full(q)) {
        return FAILURE; // Queue is full
    }

    if (check_empty(q)) {
        q->front = 0;
        q->rear = 0;
    } else {
        q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    }

    q->data[q->rear] = (char *)malloc(strlen(str) + 1);
    strcpy(q->data[q->rear], str);

    return SUCCESS;
}

/**************************************************************************
 *        FUNCTION NAME:          dequeue
 *        DESCRIPTION:            Remove a string from the queue
 *        RETURNS:                SUCCESS or FAILURE
 **************************************************************************/
int dequeue(queue_t *q, char **str) {
    if (check_empty(q)) {
        return FAILURE; // Queue is empty
    }

    *str = q->data[q->front];
    q->data[q->front] = NULL;

    if (q->front == q->rear) {
        q->front = END;
        q->rear = END;
    } else {
        q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    }

    return SUCCESS;
}

/**************************************************************************
 *        FUNCTION NAME:          display
 *        DESCRIPTION:            Display the contents of the queue
 **************************************************************************/
void display(queue_t *q) {
    if (check_empty(q)) {
        printf("Queue is empty\n");
        return;
    }

    printf("Queue contents:\n");
    int index = q->front;
    do {
        printf("[%d]: %s\n", index, q->data[index]);
        index = (index + 1) % MAX_QUEUE_SIZE;
    } while (index != (q->rear + 1) % MAX_QUEUE_SIZE);
}

/**************************************************************************
 *        FUNCTION NAME:          clean_queue
 *        DESCRIPTION:            Free all allocated memory
 **************************************************************************/
void clean_queue(queue_t *q) {
    for (int i = 0; i < MAX_QUEUE_SIZE; i++) {
        if (q->data[i] != NULL) {
            free(q->data[i]);
        }
    }
    free(q->data);
}
