#include <stdio.h>
#include <stdlib.h>

#define SIZE 100

int q1[SIZE], q2[SIZE];

int front1 = 0, rear1 = -1;
int front2 = 0, rear2 = -1;

// Queue operations
void enqueue1(int x)
{
    q1[++rear1] = x;
}

int dequeue1()
{
    return q1[front1++];
}

void enqueue2(int x)
{
    q2[++rear2] = x;
}

int dequeue2()
{
    return q2[front2++];
}

// Stack PUSH - Cheap
void push(int x)
{
    enqueue1(x);

    printf("%d pushed\n", x);
}

// Stack POP - Costly
void pop()
{
    if (front1 > rear1)
    {
        printf("Stack Underflow\n");
        return;
    }

    // Move all elements except last
    while (front1 < rear1)
        enqueue2(dequeue1());

    // Last element is the stack top
    printf("%d popped\n", dequeue1());

    // Move elements back to Queue 1
    while (front2 <= rear2)
        enqueue1(dequeue2());

    // Reset Queue 2
    front2 = 0;
    rear2 = -1;
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

    // Display from newest to oldest
    for (int i = rear1; i >= front1; i--)
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