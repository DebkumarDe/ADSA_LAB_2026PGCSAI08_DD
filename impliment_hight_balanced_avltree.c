
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data, height;
    struct Node *left, *right;
};

typedef struct Node Node;

// Create empty tree
Node* createTree() {
    return NULL;
}

// Find height
int height(Node *root) {
    if (root == NULL)
        return 0;
    return root->height;
}

// Maximum
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Balance factor
int balance(Node *root) {
    if (root == NULL)
        return 0;
    return height(root->left) - height(root->right);
}

// Create new node
Node* newNode(int value) {
    Node *temp = malloc(sizeof(Node));

    temp->data = value;
    temp->height = 1;
    temp->left = NULL;
    temp->right = NULL;

    return temp;
}

// Right rotation
Node* rightRotate(Node *y) {
    Node *x = y->left;
    Node *t = x->right;

    x->right = y;
    y->left = t;

    y->height = 1 + max(height(y->left), height(y->right));
    x->height = 1 + max(height(x->left), height(x->right));

    return x;
}

// Left rotation
Node* leftRotate(Node *x) {
    Node *y = x->right;
    Node *t = y->left;

    y->left = x;
    x->right = t;

    x->height = 1 + max(height(x->left), height(x->right));
    y->height = 1 + max(height(y->left), height(y->right));

    return y;
}

// Insert item
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

    int bf = balance(root);

    // LL
    if (bf > 1 && value < root->left->data)
        return rightRotate(root);

    // RR
    if (bf < -1 && value > root->right->data)
        return leftRotate(root);

    // LR
    if (bf > 1 && value > root->left->data) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // RL
    if (bf < -1 && value < root->right->data) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Find minimum value node
Node* minNode(Node *root) {
    Node *temp = root;

    while (temp->left != NULL)
        temp = temp->left;

    return temp;
}

// Delete item
Node* deleteItem(Node *root, int value) {
    if (root == NULL)
        return root;

    if (value < root->data)
        root->left = deleteItem(root->left, value);

    else if (value > root->data)
        root->right = deleteItem(root->right, value);

    else {
        if (root->left == NULL || root->right == NULL) {
            Node *temp = root->left ? root->left : root->right;

            if (temp == NULL) {
                free(root);
                return NULL;
            }

            *root = *temp;
            free(temp);
        }
        else {
            Node *temp = minNode(root->right);
            root->data = temp->data;
            root->right = deleteItem(root->right, temp->data);
        }
    }

    if (root == NULL)
        return root;

    root->height = 1 + max(height(root->left), height(root->right));

    int bf = balance(root);

    // LL
    if (bf > 1 && balance(root->left) >= 0)
        return rightRotate(root);

    // LR
    if (bf > 1 && balance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // RR
    if (bf < -1 && balance(root->right) <= 0)
        return leftRotate(root);

    // RL
    if (bf < -1 && balance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Search item
Node* searchItem(Node *root, int value) {
    if (root == NULL || root->data == value)
        return root;

    if (value < root->data)
        return searchItem(root->left, value);

    return searchItem(root->right, value);
}

// Delete complete tree
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

    printf("AVL Tree: ");
    inorder(root);

    if (searchItem(root, 25) != NULL)
        printf("\nItem Found");
    else
        printf("\nItem Not Found");

    root = deleteItem(root, 20);

    printf("\nAfter Deletion: ");
    inorder(root);

    deleteTree(root);
    root = NULL;

    return 0;
}
