#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 10 // Size of the hash table

// Node structure for linked list (used for chaining)
struct Node {
    int data;
    struct Node* next;
};

// Hash table structure
struct HashTable {
    struct Node* table[TABLE_SIZE]; // Array of pointers to linked lists (buckets)
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Hash function to calculate index based on key (data)
int hash(int key) {
    return key % TABLE_SIZE;
}

// Function to initialize the hash table
struct HashTable* createHashTable() {
    struct HashTable* hashTable = (struct HashTable*)malloc(sizeof(struct HashTable));
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable->table[i] = NULL;
    }
    return hashTable;
}

// Function to insert an element into the unordered set
void insert(struct HashTable* hashTable, int data) {
    int index = hash(data); // Calculate the index for the data
    struct Node* head = hashTable->table[index];

    // Check if the data is already present in the list (no duplicates allowed)
    struct Node* current = head;
    while (current != NULL) {
        if (current->data == data) {
            printf("Element %d already exists in the set.\n", data);
            return; // Data is already in the set
        }
        current = current->next;
    }

    // Create a new node and insert it at the head of the linked list
    struct Node* newNode = createNode(data);
    newNode->next = head;
    hashTable->table[index] = newNode;
    printf("Inserted %d into the set.\n", data);
}

// Function to check if an element exists in the unordered set
int search(struct HashTable* hashTable, int data) {
    int index = hash(data); // Calculate the index for the data
    struct Node* current = hashTable->table[index];

    while (current != NULL) {
        if (current->data == data) {
            return 1; // Element found
        }
        current = current->next;
    }

    return 0; // Element not found
}

// Function to remove an element from the unordered set
void removeElement(struct HashTable* hashTable, int data) {
    int index = hash(data); // Calculate the index for the data
    struct Node* current = hashTable->table[index];
    struct Node* prev = NULL;

    // Traverse the linked list and find the element
    while (current != NULL) {
        if (current->data == data) {
            // Element found, remove it
            if (prev == NULL) { // The element is at the head of the list
                hashTable->table[index] = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            printf("Removed %d from the set.\n", data);
            return;
        }
        prev = current;
        current = current->next;
    }

    printf("Element %d not found in the set.\n", data);
}

// Function to print the unordered set (hash table)
void printHashTable(struct HashTable* hashTable) {
    printf("Hash Table:\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        struct Node* current = hashTable->table[i];
        if (current == NULL) {
            printf("Bucket %d: Empty\n", i);
        } else {
            printf("Bucket %d: ", i);
            while (current != NULL) {
                printf("%d -> ", current->data);
                current = current->next;
            }
            printf("NULL\n");
        }
    }
}

// Driver code to test the unordered set implementation
int main() {
    struct HashTable* hashTable = createHashTable();

    // Insert elements into the unordered set
    insert(hashTable, 10);
    insert(hashTable, 10);
    insert(hashTable, 33);
    insert(hashTable, 22);
    insert(hashTable, 44);

    // Print the hash table
    printHashTable(hashTable);

    // Search for an element
    int searchElement = 25;
    if (search(hashTable, searchElement)) {
        printf("%d is present in the set.\n", searchElement);
    } else {
        printf("%d is not present in the set.\n", searchElement);
    }

    // Try removing an element
    removeElement(hashTable, 20);

    // Print the hash table after removal
    printHashTable(hashTable);

    // Try removing a non-existing element
    removeElement(hashTable, 40);

    return 0;
}
