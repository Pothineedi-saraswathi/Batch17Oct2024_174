/*******************************************************************************
*
*     FILENAME       :    main.c
*
*     DESCRIPTION    :    This file defines the main function for queue operations.
*
*******************************************************************************/

#include "header.h"

int main(void)
{
    node *front = NULL, *rear = NULL;
    int status, choice;

    do
    {
        printf("\n1. Insert\n");
        printf("2. Remove\n");
        printf("3. Display\n");
        printf("4. Exit\n");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
        {
            printf("Enter the integer value: ");
            int num;
            scanf("%d", &num);

            printf("Enter the string (max 80 chars): ");
            char string[MAX_STRING_LENGTH];
            scanf(" %[^\n]", string);

            enqueue(&front, &rear, num, string);
            break;
        }
        case 2:
        {
            status = dequeue(&front, &rear);
            if (FAILURE == status)
                printf("Queue is empty, cannot delete\n");
            else
                printf("Element deleted successfully\n");
            break;
        }
        case 3:
        {
            display(front);
            break;
        }
        case 4:
            break;
        default:
            printf("Invalid choice, try again\n");
        }
    } while (choice != 4);

    status = free_queue(front, rear);
    if (SUCCESS == status)
        printf("Memory freed\n");
    else
        printf("Queue was already empty\n");

    return SUCCESS;
}
