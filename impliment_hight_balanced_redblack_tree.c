
#include <stdio.h>
#include <stdlib.h>

#define RED 1
#define BLACK 0

struct Node {
    int data;
    int color;
    struct Node *left, *right, *parent;
};

typedef struct Node Node;

Node *root = NULL;

// Create a new node
Node* createNode(int key) {
    Node *newNode = malloc(sizeof(Node));

    newNode->data = key;
    newNode->color = RED;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->parent = NULL;

    return newNode;
}

// Create an empty tree
void createTree() {
    root = NULL;
}

// Left rotation
void leftRotate(Node *x) {
    Node *y = x->right;

    x->right = y->left;

    if (y->left != NULL)
        y->left->parent = x;

    y->parent = x->parent;

    if (x->parent == NULL)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
}

// Right rotation
void rightRotate(Node *y) {
    Node *x = y->left;

    y->left = x->right;

    if (x->right != NULL)
        x->right->parent = y;

    x->parent = y->parent;

    if (y->parent == NULL)
        root = x;
    else if (y == y->parent->right)
        y->parent->right = x;
    else
        y->parent->left = x;

    x->right = y;
    y->parent = x;
}

// Fix insertion
void insertFix(Node *z) {
    while (z != root && z->parent->color == RED) {

        Node *p = z->parent;
        Node *g = p->parent;

        if (p == g->left) {
            Node *u = g->right;

            if (u != NULL && u->color == RED) {
                p->color = BLACK;
                u->color = BLACK;
                g->color = RED;
                z = g;
            }
            else {
                if (z == p->right) {
                    z = p;
                    leftRotate(z);
                }

                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(z->parent->parent);
            }
        }
        else {
            Node *u = g->left;

            if (u != NULL && u->color == RED) {
                p->color = BLACK;
                u->color = BLACK;
                g->color = RED;
                z = g;
            }
            else {
                if (z == p->left) {
                    z = p;
                    rightRotate(z);
                }

                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(z->parent->parent);
            }
        }
    }

    root->color = BLACK;
}

// Insert item
void insertItem(int key) {
    Node *z = createNode(key);
    Node *y = NULL;
    Node *x = root;

    while (x != NULL) {
        y = x;

        if (key < x->data)
            x = x->left;
        else if (key > x->data)
            x = x->right;
        else {
            free(z);
            return;
        }
    }

    z->parent = y;

    if (y == NULL)
        root = z;
    else if (key < y->data)
        y->left = z;
    else
        y->right = z;

    insertFix(z);
}

// Search item
Node* searchItem(int key) {
    Node *temp = root;

    while (temp != NULL) {
        if (temp->data == key)
            return temp;

        if (key < temp->data)
            temp = temp->left;
        else
            temp = temp->right;
    }

    return NULL;
}

// Find minimum node
Node* minimum(Node *x) {
    while (x->left != NULL)
        x = x->left;

    return x;
}

// Replace one subtree with another
void transplant(Node *u, Node *v) {
    if (u->parent == NULL)
        root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;

    if (v != NULL)
        v->parent = u->parent;
}

// Fix deletion
void deleteFix(Node *x, Node *parent) {
    while (x != root && (x == NULL || x->color == BLACK)) {

        if (parent == NULL)
            break;

        if (x == parent->left) {
            Node *w = parent->right;

            if (w == NULL) {
                x = parent;
                parent = x->parent;
                continue;
            }

            if (w->color == RED) {
                w->color = BLACK;
                parent->color = RED;
                leftRotate(parent);
                w = parent->right;
            }

            if ((w->left == NULL || w->left->color == BLACK) &&
                (w->right == NULL || w->right->color == BLACK)) {

                w->color = RED;
                x = parent;
                parent = x->parent;
            }
            else {
                if (w->right == NULL || w->right->color == BLACK) {
                    if (w->left != NULL)
                        w->left->color = BLACK;

                    w->color = RED;
                    rightRotate(w);
                    w = parent->right;
                }

                w->color = parent->color;
                parent->color = BLACK;

                if (w->right != NULL)
                    w->right->color = BLACK;

                leftRotate(parent);
                x = root;
                parent = NULL;
            }
        }
        else {
            Node *w = parent->left;

            if (w == NULL) {
                x = parent;
                parent = x->parent;
                continue;
            }

            if (w->color == RED) {
                w->color = BLACK;
                parent->color = RED;
                rightRotate(parent);
                w = parent->left;
            }

            if ((w->right == NULL || w->right->color == BLACK) &&
                (w->left == NULL || w->left->color == BLACK)) {

                w->color = RED;
                x = parent;
                parent = x->parent;
            }
            else {
                if (w->left == NULL || w->left->color == BLACK) {
                    if (w->right != NULL)
                        w->right->color = BLACK;

                    w->color = RED;
                    leftRotate(w);
                    w = parent->left;
                }

                w->color = parent->color;
                parent->color = BLACK;

                if (w->left != NULL)
                    w->left->color = BLACK;

                rightRotate(parent);
                x = root;
                parent = NULL;
            }
        }
    }

    if (x != NULL)
        x->color = BLACK;
}

// Delete item
void deleteItem(int key) {
    Node *z = searchItem(key);

    if (z == NULL)
        return;

    Node *y = z;
    Node *x;
    Node *xParent;
    int originalColor = y->color;

    if (z->left == NULL) {
        x = z->right;
        xParent = z->parent;
        transplant(z, z->right);
    }
    else if (z->right == NULL) {
        x = z->left;
        xParent = z->parent;
        transplant(z, z->left);
    }
    else {
        y = minimum(z->right);
        originalColor = y->color;
        x = y->right;

        if (y->parent == z) {
            xParent = y;
            if (x != NULL)
                x->parent = y;
        }
        else {
            xParent = y->parent;
            transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }

        transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    free(z);

    if (originalColor == BLACK)
        deleteFix(x, x != NULL ? x->parent : xParent);
}

// Delete entire tree
void deleteTree(Node *temp) {
    if (temp == NULL)
        return;

    deleteTree(temp->left);
    deleteTree(temp->right);

    free(temp);
}

// Inorder traversal
void inorder(Node *temp) {
    if (temp == NULL)
        return;

    inorder(temp->left);

    printf("%d(%s) ", temp->data,
           temp->color == RED ? "R" : "B");

    inorder(temp->right);
}

int main() {
    createTree();

    insertItem(10);
    insertItem(20);
    insertItem(30);
    insertItem(15);
    insertItem(25);

    printf("Inorder: ");
    inorder(root);

    if (searchItem(20) != NULL)
        printf("\n20 Found");
    else
        printf("\n20 Not Found");

    deleteItem(20);

    printf("\nAfter deletion: ");
    inorder(root);

    deleteTree(root);
    root = NULL;

    return 0;
}
