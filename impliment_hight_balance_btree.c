
#include <stdio.h>
#include <stdlib.h>

#define T 2

struct Node {
    int key[2*T-1];
    struct Node *child[2*T];
    int n;
    int leaf;
};

typedef struct Node Node;
// Function declarations
void borrowPrev(Node *x, int idx);
void borrowNext(Node *x, int idx);

// Create a new node
Node* createNode(int leaf) {
    Node *newNode = malloc(sizeof(Node));

    newNode->n = 0;
    newNode->leaf = leaf;

    for (int i = 0; i < 2*T; i++)
        newNode->child[i] = NULL;

    return newNode;
}

// Create empty tree
Node* createTree() {
    return createNode(1);
}

// Search item
Node* searchItem(Node *root, int key) {
    int i = 0;

    while (i < root->n && key > root->key[i])
        i++;

    if (i < root->n && key == root->key[i])
        return root;

    if (root->leaf)
        return NULL;

    return searchItem(root->child[i], key);
}

// Split full child
void splitChild(Node *x, int i) {
    Node *y = x->child[i];
    Node *z = createNode(y->leaf);

    z->n = T-1;

    for (int j = 0; j < T-1; j++)
        z->key[j] = y->key[j+T];

    if (!y->leaf) {
        for (int j = 0; j < T; j++)
            z->child[j] = y->child[j+T];
    }

    y->n = T-1;

    for (int j = x->n; j >= i+1; j--)
        x->child[j+1] = x->child[j];

    x->child[i+1] = z;

    for (int j = x->n-1; j >= i; j--)
        x->key[j+1] = x->key[j];

    x->key[i] = y->key[T-1];
    x->n++;
}

// Insert into non-full node
void insertNonFull(Node *x, int key) {
    int i = x->n-1;

    if (x->leaf) {
        while (i >= 0 && key < x->key[i]) {
            x->key[i+1] = x->key[i];
            i--;
        }

        x->key[i+1] = key;
        x->n++;
    }
    else {
        while (i >= 0 && key < x->key[i])
            i--;

        i++;

        if (x->child[i]->n == 2*T-1) {
            splitChild(x, i);

            if (key > x->key[i])
                i++;
        }

        insertNonFull(x->child[i], key);
    }
}

// Insert item
Node* insertItem(Node *root, int key) {
    if (searchItem(root, key) != NULL)
        return root;

    if (root->n == 2*T-1) {
        Node *s = createNode(0);

        s->child[0] = root;

        splitChild(s, 0);

        int i = 0;

        if (key > s->key[0])
            i++;

        insertNonFull(s->child[i], key);

        return s;
    }

    insertNonFull(root, key);

    return root;
}

// Find predecessor
int predecessor(Node *x) {
    while (!x->leaf)
        x = x->child[x->n];

    return x->key[x->n-1];
}

// Find successor
int successor(Node *x) {
    while (!x->leaf)
        x = x->child[0];

    return x->key[0];
}

// Merge two children
void merge(Node *x, int idx) {
    Node *child = x->child[idx];
    Node *sibling = x->child[idx+1];

    child->key[T-1] = x->key[idx];

    for (int i = 0; i < sibling->n; i++)
        child->key[i+T] = sibling->key[i];

    if (!child->leaf) {
        for (int i = 0; i <= sibling->n; i++)
            child->child[i+T] = sibling->child[i];
    }

    for (int i = idx+1; i < x->n; i++)
        x->key[i-1] = x->key[i];

    for (int i = idx+2; i <= x->n; i++)
        x->child[i-1] = x->child[i];

    child->n += sibling->n+1;
    x->n--;

    free(sibling);
}

// Fill child having minimum keys
void fill(Node *x, int idx) {
    if (idx != 0 && x->child[idx-1]->n >= T)
        borrowPrev(x, idx);

    else if (idx != x->n && x->child[idx+1]->n >= T)
        borrowNext(x, idx);

    else {
        if (idx != x->n)
            merge(x, idx);
        else
            merge(x, idx-1);
    }
}

// Borrow from previous sibling
void borrowPrev(Node *x, int idx) {
    Node *child = x->child[idx];
    Node *sibling = x->child[idx-1];

    for (int i = child->n-1; i >= 0; i--)
        child->key[i+1] = child->key[i];

    if (!child->leaf) {
        for (int i = child->n; i >= 0; i--)
            child->child[i+1] = child->child[i];
    }

    child->key[0] = x->key[idx-1];

    if (!child->leaf)
        child->child[0] = sibling->child[sibling->n];

    x->key[idx-1] = sibling->key[sibling->n-1];

    child->n++;
    sibling->n--;
}

// Borrow from next sibling
void borrowNext(Node *x, int idx) {
    Node *child = x->child[idx];
    Node *sibling = x->child[idx+1];

    child->key[child->n] = x->key[idx];

    if (!child->leaf)
        child->child[child->n+1] = sibling->child[0];

    x->key[idx] = sibling->key[0];

    for (int i = 1; i < sibling->n; i++)
        sibling->key[i-1] = sibling->key[i];

    if (!sibling->leaf) {
        for (int i = 1; i <= sibling->n; i++)
            sibling->child[i-1] = sibling->child[i];
    }

    child->n++;
    sibling->n--;
}

// Delete from node
void deleteNode(Node *x, int key) {
    int idx = 0;

    while (idx < x->n && x->key[idx] < key)
        idx++;

    if (idx < x->n && x->key[idx] == key) {
        if (x->leaf) {
            for (int i = idx+1; i < x->n; i++)
                x->key[i-1] = x->key[i];

            x->n--;
        }
        else {
            if (x->child[idx]->n >= T) {
                int pred = predecessor(x->child[idx]);
                x->key[idx] = pred;
                deleteNode(x->child[idx], pred);
            }
            else if (x->child[idx+1]->n >= T) {
                int succ = successor(x->child[idx+1]);
                x->key[idx] = succ;
                deleteNode(x->child[idx+1], succ);
            }
            else {
                merge(x, idx);
                deleteNode(x->child[idx], key);
            }
        }
    }
    else {
        if (x->leaf)
            return;

        int flag = (idx == x->n);

        if (x->child[idx]->n < T)
            fill(x, idx);

        if (flag && idx > x->n)
            deleteNode(x->child[idx-1], key);
        else
            deleteNode(x->child[idx], key);
    }
}

// Delete item
Node* deleteItem(Node *root, int key) {
    if (root == NULL)
        return NULL;

    deleteNode(root, key);

    if (root->n == 0) {
        Node *temp = root;

        if (root->leaf)
            root = NULL;
        else
            root = root->child[0];

        free(temp);
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

// Display tree
void display(Node *root) {
    if (root == NULL)
        return;

    int i;

    for (i = 0; i < root->n; i++) {
        if (!root->leaf)
            display(root->child[i]);

        printf("%d ", root->key[i]);
    }

    if (!root->leaf)
        display(root->child[i]);
}

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

    printf("B-Tree: ");
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
