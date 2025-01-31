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

// Benchmark function: Measure search time and save results to a file
void benchmark_search_to_file(const char* file_name, int max_array_size, int step_size) {
    FILE* file = fopen(file_name, "w");
    if (file == NULL) {
        fprintf(stderr, "Error: Unable to open file '%s' for writing.\n", file_name);
        return;
    }

    fprintf(file, "# Array Size\tTime Taken (milliseconds)\tKey Type\n");

    int repetitions = 1000;  // Repeat the search multiple times for accuracy

    for (int array_size = step_size; array_size <= max_array_size; array_size += step_size) {
        int* array = sorted_array(array_size);  // Generate a sorted array
        if (array == NULL) {
            fprintf(stderr, "Memory allocation failed at size %d\n", array_size);
            break;
        }

        // Test case 1: Search for a "hit" key (middle element of the array)
        int key_hit = array[array_size / 2];
        clock_t start_time_hit = clock();
        for (int i = 0; i < repetitions; i++) {
            sorted_search(array, array_size, key_hit);
        }
        clock_t end_time_hit = clock();
        double time_taken_hit = (double)(end_time_hit - start_time_hit) * 1000 / (CLOCKS_PER_SEC * repetitions);

        // Test case 2: Search for a "miss" key (greater than the largest value)
        int key_miss = array[array_size - 1] + 10;
        clock_t start_time_miss = clock();
        for (int i = 0; i < repetitions; i++) {
            sorted_search(array, array_size, key_miss);
        }
        clock_t end_time_miss = clock();
        double time_taken_miss = (double)(end_time_miss - start_time_miss) * 1000 / (CLOCKS_PER_SEC * repetitions);

        // Write results for both "hit" and "miss" cases
        fprintf(file, "%d\t%.2f\tHit\n", array_size, time_taken_hit);
        fprintf(file, "%d\t%.2f\tMiss\n", array_size, time_taken_miss);

        free(array);  // Free the allocated memory
    }

    fclose(file);
}

int main() {
    const char* output_file = "sorted_search_results";  // Save results to this file
    int max_array_size = 1000000;  // Maximum array size (1 million elements)
    int step_size = 10000;         // Increment: analyze every 10,000 elements

    srand((unsigned int)time(NULL));  // Seed the random number generator

    benchmark_search_to_file(output_file, max_array_size, step_size);

    printf("Benchmark results saved to '%s'.\n", output_file);

    return 0;
}