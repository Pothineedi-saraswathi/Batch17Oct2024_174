/****************************************************************************
 * *
 * * FILE NAME:     main.c
 * *
 * * DESCRIPTION:   Contains the main function for various operations on the queue
 *
 * DATE            NAME            REFERENCE       REASON
 *
 ***************************************************************************/

/***************************************************************************
 *                       Header Files                                      *
 ***************************************************************************/
#include "header.h"

/**************************************************************************
 *        FUNCTION NAME:          main
 *        DESCRIPTION:            Invokes all the functions of the queue
 **************************************************************************/
int main() {
    queue_t q1;
    int option;
    char input[100];   // Buffer for input strings
    char *removed_str; // Pointer to store dequeued string

    // Initialize the Queue
    init_queue(&q1);

    // Main Input loop (Driver Loop)
    while (1) {
        printf("\nPlease enter your choice.\n");
        printf("1) Insert a string\n");
        printf("2) Remove a string\n");
        printf("3) Check Empty\n");
        printf("4) Check Full\n");
        printf("5) Display the queue\n");
        printf("6) Exit\n");

        scanf("%d", &option);
        getchar(); // Clear newline character

        switch (option) {
            case 1: /* Insert a string */
                printf("Enter the string: ");
                fgets(input, sizeof(input), stdin);
                input[strcspn(input, "\n")] = '\0'; // Remove trailing newline
                if (enqueue(&q1, input) == SUCCESS) {
                    printf("String inserted successfully\n");
                } else {
                    printf("Queue is full, cannot insert\n");
                }
                break;

            case 2: /* Remove a string */
                if (dequeue(&q1, &removed_str) == SUCCESS) {
                    printf("Removed string: %s\n", removed_str);
                    free(removed_str); // Free memory of dequeued string
                } else {
                    printf("Queue is empty, cannot remove\n");
                }
                break;

            case 3: /* Check Empty */
                printf(check_empty(&q1) == SUCCESS ? "Queue is empty\n" : "Queue is not empty\n");
                break;

            case 4: /* Check Full */
                printf(check_full(&q1) == SUCCESS ? "Queue is full\n" : "Queue is not full\n");
                break;

            case 5: /* Display */
                display(&q1);
                break;

            case 6: /* Exit */
                clean_queue(&q1); // Clean memory
                exit(0);

            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}
