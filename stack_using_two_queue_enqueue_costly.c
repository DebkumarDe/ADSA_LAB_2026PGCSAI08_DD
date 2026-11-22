#include <stdio.h>
#include <stdlib.h>

#define SIZE 100

int q1[SIZE], q2[SIZE];
int front1 = 0, rear1 = -1;
int front2 = 0, rear2 = -1;

// Queue 1 operations
void enqueue1(int x)
{
    q1[++rear1] = x;
}

int dequeue1()
{
    return q1[front1++];
}

// Queue 2 operations
void enqueue2(int x)
{
    q2[++rear2] = x;
}

int dequeue2()
{
    return q2[front2++];
}

// Stack PUSH - Costly
void push(int x)
{
    // Move all elements from Queue 1 to Queue 2
    while (front1 <= rear1)
        enqueue2(dequeue1());

    // Insert new element into Queue 1
    enqueue1(x);

    // Move elements back to Queue 1
    while (front2 <= rear2)
        enqueue1(dequeue2());

    // Reset Queue 2
    front2 = 0;
    rear2 = -1;

    printf("%d pushed\n", x);
}

// Stack POP - Cheap
void pop()
{
    if (front1 > rear1)
    {
        printf("Stack Underflow\n");
        return;
    }

    printf("%d popped\n", dequeue1());
}

// Display stack
void display()
{
    if (front1 > rear1)
    {
        printf("Stack is empty\n");
        return;
    }

    printf("Stack: ");

    for (int i = front1; i <= rear1; i++)
        printf("%d ", q1[i]);

    printf("\n");
}

int main()
{
    int choice, value;

    while (1)
    {
        printf("\n--- Stack Using Two Queues ---\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Display\n");
        printf("4. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                printf("Enter value: ");
                scanf("%d", &value);
                push(value);
                break;

            case 2:
                pop();
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