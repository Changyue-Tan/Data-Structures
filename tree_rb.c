#include <stdio.h>
#include <stdlib.h>

#define RED   0
#define BLACK 1

// Structure for Red-Black Tree Node
typedef struct Node {
    int data;
    int color;
    struct Node *left, *right, *parent;
} Node;

Node *root = NULL;

// Function to create a new node
Node *createNode(int data) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->color = RED;  // New node is always RED
    newNode->left = newNode->right = newNode->parent = NULL;
    return newNode;
}

// Left rotation
void leftRotate(Node *x) {
    Node *y = x->right;
    x->right = y->left;
    
    if (y->left != NULL) {
        y->left->parent = x;
    }
    
    y->parent = x->parent;
    
    if (x->parent == NULL) {
        root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    
    y->left = x;
    x->parent = y;
}

// Right rotation
void rightRotate(Node *x) {
    Node *y = x->left;
    x->left = y->right;
    
    if (y->right != NULL) {
        y->right->parent = x;
    }
    
    y->parent = x->parent;
    
    if (x->parent == NULL) {
        root = y;
    } else if (x == x->parent->right) {
        x->parent->right = y;
    } else {
        x->parent->left = y;
    }
    
    y->right = x;
    x->parent = y;
}

// Fix violation after insertion
void fixViolation(Node *z) {
    Node *uncle;
    
    while (z != root && z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            uncle = z->parent->parent->right;
            
            // Case 1: Uncle is red
            if (uncle != NULL && uncle->color == RED) {
                z->parent->color = BLACK;
                uncle->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                // Case 2: z is right child
                if (z == z->parent->right) {
                    z = z->parent;
                    leftRotate(z);
                }
                // Case 3: z is left child
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(z->parent->parent);
            }
        } else {
            uncle = z->parent->parent->left;
            
            // Case 1: Uncle is red
            if (uncle != NULL && uncle->color == RED) {
                z->parent->color = BLACK;
                uncle->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                // Case 2: z is left child
                if (z == z->parent->left) {
                    z = z->parent;
                    rightRotate(z);
                }
                // Case 3: z is right child
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(z->parent->parent);
            }
        }
    }
    
    root->color = BLACK;
}

// Insertion function
void insert(int data) {
    Node *z = createNode(data);
    Node *y = NULL;
    Node *x = root;
    
    // Binary search tree insertion
    while (x != NULL) {
        y = x;
        if (z->data < x->data) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    
    z->parent = y;
    
    if (y == NULL) {
        root = z;
    } else if (z->data < y->data) {
        y->left = z;
    } else {
        y->right = z;
    }
    
    // Fix violations of red-black tree properties
    fixViolation(z);
}

// In-order traversal to print tree nodes
void inorderTraversal(Node *node) {
    if (node == NULL) {
        return;
    }
    inorderTraversal(node->left);
    printf("%d ", node->data);
    inorderTraversal(node->right);
}

// Driver function
int main() {
    // Insert nodes
    insert(20);
    insert(15);
    insert(25);
    insert(10);
    insert(5);
    insert(30);
    
    // Print in-order traversal of the Red-Black Tree
    printf("In-order traversal: ");
    inorderTraversal(root);
    printf("\n");
    
    return 0;
}
