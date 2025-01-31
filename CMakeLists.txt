cmake_minimum_required(VERSION 3.29)
project(ID1021_Searching C)

set(CMAKE_C_STANDARD 11)

add_executable(ID1021_Searching
        unsorted_search.c
        sorted_search.c
        nonbinary_sorted_search.c
        unsorted_binary.c
        sorted_search_64.c)
