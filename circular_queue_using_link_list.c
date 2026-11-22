#include <stdio.h>
#include <stdlib.h>

// Structure for a node
struct Node
{
    int data;
    struct Node *next;
};

struct Node *front = NULL;
struct Node *rear = NULL;

// Insert an element
void enqueue(int value)
{
    struct Node *newNode;

    newNode = (struct Node *)malloc(sizeof(struct Node));

    if (newNode == NULL)
    {
        printf("Memory allocation failed\n");
        return;
    }

    newNode->data = value;

    // Queue is empty
    if (front == NULL)
    {
        front = newNode;
        rear = newNode;

        // Last node points to first node
        rear->next = front;
    }
    else
    {
        // Add new node at the rear
        newNode->next = front;
        rear->next = newNode;
        rear = newNode;
    }

    printf("%d inserted\n", value);
}

// Delete an element
void dequeue()
{
    struct Node *temp;

    // Queue is empty
    if (front == NULL)
    {
        printf("Queue Underflow\n");
        return;
    }

    // Only one element
    if (front == rear)
    {
        printf("%d deleted\n", front->data);

        free(front);

        front = NULL;
        rear = NULL;
    }
    else
    {
        temp = front;

        printf("%d deleted\n", front->data);

        // Move front to next node
        front = front->next;

        // Rear must point to new front
        rear->next = front;

        free(temp);
    }
}

// Display the queue
void display()
{
    struct Node *temp;

    if (front == NULL)
    {
        printf("Queue is empty\n");
        return;
    }

    temp = front;
    printf("Circular Queue: ");

    do
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    while (temp != front);

    printf("\n");
}

int main()
{
    int choice, value;

    while (1)
    {
        printf("\n--- Circular Queue Using Linked List ---\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Display\n");
        printf("4. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                printf("Enter value: ");
                scanf("%d", &value);
                enqueue(value);
                break;

            case 2:
                dequeue();
                break;

            case 3:
                display();
                break;

            case 4:
                exit(0);

            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}