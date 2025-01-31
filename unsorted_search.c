#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

// clang main.c -o main

bool unsorted_search(int array[], int length, int key) {
    for (int index = 0; index < length ; index++) {
        if (array[index] == key) {
            return true;
        }
    }
    return false;
}

void benchmark_search(int array_size, int key) {
    // Allocate array dynamically
    int* array = (int*)malloc(array_size * sizeof(int));
    if (array == NULL) {
        fprintf(stderr, "Memory allocation failed!\n");
        return;
    }

    // Fill the array with values from 0 to array_size - 1
    for (int i = 0; i < array_size; i++) {
        array[i] = i;
    }

    // Measure the time it takes to search
    clock_t start_time = clock(); // Start timer
    bool found = unsorted_search(array, array_size, key);
    clock_t end_time = clock(); // End timer

    // Calculate and print the time it took
    double time_taken = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("Array size: %d, Time taken: %.6f seconds, Key %s\n",
        array_size,
        time_taken,
        found ? "found" : "not found");

    // Free allocated memory
    free(array);
}

int main() {
    // Perform benchmark on arrays with increasing sizes
    int key = -1; // Use a key that won't be found to simulate worst-case scenario

    // Run benchmarks for different array sizes
    benchmark_search(1000, key);
    benchmark_search(10000, key);
    benchmark_search(100000, key);
    benchmark_search(1000000, key); // Benchmark for a million elements

    return 0;
}