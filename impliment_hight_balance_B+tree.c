
#include <stdio.h>
#include <stdlib.h>

#define M 4

struct Node {
    int key[M];
    struct Node *child[M+1];
    int n;
    int leaf;
    struct Node *next;
};

typedef struct Node Node;

// Create a new node
Node* createNode(int leaf) {
    Node *p = malloc(sizeof(Node));

    p->n = 0;
    p->leaf = leaf;
    p->next = NULL;

    for (int i = 0; i <= M; i++)
        p->child[i] = NULL;

    return p;
}

// Create empty tree
Node* createTree() {
    return createNode(1);
}

// Search item
Node* searchItem(Node *root, int key) {
    if (root == NULL)
        return NULL;

    Node *p = root;

    while (!p->leaf) {
        int i = 0;

        while (i < p->n && key >= p->key[i])
            i++;

        p = p->child[i];
    }

    for (int i = 0; i < p->n; i++) {
        if (p->key[i] == key)
            return p;
    }

    return NULL;
}

// Recursive insertion
int insertRec(Node *p, int key, int *sep, Node **right) {
    int i;

    if (p->leaf) {
        int temp[M];

        for (i = 0; i < p->n; i++)
            temp[i] = p->key[i];

        i = p->n - 1;

        while (i >= 0 && temp[i] > key) {
            temp[i+1] = temp[i];
            i--;
        }

        temp[i+1] = key;

        if (p->n < M-1) {
            p->n++;

            for (i = 0; i < p->n; i++)
                p->key[i] = temp[i];

            return 0;
        }

        Node *r = createNode(1);

        p->n = 2;
        r->n = 2;

        for (i = 0; i < 2; i++) {
            p->key[i] = temp[i];
            r->key[i] = temp[i+2];
        }

        r->next = p->next;
        p->next = r;

        *sep = r->key[0];
        *right = r;

        return 1;
    }

    i = 0;

    while (i < p->n && key >= p->key[i])
        i++;

    int newKey;
    Node *newRight = NULL;

    if (!insertRec(p->child[i], key, &newKey, &newRight))
        return 0;

    int tempKey[M];
    Node *tempChild[M+1];

    for (int j = 0; j < p->n; j++)
        tempKey[j] = p->key[j];

    for (int j = 0; j <= p->n; j++)
        tempChild[j] = p->child[j];

    for (int j = p->n; j > i; j--)
        tempKey[j] = tempKey[j-1];

    tempKey[i] = newKey;

    for (int j = p->n+1; j > i+1; j--)
        tempChild[j] = tempChild[j-1];

    tempChild[i+1] = newRight;

    if (p->n < M-1) {
        p->n++;

        for (int j = 0; j < p->n; j++)
            p->key[j] = tempKey[j];

        for (int j = 0; j <= p->n; j++)
            p->child[j] = tempChild[j];

        return 0;
    }

    Node *r = createNode(0);

    *sep = tempKey[2];

    p->n = 2;
    r->n = 1;

    p->key[0] = tempKey[0];
    p->key[1] = tempKey[1];

    r->key[0] = tempKey[3];

    for (int j = 0; j <= 2; j++)
        p->child[j] = tempChild[j];

    for (int j = 0; j <= 1; j++)
        r->child[j] = tempChild[j+3];

    *right = r;

    return 1;
}

// Insert item
Node* insertItem(Node *root, int key) {
    if (searchItem(root, key) != NULL)
        return root;

    int sep;
    Node *right = NULL;

    if (insertRec(root, key, &sep, &right)) {
        Node *newRoot = createNode(0);

        newRoot->key[0] = sep;
        newRoot->child[0] = root;
        newRoot->child[1] = right;
        newRoot->n = 1;

        root = newRoot;
    }

    return root;
}

// Delete entire tree
void deleteTree(Node *root) {
    if (root == NULL)
        return;

    if (!root->leaf) {
        for (int i = 0; i <= root->n; i++)
            deleteTree(root->child[i]);
    }

    free(root);
}

// Store all leaf keys
void collect(Node *root, int **arr, int *count, int *capacity) {
    if (root == NULL)
        return;

    if (root->leaf) {
        for (int i = 0; i < root->n; i++) {
            if (*count == *capacity) {
                *capacity = (*capacity == 0) ? 8 : *capacity * 2;
                *arr = realloc(*arr, *capacity * sizeof(int));
            }

            (*arr)[(*count)++] = root->key[i];
        }
    }
    else {
        for (int i = 0; i <= root->n; i++)
            collect(root->child[i], arr, count, capacity);
    }
}

// Delete item
Node* deleteItem(Node *root, int key) {
    if (searchItem(root, key) == NULL)
        return root;

    int *arr = NULL;
    int count = 0, capacity = 0;

    collect(root, &arr, &count, &capacity);

    deleteTree(root);

    root = createTree();

    for (int i = 0; i < count; i++) {
        if (arr[i] != key)
            root = insertItem(root, arr[i]);
    }

    free(arr);

    return root;
}

// Display B+ Tree leaf keys
void display(Node *root) {
    if (root == NULL)
        return;

    while (!root->leaf)
        root = root->child[0];

    while (root != NULL) {
        for (int i = 0; i < root->n; i++)
            printf("%d ", root->key[i]);

        root = root->next;
    }
}

// Main function
int main() {
    Node *root = createTree();

    root = insertItem(root, 10);
    root = insertItem(root, 20);
    root = insertItem(root, 5);
    root = insertItem(root, 6);
    root = insertItem(root, 12);
    root = insertItem(root, 30);
    root = insertItem(root, 7);
    root = insertItem(root, 17);

    printf("B+ Tree: ");
    display(root);

    if (searchItem(root, 12) != NULL)
        printf("\n12 Found");
    else
        printf("\n12 Not Found");

    root = deleteItem(root, 6);

    printf("\nAfter deletion: ");
    display(root);

    deleteTree(root);
    root = NULL;

    return 0;
}
