#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

// Define the heap structure
struct MinHeap {
    int arr[MAX_SIZE];
    int size;
};

// Function to swap two elements
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function to heapify the tree
void heapify(struct MinHeap *heap, int index) {
    int smallest = index;  // Initialize smallest as root
    int left = 2 * index + 1; // Left child index
    int right = 2 * index + 2; // Right child index

    // Check if left child exists and is smaller than root
    if (left < heap->size && heap->arr[left] < heap->arr[smallest]) {
        smallest = left;
    }

    // Check if right child exists and is smaller than root
    if (right < heap->size && heap->arr[right] < heap->arr[smallest]) {
        smallest = right;
    }

    // If smallest is not root, swap and heapify
    if (smallest != index) {
        swap(&heap->arr[index], &heap->arr[smallest]);
        heapify(heap, smallest);
    }
}

// Function to insert an element into the heap
void insert(struct MinHeap *heap, int value) {
    if (heap->size == MAX_SIZE) {
        printf("Heap is full.\n");
        return;
    }

    // First, insert the new element at the end
    heap->arr[heap->size] = value;
    heap->size++;

    // Fix the heap property if it's violated
    int index = heap->size - 1;
    while (index > 0 && heap->arr[index] < heap->arr[(index - 1) / 2]) {
        swap(&heap->arr[index], &heap->arr[(index - 1) / 2]);
        index = (index - 1) / 2;
    }
}

// Function to remove the root element (extract the minimum element)
int extractMin(struct MinHeap *heap) {
    if (heap->size <= 0) {
        printf("Heap is empty.\n");
        return -1;
    }
    if (heap->size == 1) {
        heap->size--;
        return heap->arr[0];
    }

    // Store the minimum value, and remove the root
    int root = heap->arr[0];
    heap->arr[0] = heap->arr[heap->size - 1];
    heap->size--;

    // Heapify the root to maintain the heap property
    heapify(heap, 0);

    return root;
}

// Function to get the minimum element (root)
int getMin(struct MinHeap *heap) {
    if (heap->size <= 0) {
        printf("Heap is empty.\n");
        return -1;
    }
    return heap->arr[0];
}

// Function to print the heap array
void printHeap(struct MinHeap *heap) {
    for (int i = 0; i < heap->size; i++) {
        printf("%d ", heap->arr[i]);
    }
    printf("\n");
}

int main() {
    struct MinHeap heap;
    heap.size = 0;

    // Insert elements into the heap
    insert(&heap, 3);
    insert(&heap, 1);
    insert(&heap, 15);
    insert(&heap, 5);
    insert(&heap, 2);
    insert(&heap, 4);

    printf("Heap elements after insertion: ");
    printHeap(&heap);

    // Extract the minimum element
    printf("Extracted min: %d\n", extractMin(&heap));
    printf("Heap elements after extraction: ");
    printHeap(&heap);

    // Get the minimum element without removing it
    printf("Current min: %d\n", getMin(&heap));

    return 0;
}
