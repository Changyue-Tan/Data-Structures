#include <stdio.h>
#include <stdlib.h>

// Define a Node structure
struct Node {
    int data;
    struct Node* next;
};

// Function to create a new node
struct Node* newNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->next = NULL;
    return node;
}

// Function to print the linked list
void printList(struct Node* head) {
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// Function to swap two nodes in the linked list
void swap(struct Node* a, struct Node* b) {
    int temp = a->data;
    a->data = b->data;
    b->data = temp;
}

// Bubble Sort on linked list
void bubbleSort(struct Node* head) {
    if (head == NULL) return;  // Return if the list is empty

    struct Node *i, *j;
    int swapped;

    do {
        swapped = 0;
        i = head;

        // Traverse the list
        while (i != NULL && i->next != NULL) {
            j = i->next;
            if (i->data > j->data) {
                // Swap data if the current node's data is greater than the next node's data
                swap(i, j);
                swapped = 1;
            }
            i = i->next;
        }
    } while (swapped);  // Continue the loop if a swap was made
}

// Driver code
int main() {
    // Creating a sample linked list: 64 -> 34 -> 25 -> 12 -> 22 -> 11 -> 90
    struct Node* head = newNode(64);
    head->next = newNode(34);
    head->next->next = newNode(25);
    head->next->next->next = newNode(12);
    head->next->next->next->next = newNode(22);
    head->next->next->next->next->next = newNode(11);
    head->next->next->next->next->next->next = newNode(90);

    printf("Original Linked List: \n");
    printList(head);

    bubbleSort(head);

    printf("Sorted Linked List: \n");
    printList(head);

    return 0;
}
