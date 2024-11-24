/*******************************************************************************
*
*     FILENAME       :    functions.c
*
*     DESCRIPTION    :    This file defines the various functions on queue.
*
*******************************************************************************/

#include "header.h"

/*******************************************************************************
* Function Definitions
*******************************************************************************/

int isempty(node *front)
{
    return (NULL == front) ? SUCCESS : FAILURE;
}

void enqueue(node **front, node **rear, int value, char *string)
{
    node *newnode = (node *)malloc(sizeof(node));
    if (NULL == newnode)
    {
        printf("Memory not available\n");
        exit(FAILURE);
    }

    newnode->data = value;
    newnode->data_str = (char *)malloc(MAX_STRING_LENGTH);
    if (NULL == newnode->data_str)
    {
        printf("Memory not available for string\n");
        free(newnode);
        exit(FAILURE);
    }
    strncpy(newnode->data_str, string, MAX_STRING_LENGTH - 1);
    newnode->data_str[MAX_STRING_LENGTH - 1] = '\0';
    newnode->next = NULL;

    if (isempty(*front))
    {
        *front = newnode;
        *rear = newnode;
    }
    else
    {
        (*rear)->next = newnode;
        *rear = newnode;
    }
}

int dequeue(node **front, node **rear)
{
    if (isempty(*front))
    {
        printf("Queue Underflow\n");
        return FAILURE;
    }

    node *temp_node = *front;
    if (*front == *rear)
    {
        *front = NULL;
        *rear = NULL;
    }
    else
    {
        *front = (*front)->next;
    }

    printf("Element deleted is %d, String: %s\n", temp_node->data, temp_node->data_str);
    free(temp_node->data_str);
    free(temp_node);
    return SUCCESS;
}

void display(node *front)
{
    if (isempty(front))
    {
        printf("The Queue is empty\n");
    }
    else
    {
        printf("Queue contents:\n");
        for (node *current = front; current != NULL; current = current->next)
        {
            printf("Data: %d, String: %s\n", current->data, current->data_str);
        }
    }
}

int free_queue(node *front, node *rear)
{
    if (isempty(front))
    {
        return FAILURE;
    }

    while (front != NULL)
    {
        node *current = front->next;
        free(front->data_str);
        free(front);
        front = current;
    }

    rear = NULL;
    return SUCCESS;
}
