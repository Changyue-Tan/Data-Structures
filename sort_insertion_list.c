#include <stdio.h>
#include <stdlib.h>

// Define the structure for a linked list node
struct Node {
    int data;
    struct Node* next;
};

// Forward declaration of insertSorted function
void insertSorted(struct Node** sorted_ref, struct Node* new_node);

// Function to insert a new node at the beginning of the list
void push(struct Node** head_ref, int new_data) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->data = new_data;
    new_node->next = (*head_ref);
    (*head_ref) = new_node;
}

// Function to perform insertion sort on the linked list
void insertionSort(struct Node** head_ref) {
    struct Node *sorted = NULL; // Initialize sorted list
    struct Node *current = *head_ref; // Start from the head of the unsorted list

    // Traverse the given list and insert nodes in the sorted list
    while (current != NULL) {
        struct Node *next = current->next; // Store the next node
        // Insert current node in the sorted list
        insertSorted(&sorted, current);
        current = next; // Move to the next node
    }

    // Make the head of the sorted list the head of the original list
    *head_ref = sorted;
}

// Function to insert a node in the sorted linked list
void insertSorted(struct Node** sorted_ref, struct Node* new_node) {
    struct Node* current;
    // If the sorted list is empty or the new node should be inserted at the beginning
    if (*sorted_ref == NULL || (*sorted_ref)->data >= new_node->data) {
        new_node->next = *sorted_ref;
        *sorted_ref = new_node;
    } else {
        // Find the node before the point where the new node should be inserted
        current = *sorted_ref;
        while (current->next != NULL && current->next->data < new_node->data) {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }
}

// Function to print the linked list
void printList(struct Node* node) {
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}

// Driver code
int main() {
    struct Node* head = NULL;

    // Insert elements into the linked list
    push(&head, 12);
    push(&head, 11);
    push(&head, 13);
    push(&head, 5);
    push(&head, 6);

    printf("Original Linked List: \n");
    printList(head);

    // Perform insertion sort on the linked list
    insertionSort(&head);

    printf("Sorted Linked List: \n");
    printList(head);

    return 0;
}
