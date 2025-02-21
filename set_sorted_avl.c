#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
    int height;
};

// Function to get the height of the tree
int height(struct Node* node) {
    if (node == NULL) return 0;
    return node->height;
}

// Function to get the maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Function to create a new node
struct Node* newNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = node->right = NULL;
    node->height = 1;
    return node;
}

// Right rotate subtree rooted with y
struct Node* rightRotate(struct Node* y) {
    struct Node* x = y->left;
    struct Node* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    // Return the new root
    return x;
}

// Left rotate subtree rooted with x
struct Node* leftRotate(struct Node* x) {
    struct Node* y = x->right;
    struct Node* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    // Return the new root
    return y;
}

// Get the balance factor of a node
int getBalance(struct Node* node) {
    if (node == NULL) return 0;
    return height(node->left) - height(node->right);
}

// Function to insert a node into the AVL tree (Set)
struct Node* insert(struct Node* node, int data) {
    // Step 1: Perform the normal BST insert
    if (node == NULL) return newNode(data);

    if (data < node->data) {
        node->left = insert(node->left, data);
    } else if (data > node->data) {
        node->right = insert(node->right, data);
    } else {
        return node; // No duplicates allowed in a set
    }

    // Step 2: Update the height of this ancestor node
    node->height = 1 + max(height(node->left), height(node->right));

    // Step 3: Get the balance factor and perform rotations if necessary
    int balance = getBalance(node);

    // Left Left case
    if (balance > 1 && data < node->left->data)
        return rightRotate(node);

    // Right Right case
    if (balance < -1 && data > node->right->data)
        return leftRotate(node);

    // Left Right case
    if (balance > 1 && data > node->left->data) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left case
    if (balance < -1 && data < node->right->data) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    // Return the (unchanged) node pointer
    return node;
}

// Function to perform an in-order traversal of the AVL tree (Set)
void inOrder(struct Node* root) {
    if (root != NULL) {
        inOrder(root->left);
        printf("%d ", root->data);
        inOrder(root->right);
    }
}

// Function to search an element in the AVL tree (Set)
int search(struct Node* root, int data) {
    if (root == NULL) return 0; // Not found
    if (root->data == data) return 1; // Found
    if (data < root->data) return search(root->left, data);
    return search(root->right, data);
}

// Driver code
int main() {
    struct Node* root = NULL;

    // Insert elements into the Set (AVL Tree)
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 15);
    root = insert(root, 25);

    // Print the Set elements (in-order traversal)
    printf("Set elements (in-order): ");
    inOrder(root);
    printf("\n");

    // Search for an element
    int searchElement = 15;
    if (search(root, searchElement)) {
        printf("%d is present in the set.\n", searchElement);
    } else {
        printf("%d is not present in the set.\n", searchElement);
    }

    // Try inserting a duplicate element
    root = insert(root, 15);
    printf("Set elements after attempting to insert duplicate 15: ");
    inOrder(root);
    printf("\n");

    return 0;
}
