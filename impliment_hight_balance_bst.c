
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    int height;
    struct Node *left, *right;
};

typedef struct Node Node;

// Create an empty tree
Node* createTree() {
    return NULL;
}

// Find height
int height(Node *root) {
    if (root == NULL)
        return 0;

    return root->height;
}

// Find maximum
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Calculate balance factor
int balanceFactor(Node *root) {
    if (root == NULL)
        return 0;

    return height(root->left) - height(root->right);
}

// Right rotation (LL case)
Node* rightRotate(Node *y) {
    Node *x = y->left;
    Node *t = x->right;

    x->right = y;
    y->left = t;

    y->height = 1 + max(height(y->left), height(y->right));
    x->height = 1 + max(height(x->left), height(x->right));

    return x;
}

// Left rotation (RR case)
Node* leftRotate(Node *x) {
    Node *y = x->right;
    Node *t = y->left;

    y->left = x;
    x->right = t;

    x->height = 1 + max(height(x->left), height(x->right));
    y->height = 1 + max(height(y->left), height(y->right));

    return y;
}

// Create new node
Node* newNode(int value) {
    Node *temp = malloc(sizeof(Node));

    temp->data = value;
    temp->left = NULL;
    temp->right = NULL;
    temp->height = 1;

    return temp;
}

// Insert an item
Node* insertItem(Node *root, int value) {
    if (root == NULL)
        return newNode(value);

    if (value < root->data)
        root->left = insertItem(root->left, value);

    else if (value > root->data)
        root->right = insertItem(root->right, value);

    else
        return root;

    root->height = 1 + max(height(root->left), height(root->right));

    int bf = balanceFactor(root);

    // LL Case
    if (bf > 1 && value < root->left->data)
        return rightRotate(root);

    // RR Case
    if (bf < -1 && value > root->right->data)
        return leftRotate(root);

    // LR Case
    if (bf > 1 && value > root->left->data) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // RL Case
    if (bf < -1 && value < root->right->data) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Find minimum node
Node* minValueNode(Node *root) {
    Node *current = root;

    while (current->left != NULL)
        current = current->left;

    return current;
}

// Delete an item
Node* deleteItem(Node *root, int value) {
    if (root == NULL)
        return root;

    if (value < root->data)
        root->left = deleteItem(root->left, value);

    else if (value > root->data)
        root->right = deleteItem(root->right, value);

    else {
        if (root->left == NULL || root->right == NULL) {
            Node *temp;

            if (root->left != NULL)
                temp = root->left;
            else
                temp = root->right;

            if (temp == NULL) {
                temp = root;
                root = NULL;
            }
            else {
                *root = *temp;
            }

            free(temp);
        }
        else {
            Node *temp = minValueNode(root->right);

            root->data = temp->data;

            root->right = deleteItem(root->right, temp->data);
        }
    }

    if (root == NULL)
        return root;

    root->height = 1 + max(height(root->left), height(root->right));

    int bf = balanceFactor(root);

    // LL Case
    if (bf > 1 && balanceFactor(root->left) >= 0)
        return rightRotate(root);

    // LR Case
    if (bf > 1 && balanceFactor(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // RR Case
    if (bf < -1 && balanceFactor(root->right) <= 0)
        return leftRotate(root);

    // RL Case
    if (bf < -1 && balanceFactor(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Search an item
Node* searchItem(Node *root, int value) {
    if (root == NULL || root->data == value)
        return root;

    if (value < root->data)
        return searchItem(root->left, value);

    return searchItem(root->right, value);
}

// Delete entire tree
void deleteTree(Node *root) {
    if (root == NULL)
        return;

    deleteTree(root->left);
    deleteTree(root->right);

    free(root);
}

// Inorder traversal
void inorder(Node *root) {
    if (root == NULL)
        return;

    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

int main() {
    Node *root = createTree();

    root = insertItem(root, 30);
    root = insertItem(root, 20);
    root = insertItem(root, 10);
    root = insertItem(root, 25);
    root = insertItem(root, 40);
    root = insertItem(root, 50);

    printf("Inorder: ");
    inorder(root);

    if (searchItem(root, 25) != NULL)
        printf("\n25 Found");
    else
        printf("\n25 Not Found");

    root = deleteItem(root, 20);

    printf("\nAfter deletion: ");
    inorder(root);

    deleteTree(root);

    return 0;
}
