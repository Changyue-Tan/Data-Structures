#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_SIZE 100

// Structure for a min-heap priority queue
typedef struct {
    int data[MAX_SIZE];  // Array to store heap elements
    int size;            // Current number of elements in the heap
} PriorityQueue;

// Function to initialize a priority queue
void initQueue(PriorityQueue* pq) {
    pq->size = 0;
}

// Function to get the parent index of a node
int parent(int i) {
    return (i - 1) / 2;
}

// Function to get the left child index of a node
int leftChild(int i) {
    return 2 * i + 1;
}

// Function to get the right child index of a node
int rightChild(int i) {
    return 2 * i + 2;
}

// Function to heapify a subtree rooted at index i
void heapify(PriorityQueue* pq, int i) {
    int smallest = i;
    int left = leftChild(i);
    int right = rightChild(i);

    if (left < pq->size && pq->data[left] < pq->data[smallest]) {
        smallest = left;
    }

    if (right < pq->size && pq->data[right] < pq->data[smallest]) {
        smallest = right;
    }

    if (smallest != i) {
        // Swap pq->data[i] and pq->data[smallest]
        int temp = pq->data[i];
        pq->data[i] = pq->data[smallest];
        pq->data[smallest] = temp;

        // Recursively heapify the affected subtree
        heapify(pq, smallest);
    }
}

// Function to insert an element into the priority queue
void insert(PriorityQueue* pq, int value) {
    if (pq->size >= MAX_SIZE) {
        printf("Queue is full!\n");
        return;
    }

    // Insert the new element at the end of the heap
    pq->data[pq->size] = value;
    pq->size++;

    // Fix the min-heap property if it's violated
    int i = pq->size - 1;
    while (i > 0 && pq->data[parent(i)] > pq->data[i]) {
        // Swap pq->data[i] and pq->data[parent(i)]
        int temp = pq->data[i];
        pq->data[i] = pq->data[parent(i)];
        pq->data[parent(i)] = temp;

        i = parent(i);
    }
}

// Function to extract the minimum (root) from the priority queue
int extractMin(PriorityQueue* pq) {
    if (pq->size <= 0) {
        printf("Queue is empty!\n");
        return INT_MAX;
    }

    // The root of the heap contains the minimum element
    int root = pq->data[0];

    // Replace the root with the last element in the heap
    pq->data[0] = pq->data[pq->size - 1];
    pq->size--;

    // Heapify the root element to maintain the min-heap property
    heapify(pq, 0);

    return root;
}

// Function to get the minimum element (root) without extracting it
int getMin(PriorityQueue* pq) {
    if (pq->size <= 0) {
        printf("Queue is empty!\n");
        return INT_MAX;
    }
    return pq->data[0];
}

// Function to print the elements of the priority queue (heap array)
void printQueue(PriorityQueue* pq) {
    for (int i = 0; i < pq->size; i++) {
        printf("%d ", pq->data[i]);
    }
    printf("\n");
}

int main() {
    PriorityQueue pq;
    initQueue(&pq);

    // Insert some elements into the priority queue
    insert(&pq, 10);
    insert(&pq, 20);
    insert(&pq, 15);
    insert(&pq, 30);
    insert(&pq, 5);

    printf("Priority Queue (Min-Heap) after insertions:\n");
    printQueue(&pq);

    // Extract the minimum element
    printf("\nExtracting minimum: %d\n", extractMin(&pq));

    printf("Priority Queue after extracting min:\n");
    printQueue(&pq);

    // Get the minimum element without extracting it
    printf("\nCurrent minimum: %d\n", getMin(&pq));

    return 0;
}
