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

// Linear search function
bool sorted_search_linear(int array[], int length, int key) {
    for (int i = 0; i < length; i++) {
        if (array[i] == key) {
            return true; // Found the key
        }
    }
    return false; // Key not found
}

// Benchmark function: Write hit and miss results to separate files
void benchmark_search_to_separate_files(const char* hit_file_name, const char* miss_file_name, int max_array_size, int step_size) {
    FILE* hit_file = fopen(hit_file_name, "w");
    FILE* miss_file = fopen(miss_file_name, "w");

    // Validate that both files were opened successfully
    if (hit_file == NULL || miss_file == NULL) {
        fprintf(stderr, "Error: Unable to open specified files for writing.\n");
        if (hit_file != NULL) fclose(hit_file);
        if (miss_file != NULL) fclose(miss_file);
        return;
    }

    // Write headers to the files
    fprintf(hit_file, "# Array Size\tTime Taken (microseconds) - Hit\n");
    fprintf(miss_file, "# Array Size\tTime Taken (microseconds) - Miss\n");

    printf("# Array Size\tHit Time (microseconds)\tMiss Time (microseconds)\n");

    int repetitions = 10;  // Repeat the search multiple times for better timing accuracy (reduce for large array sizes)

    // Perform the benchmark for all array sizes
    for (int array_size = step_size; array_size <= max_array_size; array_size += step_size) {
        int* array = sorted_array(array_size);  // Generate a sorted array
        if (array == NULL) {
            fprintf(stderr, "Memory allocation failed at size %d\n", array_size);
            break;
        }

        // Test 1: Search for a key that exists (hit)
        int key_hit = array[array_size / 2];  // Middle element
        clock_t start_time_hit = clock();
        for (int i = 0; i < repetitions; i++) {
            sorted_search_linear(array, array_size, key_hit);
        }
        clock_t end_time_hit = clock();
        double time_taken_hit = (double)(end_time_hit - start_time_hit) * 1000000 / (CLOCKS_PER_SEC * repetitions);

        // Test 2: Search for a key that does not exist (miss)
        int key_miss = array[array_size - 1] + 10;  // A value greater than the largest array element
        clock_t start_time_miss = clock();
        for (int i = 0; i < repetitions; i++) {
            sorted_search_linear(array, array_size, key_miss);
        }
        clock_t end_time_miss = clock();
        double time_taken_miss = (double)(end_time_miss - start_time_miss) * 1000000 / (CLOCKS_PER_SEC * repetitions);

        // Write hit result to the hit file
        fprintf(hit_file, "%d\t%.2f\n", array_size, time_taken_hit);

        // Write miss result to the miss file
        fprintf(miss_file, "%d\t%.2f\n", array_size, time_taken_miss);

        // Print results to the terminal
        printf("%d\t\t%.2f\t\t%.2f\n", array_size, time_taken_hit, time_taken_miss);

        // Free the allocated memory for the array
        free(array);
    }

    // Close the files after writing
    fclose(hit_file);
    fclose(miss_file);

    printf("Benchmark results saved to '%s' (hit cases) and '%s' (miss cases).\n", hit_file_name, miss_file_name);
}

int main() {
    const char* hit_file = "sorted_search_hit_linear.dat";   // File for hit case results
    const char* miss_file = "sorted_search_miss_linear.dat"; // File for miss case results
    int max_array_size = 1000000;  // Adjust as needed to prevent slow execution for large arrays
    int step_size = 1000;         // Increment array size by 1,000 elements

    srand((unsigned int)time(NULL));  // Seed the random number generator for array generation

    // Run the benchmark and save results to separate files
    benchmark_search_to_separate_files(hit_file, miss_file, max_array_size, step_size);

    return 0;
}