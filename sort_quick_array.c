#include <stdio.h>

// Function to swap two elements
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function to partition the array and return the pivot index
int partition(int arr[], int low, int high) {
    int pivot = arr[high];  // Pivot element
    int i = (low - 1);  // Index of smaller element

    // Traverse through all elements of the array
    // Compare each element with the pivot
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;    // Increment the index of smaller element
            swap(&arr[i], &arr[j]);
        }
    }

    // Swap the pivot element with the element at i + 1
    swap(&arr[i + 1], &arr[high]);

    // Return the partition index
    return (i + 1);
}

// Recursive function to sort the array using Quick Sort
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        // Find pivot index such that elements smaller than the pivot are on the left
        // and elements greater than the pivot are on the right
        int pi = partition(arr, low, high);

        // Recursively sort the left and right sub-arrays
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Function to print the array
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Driver code
int main() {
    int arr[] = {10, 7, 8, 9, 1, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Unsorted array: \n");
    printArray(arr, n);

    // Call quickSort function
    quickSort(arr, 0, n - 1);

    printf("\nSorted array: \n");
    printArray(arr, n);

    return 0;
}
