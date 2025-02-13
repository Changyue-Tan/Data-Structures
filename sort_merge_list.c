#include <stdio.h>
#include <stdlib.h>

// Define the structure for a node in the linked list
struct Node {
    int data;
    struct Node* next;
};

// Function to split the linked list into two halves
void split(struct Node* head, struct Node** front, struct Node** back) {
    struct Node* fast;
    struct Node* slow;

    if (head == NULL || head->next == NULL) {
        *front = head;
        *back = NULL;
        return;
    }

    slow = head;
    fast = head->next;

    // Move fast by 2 and slow by 1
    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            fast = fast->next;
            slow = slow->next;
        }
    }

    *front = head;
    *back = slow->next;
    slow->next = NULL;
}

// Function to merge two sorted linked lists
struct Node* merge(struct Node* left, struct Node* right) {
    if (left == NULL) return right;
    if (right == NULL) return left;

    if (left->data < right->data) {
        left->next = merge(left->next, right);
        return left;
    } else {
        right->next = merge(left, right->next);
        return right;
    }
}

// Function to perform merge sort on the linked list
struct Node* mergeSort(struct Node* head) {
    if (head == NULL || head->next == NULL) {
        return head;
    }

    struct Node* left;
    struct Node* right;

    // Split the list into two halves
    split(head, &left, &right);

    // Recursively sort each half
    left = mergeSort(left);
    right = mergeSort(right);

    // Merge the two sorted halves
    return merge(left, right);
}

// Helper function to push a new node to the front of the list
void push(struct Node** head_ref, int new_data) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->data = new_data;
    new_node->next = (*head_ref);
    (*head_ref) = new_node;
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
    struct Node* list = NULL;

    // Creating an unsorted linked list
    push(&list, 15);
    push(&list, 10);
    push(&list, 5);
    push(&list, 20);
    push(&list, 25);
    push(&list, 30);
    push(&list, 40);

    printf("Given linked list: \n");
    printList(list);

    // Perform merge sort on the linked list
    list = mergeSort(list);

    printf("\nSorted linked list: \n");
    printList(list);

    return 0;
}
