#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

// Function to generate a sorted array of size 'n'
int* sorted_array(int n) {
    int *array = (int*)malloc(n * sizeof(int));
    if (array == NULL) {
        fprintf(stderr, "Memory allocation failed for array size %d.\n", n);
        exit(EXIT_FAILURE);
    }
    int nxt = 0;
    for (int i = 0; i < n; i++) {
        nxt += rand() % 10 + 1;  // Increment by a random value between 1 and 10
        array[i] = nxt;
    }
    return array;
}

// Binary search function
bool sorted_search(int array[], int length, int key) {
    int low = 0, high = length - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;  // Prevent overflow
        if (array[mid] == key) {
            return true;
        }
        if (array[mid] < key) {
            low = mid + 1;  // Search the right side
        } else {
            high = mid - 1;  // Search the left side
        }
    }
    return false;  // Key not found
}

int main() {
    int array_size = 1000000;  // Array size of 64 million
    printf("Generating an array of size %d...\n", array_size);

    // Generate a sorted array of size 64 million
    srand((unsigned int)time(NULL));  // Seed the random number generator
    int* array = sorted_array(array_size);

    if (array == NULL) {
        fprintf(stderr, "Failed to allocate memory for the array.\n");
        return EXIT_FAILURE;
    }

    printf("Array generation completed. Starting binary search...\n");

    // Timing for a hit case (key exists)
    int key_hit = array[array_size / 2];  // Middle element (guaranteed to exist)
    clock_t start_time_hit = clock();
    bool hit_result = sorted_search(array, array_size, key_hit);
    clock_t end_time_hit = clock();
    double time_taken_hit = (double)(end_time_hit - start_time_hit) * 1000000000 / CLOCKS_PER_SEC;  // Convert to nanoseconds

    // Timing for a miss case (key does not exist)
    int key_miss = array[array_size - 1] + 10;  // Out-of-bounds value (guaranteed not to exist)
    clock_t start_time_miss = clock();
    bool miss_result = sorted_search(array, array_size, key_miss);
    clock_t end_time_miss = clock();
    double time_taken_miss = (double)(end_time_miss - start_time_miss) * 1000000000 / CLOCKS_PER_SEC;  // Convert to nanoseconds

    // Print results
    printf("Binary Search Completed.\n");
    printf("Hit Test: Key found? %s | Time Taken: %.2f nanoseconds\n", hit_result ? "Yes" : "No", time_taken_hit);
    printf("Miss Test: Key found? %s | Time Taken: %.2f nanoseconds\n", miss_result ? "Yes" : "No", time_taken_miss);

    // Free allocated memory
    free(array);

    return 0;
}