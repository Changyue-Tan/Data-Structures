#include <stdio.h>
#include <stdlib.h>

// Define the node structure for the doubly linked list
struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
};

// Function to create a new node
struct Node* newNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->prev = node->next = NULL;
    return node;
}

// Function to swap two nodes in the doubly linked list
void swapNodes(struct Node* a, struct Node* b) {
    // Swap data between nodes a and b
    int temp = a->data;
    a->data = b->data;
    b->data = temp;
}

// Partition function that takes the last element as pivot, places it in the correct position
// and places smaller elements on the left of the pivot and larger ones on the right
struct Node* partition(struct Node* low, struct Node* high) {
    int pivot = high->data;
    struct Node* i = low->prev;

    for (struct Node* j = low; j != high; j = j->next) {
        if (j->data <= pivot) {
            i = (i == NULL) ? low : i->next;
            swapNodes(i, j);
        }
    }
    i = (i == NULL) ? low : i->next;
    swapNodes(i, high);
    return i;
}

// QuickSort function to sort the doubly linked list
void quickSort(struct Node* low, struct Node* high) {
    if (low != NULL && high != NULL && low != high && low != high->next) {
        struct Node* p = partition(low, high);

        // Recursively sort the left and right partitions
        quickSort(low, p->prev);
        quickSort(p->next, high);
    }
}

// Function to print the list
void printList(struct Node* head) {
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// Helper function to find the last node of the list
struct Node* getLastNode(struct Node* head) {
    while (head != NULL && head->next != NULL) {
        head = head->next;
    }
    return head;
}

// Function to insert a new node at the end of the doubly linked list
void append(struct Node** head_ref, int new_data) {
    struct Node* new_node = newNode(new_data);
    struct Node* last = *head_ref;

    if (*head_ref == NULL) {
        *head_ref = new_node;
        return;
    }

    while (last->next != NULL) {
        last = last->next;
    }

    last->next = new_node;
    new_node->prev = last;
}

int main() {
    struct Node* head = NULL;

    // Insert elements into the doubly linked list
    append(&head, 10);
    append(&head, 80);
    append(&head, 30);
    append(&head, 90);
    append(&head, 40);
    append(&head, 50);
    append(&head, 70);

    printf("Original list: ");
    printList(head);

    // Get the last node of the list
    struct Node* last = getLastNode(head);

    // Perform Quick Sort
    quickSort(head, last);

    printf("Sorted list: ");
    printList(head);

    return 0;
}
