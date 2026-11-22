#include <stdio.h>
#include <stdlib.h>

#define SIZE 100

int stack1[SIZE], stack2[SIZE];
int top1 = -1, top2 = -1;

// Stack operations
void push1(int x)
{
    stack1[++top1] = x;
}

void push2(int x)
{
    stack2[++top2] = x;
}

int pop1()
{
    return stack1[top1--];
}

int pop2()
{
    return stack2[top2--];
}

// Queue Enqueue - Cheap
void enqueue(int x)
{
    push1(x);
    printf("%d inserted\n", x);
}

// Queue Dequeue - Costly
void dequeue()
{
    if (top1 == -1 && top2 == -1)
    {
        printf("Queue Underflow\n");
        return;
    }

    // Transfer elements only if stack2 is empty
    if (top2 == -1)
    {
        while (top1 != -1)
            push2(pop1());
    }

    printf("%d deleted\n", pop2());
}

// Display queue
void display()
{
    if (top1 == -1 && top2 == -1)
    {
        printf("Queue is empty\n");
        return;
    }

    printf("Queue: ");

    // Stack2 contains older elements
    for (int i = top2; i >= 0; i--)
        printf("%d ", stack2[i]);

    // Stack1 contains newer elements
    for (int i = 0; i <= top1; i++)
        printf("%d ", stack1[i]);

    printf("\n");
}

int main()
{
    int choice, value;

    while (1)
    {
        printf("\n--- Queue Using Two Stacks (Method 2) ---\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Display\n");
        printf("4. Exit\n");

        printf("Enter choice: ");
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