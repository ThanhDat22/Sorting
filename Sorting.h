#ifndef SORTING_H
#define SORTING_H

#include "Vector.h"

#include <random>
#include <stdexcept>

using namespace std;

template<class T>
class Sorting {
public:
    // Member functions
    static void swap(T&, T&);
    static Vector<T> generate_vector(size_t, T, T);

    static void selection_sort(Vector<T>&);
    static void bubble_sort(Vector<T>&);
    static void insertion_sort(Vector<T>&);
    static void shell_sort(Vector<T>&);
    static void merge_sort(Vector<T>&);
    static void quick_sort(Vector<T>&);
    static void heap_sort(Vector<T>&);
    static void counting_sort(Vector<T>&);
    static void radix_sort(Vector<T>&);
    static void bucket_sort(Vector<T>&);
    static void tim_sort(Vector<T>&);
    static void intro_sort(Vector<T>&);
private:
    // Private helper functions
    static void merge(const Vector<T>&, Vector<T>&, Vector<T>&); // Helper function for merge sort

    static size_t lomuto_partition(Vector<T>&, size_t, size_t); // Helper function for quick sort Lomuto
    static void lomuto_quick_sort_recursive(Vector<T>&, size_t, size_t); // Helper function for quick sort Lomuto

    static size_t hoare_partition(Vector<T>&, size_t, size_t); // Helper function for quick sort Hoare
    static void hoare_quick_sort_recursive(Vector<T>&, size_t, size_t); // Helper function for quick sort Hoare

    static size_t median_of_three(Vector<T>&, size_t, size_t);
    static size_t hoare_partition_with_median(Vector<T>&, size_t, size_t); // Helper function for quick sort Hoare with median-of-three
    static void hoare_quick_sort_with_median_recursive(Vector<T>&, size_t, size_t); // Helper function for quick sort Hoare with median-of-three
    static void insertion_sort(Vector<T>&, size_t, size_t); // Insertion sort for a range of the vector

    static void max_heapify(Vector<T>&, size_t, size_t); // Moves the root downward to form a max heap
    static void build_max_heap(Vector<T>&, size_t); // Generates a max heap rooted at given index
    static void heap_sort(Vector<T>&, size_t); // Helper function for heap sort

    static void min(const Vector<T>&); // Finds the minimum value in the vector
    static void max(const Vector<T>&); // Finds the maximum value in the vector
    static void count_frequency(const Vector<T>&, T, T); // Counts the frequency of each element in the vector
    
    static void counting_sort_by_digit(Vector<T>&, size_t); // Sorts the vector based on a specific digit

};

#endif // SORTING_H