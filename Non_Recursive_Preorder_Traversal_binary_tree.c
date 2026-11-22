
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *left, *right;
};

void preorder(struct Node *root) {
    struct Node *stack[100];
    int top = -1;

    if (root == NULL)
        return;

    stack[++top] = root;

    while (top != -1) {
        struct Node *temp = stack[top--];

        printf("%d ", temp->data);

        if (temp->right != NULL)
            stack[++top] = temp->right;

        if (temp->left != NULL)
            stack[++top] = temp->left;
    }
}

int main() {
    struct Node *root = malloc(sizeof(struct Node));
    root->data = 1;

    root->left = malloc(sizeof(struct Node));
    root->right = malloc(sizeof(struct Node));

    root->left->data = 2;
    root->right->data = 3;

    root->left->left = malloc(sizeof(struct Node));
    root->left->right = malloc(sizeof(struct Node));

    root->left->left->data = 4;
    root->left->right->data = 5;

    root->left->left->left = NULL;
    root->left->left->right = NULL;
    root->left->right->left = NULL;
    root->left->right->right = NULL;

    root->right->left = NULL;
    root->right->right = NULL;

    printf("Preorder: ");
    preorder(root);

    return 0;
}
