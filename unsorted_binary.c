#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

// clang unsorted_search.c -o unsorted_search

bool unsorted_search(int array[], int length, int key) {
    for (int index = 0; index < length; index++) {
        if (array[index] == key) {
            return true;
        }
    }
    return false;
}

void benchmark_search_to_file(const char* file_name, int max_array_size, int step_size, int key) {
    FILE *file = fopen(file_name, "w");
    if (file == NULL) {
        fprintf(stderr, "Error: Unable to open file '%s' for writing.\n", file_name);
        return;
    }

    fprintf(file, "# Array Size\tTime Taken (microseconds)\n");

    for (int array_size = step_size; array_size <= max_array_size; array_size += step_size) {
        int* array = (int*)malloc(array_size * sizeof(int));
        if (array == NULL) {
            fprintf(stderr, "Memory allocation failed at size %d\n", array_size);
            break;
        }

        for (int i = 0; i < array_size; i++) {
            array[i] = i;
        }

        clock_t start_time = clock();
        unsorted_search(array, array_size, key);
        clock_t end_time = clock();

        // Convert time to microseconds
        double time_taken = (double)(end_time - start_time) * 1000000 / CLOCKS_PER_SEC;

        fprintf(file, "%d\t%.2f\n", array_size, time_taken);
        free(array);
    }

    fclose(file);
}

int main() {
    const char* output_file = "unsorted_search_results";  // Save results to this file
    int max_array_size = 1000000;  // Maximum array size (1 million elements)
    int step_size = 10000;         // Increment: analyze every 10,000 elements
    int key = -1;                  // Use a key that won't be found (worst-case scenario)

    benchmark_search_to_file(output_file, max_array_size, step_size, key);

    printf("Benchmark results saved to '%s'.\n", output_file);

    return 0;
}