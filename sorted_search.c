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

// Binary search for sorted arrays
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

void benchmark_search_to_file(const char* file_name, int max_array_size, int step_size, int key) {
    FILE* file = fopen(file_name, "w");
    if (file == NULL) {
        fprintf(stderr, "Error: Unable to open file '%s' for writing.\n", file_name);
        return;
    }

    fprintf(file, "# Array Size\tTime Taken (microseconds)\n");

    for (int array_size = step_size; array_size <= max_array_size; array_size += step_size) {
        int* array = sorted_array(array_size);  // Generate a sorted array
        if (array == NULL) {
            fprintf(stderr, "Memory allocation failed at size %d\n", array_size);
            break;
        }

        clock_t start_time = clock();
        sorted_search(array, array_size, key);  // Perform sorted search
        clock_t end_time = clock();

        // Convert time to microseconds
        double time_taken = (double)(end_time - start_time) * 1000000 / CLOCKS_PER_SEC;

        fprintf(file, "%d\t%.2f\n", array_size, time_taken);
        free(array);  // Free the allocated memory
    }

    fclose(file);
}

int main() {
    const char* output_file = "sorted_search_results";  // Save results to this file
    int max_array_size = 1000000;  // Maximum array size (1 million elements)
    int step_size = 10000;         // Increment: analyze every 10,000 elements
    int key = -1;                  // Use a key that won't be found (worst-case scenario)

    srand((unsigned int)time(NULL));  // Seed the random number generator

    benchmark_search_to_file(output_file, max_array_size, step_size, key);

    printf("Benchmark results saved to '%s'.\n", output_file);

    return 0;
}