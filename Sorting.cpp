#include "Sorting.h"

/** Swaps two integers
    @param a: First integer to swap
    @param b: Second integer to swap
*/
void Sorting<T>::swap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
} // Time complexity: O(1), Space complexity: O(1)

/** Generates a vector of random integers
    @param size: The number of elements in the vector
    @param min: The minimum value of the random integers
    @param max: The maximum value of the random integers
    @return: A vector of random integers
*/
Vector<T> Sorting<T>::generate_vector(size_t size, T min, T max) {
    Vector<T> vector(size);
    if (min > max) {
        throw std::invalid_argument("Minimum value cannot be greater than maximum value.");
    }
    random_device rd; // Obtain a random number from hardware
    mt19937 generator(rd()); // Seed the generator
    uniform_int_distribution<> distribution(min, max); // Define the range

    // Clear existing elements in the vector
    while (!vector.empty()) {
        vector.pop_back();
    }

    // Generate random numbers and add them to the vector
    for (size_t i = 0; i < size; ++i) {
        vector.push_back(distribution(generator));
    }
    return vector;
} // Time complexity: O(n), Space complexity: O(n)


void Sorting<T>::bubble_sort(Vector<T>& vector) {
    for (size_t i = 0; i < vector.size(); ++i) {
        // Stores whether a swap occurs in this iteration
        bool swapped = false;

        for (size_t j = 1; j < vector.size() - i; ++j) {
            if (vector.at(j) < vector.at(j - 1)) {
                swap(vector.at(j), vector.at(j - 1));
                swapped = true;
            }
        }
        // If no swaps occurred, the vector is already sorted
        if (!swapped) { 
            return;
        }
    }
} // Time complexity: O(n^2), Space complexity: O(1)

void Sorting<T>::selection_sort(Vector<T>& vector) {
    for (size_t i = 0; i < vector.size(); ++i) {
        // Stores the index of the min value in the rest of the vector
        size_t min_index = i;

        // Finds the min value in the rest of the vector
        for (size_t j = i + 1; j < vector.size(); ++j) {
            if (vector.at(j) < vector.at(min_index)) {
                min_index = j;
            }
        }

        // Swaps vec.at(min) with vec.at(i) if they are not the same
        if (min_index != i) {
            swap(vector.at(i), vector.at(min_index));
        }
    }
} // Time complexity: O(n^2), Space complexity: O(1)

void Sorting<T>::insertion_sort(Vector<T>& vector, size_t start, size_t end) {
    for (size_t mark = start + 1; mark < end + 1; ++mark) {
        T key = vector.at(mark);
        size_t j = mark;

        // Shifts elements to the right 
        while (j > start && vector.at(j - 1) > key) {
            vector.at(j) = vector.at(j - 1);
            --j;
        }
        vector.at(j) = key;
    }
} // Time complexity: O(n^2)
void Sorting<T>::insertion_sort(Vector<T>& vector) {
    if (vector.size() < 2) { return; }
    insertion_sort(vector, 0, vector.size() - 1);
} // Time complexity: O(n^2)

void Sorting<T>::shell_sort(Vector<T>& vector) {
    const size_t n = vector.size();

    // Starts with gap = n/2, and reduces it by half
    for (size_t gap = n/2; gap > 0; gap /= 2) {
        // Performs a gapped insertion sort
        for (size_t i = gap; i < n; ++i) {
            T temp = vector.at(i);
            size_t j = i;

            // Shifts larger elements to the right
            while (j >= gap && vector.at(j - gap) > temp) {
                vector.at(j) = vector.at(j - gap);
                j -= gap;
            }

            // Inserts the element into its correct position
            vector.at(j) = temp;

        }
    }
} // Time complexity: O(nlogn)

void Sorting<T>::merge (const Vector<T>& left, Vector<T>& right, Vector<T>& merged) {
    size_t i = 0, j = 0, k = 0;

    // Merges the two halves into the merged vector
    while (i < left.size() && j < right.size()) {
        if (left.at(i) <= right.at(j)) {
            merged.at(k++) = left.at(i++);
        } else {
            merged.at(k++) = right.at(j++);
        }
    }

    // Copies any remaining elements from the left half
    while (i < left.size()) {
        merged.at(k++) = left.at(i++);
    }
    // Copies any remaining elements from the right half
    while (j < right.size()) {
        merged.at(k++) = right.at(j++);
    }
} // Time complexity: O(n)

void Sorting<T>::merge_sort(Vector<T>& vector) {
    // Base case: if the vector has 1 or 0 elements, it's already sorted
    if (vector.size() < 2) {
        return;
    }

    // Splits the vector into two halves
    Vector<T> left, right;
    for (size_t i = 0; i < vector.size(); ++i) {
        if (i < vector.size() / 2) {
            left.push_back(vector.at(i));
        } else {
            right.push_back(vector.at(i));
        }
    }

    // Recursively sorts both halves
    merge_sort(left);
    merge_sort(right);

    // Merges the sorted halves back into the original vector
    merge(left, right, vector);
} // Time complexity: O(nlogn)

/** Partitions the vector using the Lomuto partitioning.
    @param vector The vector to be partitioned
    @param low The starting index of the sub-vector to be partitioned
    @param high The ending index of the sub-vector to be partitioned
    @return The index of the pivot after partitioning
*/
size_t Sorting<T>::lomuto_partition(Vector<T>& vector, size_t low, size_t high) {
    T pivot = vector.at(high); // Chooses the last element as the pivot
    size_t i = low; // Pointer for the smaller element

    // Move smaller elements to the left of the pivot
    for (size_t j = low; j < high; ++j) {
        if (vector.at(j) < pivot) {
            swap(vector.at(i), vector.at(j));
            ++i;
        }
    }
    // Place the pivot in its correct position
    swap(vector.at(i), vector.at(high));
    return i;
} // Time complexity: O(n), Space complexity: O(1)

/** Recursively sorts the vector using the Lomuto quick sort algorithm.
    @param vector The vector to be sorted
    @param low The starting index of the sub-vector to be sorted
    @param high The ending index of the sub-vector to be sorted
*/
void Sorting<T>::lomuto_quick_sort_recursive(Vector<T>& vector, size_t low, size_t high) {
    // Base case: if the sub-array has 1 or 0 elements, it's already sorted
    if (low >= high) { return; }

    // Partitions the array and gets the pivot index
    size_t pivot_index = lomuto_partition(vector, low, high);

    // Recursively sorts the elements before and after the pivot
    if (pivot_index > low) {
        lomuto_quick_sort_recursive(vector, low, pivot_index - 1);
    }
    if (pivot_index < high) {
        lomuto_quick_sort_recursive(vector, pivot_index + 1, high);
    }
} // Time complexity: O(nlogn)

/** Sorts the vector using the quick sort algorithm.
    @param vector The vector to be sorted
*/
void Sorting<T>::quick_sort(Vector<T>& vector) {
    // Base case: if the vector has 1 or 0 elements, it's already sorted
    if (vector.size() < 2) { return; }

    // Calls the recursive quick sort function
    hoare_quick_sort_with_median_recursive(vector, 0, vector.size() - 1);
} // Time complexity: O(nlogn)

/** Partitions a vector using Hoare's scheme.
    @param vector: Vector to be partitioned
    @param low: Starting index of the sub-vector to be partitioned
    @param high: Ending index of the sub-vector to be partitioned
    @return: Boundary between the two partitions
*/
size_t Sorting<T>::hoare_partition(Vector<T>& vector, size_t low, size_t high) {
    T pivot = vector.at(low); // Chooses the first element as the pivot
    size_t i = low; // Pointer for the smaller element
    size_t j = high; // Pointer for the larger element

    while (true) {
        // Finds an element >= pivot from the left
        while (vector.at(i) < pivot) {
            ++i;
        }

        // Finds an element <= pivot from the right
        while (vector.at(j) > pivot) {
            --j;
        }

        // If the pointers have crossed, return the partition index
        if (i >= j) {
            return j;
        }

        // Swap elements at i and j
        swap(vector.at(i), vector.at(j));

        // Move the pointers
        ++i;
        --j;
    }
} // Time complexity: O(n)

/** Recursively sorts the vector using the Hoare quick sort algorithm.
    @param vector The vector to be sorted
    @param low The starting index of the sub-vector to be sorted
    @param high The ending index of the sub-vector to be sorted
*/
void Sorting<T>::hoare_quick_sort_recursive(Vector<T>& vector, size_t low, size_t high) {
    // Base case: if the sub-array has 1 or 0 elements, it's already sorted
    if (low >= high) { return; }

    // Partitions the array and gets the pivot index
    size_t pivot_index = hoare_partition(vector, low, high);

    // Recursively sorts the elements before and after the pivot
    hoare_quick_sort_recursive(vector, low, pivot_index);
    hoare_quick_sort_recursive(vector, pivot_index + 1, high);
} // Time complexity: O(nlogn)

/** Returns the index of the median of three elements in a vector.
    @param vector: The vector containing the elements
    @param left: The index of the first element
    @param right: The index of the last element
    @return The index of the median element
*/
size_t Sorting<T>::median_of_three(Vector<T>& vector, size_t left, size_t right) {
    size_t mid = left + (right - left) / 2;

    // Order the left, mid, and right elements
    if (vector.at(left) > vector.at(mid)) {
        swap(vector.at(left), vector.at(mid));
    }
    if (vector.at(left) > vector.at(right)) {
        swap(vector.at(left), vector.at(right));
    }
    if (vector.at(mid) > vector.at(right)) {
        swap(vector.at(mid), vector.at(right));
    }

    return mid;
}

size_t Sorting<T>::hoare_partition_with_median(Vector<T>& vector, size_t left, size_t right) {
    size_t median_index = median_of_three(vector, left, right);
    T pivot = vector.at(median_index);

    size_t i = left;
    size_t j = right;

    while (true) {
        // Move i to the right until fiding an element >= pivot
        while (vector.at(i) < pivot) {
            ++i;
        }
        // Move j to the left until finding an element <= pivot
        while (vector.at(j) > pivot) {
            --j;
        }
        // Pointers crossed, return the partition index
        if (i >= j) {
            return j;
        }

        // Swap elements at i and j
        swap(vector.at(i), vector.at(j));

        // Move the pointers
        ++i;
        --j;
    }
} // Time complexity: O(n)

void Sorting<T>::hoare_quick_sort_with_median_recursive(Vector<T>& vector, size_t left, size_t right) {
    const size_t INSERTION_SORT_THRESHOLD = 16; // Threshold for switching to insertion sort

    // Base case: if the sub-array has 1 or 0 elements, it's already sorted
    if (left >= right) { return; }

    // Small partition: use insertion sort
    if (right - left < INSERTION_SORT_THRESHOLD) {
        insertion_sort(vector, left, right);
        return;
    }

    // Large partition: median of three + Hoare
    size_t pivot_index = hoare_partition_with_median(vector, left, right);
    hoare_quick_sort_with_median_recursive(vector, left, pivot_index);
    hoare_quick_sort_with_median_recursive(vector, pivot_index + 1, right);
} // Time complexity: O(nlogn)

/** Heapify a node in a max heap
 * @param vector: The vector containing the heap
 * @param root: The index of the root of the subtree to heapify
 * @param size: The size of the heap
 */
void Sorting<T>::max_heapify(Vector<T>& vector, size_t root, size_t size) {
    size_t left = root * 2 + 1; // Left child index
    size_t right = root * 2 + 2; // Right child index
    size_t max = root;

    // Finds the largest among root, left child, and right child
    if (left < size && vector.at(max) < vector.at(left)) {
        max = left;
    }
    if (right < size && vector.at(max) < vector.at(right)) {
        max = right;
    }

    // If the largest element is not the root, swap it with the root and continue heapifying
    if (max != root) {
        swap(vector.at(root), vector.at(max));
        max_heapify(vector, max, size);
    }
} // Time complexity: O(log(n))

void Sorting<T>::build_max_heap(Vector<T>& vector, size_t root) {
    size_t left = root * 2 + 1; // Left child index
    size_t right = root * 2 + 2; // Right child index
    
    if (left < vector.size()) {
        build_max_heap(vector, left);
    }
    if (right < vector.size()) {
        build_max_heap(vector, right);
    }
    max_heapify(vector, root, vector.size());
} // Time complexity: O(log(n))

void Sorting<T>::heap_sort(Vector<T>& vector, size_t size) {
    // Build a max heap from the vector
    build_max_heap(vector, 0); // Converts vector to max heap

    // One by one extract elements from the heap
    for (size_t i = size - 1; i > 0; --i) {
        // Move the current root to the end
        swap(vector.at(0), vector.at(i));

        // Call max_heapify on the reduced heap
        max_heapify(vector, 0, --size); 
    }
} // Time complexity: O(nlog(n))
void Sorting<T>::heap_sort(Vector<T>& vector) {
    if (vector.size() < 2) { return; }
    heap_sort(vector, vector.size());
} // Time complexity: O(nlog(n))


template<class T>
void Sorting<T>::min(const Vector<T>& vector) {
    if (vector.empty()) {
        throw std::invalid_argument("Vector is empty.");
    }

    T min_value = vector.at(0);
    for (size_t i = 1; i < vector.size(); ++i) {
        if (vector.at(i) < min_value) {
            min_value = vector.at(i);
        }
    }
} // Time complexity: O(n)

template<class T>
void Sorting<T>::max(const Vector<T>& vector) {
    if (vector.empty()) {
        throw std::invalid_argument("Vector is empty.");
    }

    T max_value = vector.at(0);
    for (size_t i = 1; i < vector.size(); ++i) {
        if (vector.at(i) > max_value) {
            max_value = vector.at(i);
        }
    }
} // Time complexity: O(n)

template<class T>
void Sorting<T>::count_frequency(const Vector<T>& vector, T min_value, T max_value) {
    size_t range = static_cast<size_t>(max_value - min_value + 1);

    // Initializes all count to 0
    Vector<size_t> count(range, 0);

    // Counts the frequency of each element in the vector
    for (size_t i = 0; i < vector.size(); ++i) {
        size_t index = static_cast<size_t>(vector.at(i) - min_value);
        ++count.at(index);
    }
    return count;
}

template<class T>
void Sorting<T>::counting_sort(Vector<T>& vector) {
    static_assert(std::is_integral<T>::value, "Counting sort can only be used with integral types.");

    if (vector.size() < 2) { return; } 

    // Step 1: Find the maximum and minimum values in the vector
    T min_value = min(vector);
    T max_value = max(vector);

    // Step 2: Count the frequency of each element in the vector
    Vector<size_t> count = count_frequency(vector, min_value, max_value);

    // Step 3: Calculates the cumulative count
    for (size_t i = 1; i < count.size(); ++i) {
        count.at(i) += count.at(i - 1);
    }

    // Step 4: Build the output vector
    Vector<T> output(vector.size());

    for (size_t i = vector.size(); i > 0; --i) {
        T value = vector.at(i - 1);
        size_t index = static_cast<size_t>(value - min_value);
        size_t position = count.at(index) - 1;
        output.at(position) = value;
        --count.at(index);
    }

    // Step 5: Copy the output vector back to the original vector
    vector = output;
} // Time complexity: O(n + k)

template<class T>
void Sorting<T>::counting_sort_by_digit(Vector<T>& vector, size_t digit_place) {
    static_assert(std::is_integral<T>::value, "Counting sort can only be used with integral types.");

    if (vector.size() < 2) { return; } 

    const size_t BASE = 10;

    Vector<size_t> count(BASE, 0); // Initializes all count to 0
    Vector<T> output(vector.size()); // Output vector

    // Step 1: Count the frequency of each digit
    for (size_t i = 0; i < vector.size(); ++i) {
        size_t digit = (vector.at(i) / digit_place) % BASE;
        ++count.at(digit);
    }

    // Step 2: Calculates the cumulative count
    for (size_t i = 1; i < count.size(); ++i) {
        count.at(i) += count.at(i - 1);
    }

    // Step 3: Build the output from right to left
    for (size_t i = vector.size(); i > 0; --i) {
        T value = vector.at(i - 1);
        size_t digit = (value / digit_place) % BASE;

        size_t position = count.at(digit) - 1;
        output.at(position) = value;
        --count.at(digit);
    }

    // Step 4: Copy the output vector back to the original vector
    vector = output;
} // Time complexity: O(n + k)

template<class T>
void Sorting<T>::radix_sort(Vector<T>& vector) {
    static_assert(std::is_integral<T>::value, "Radix sort can only be used with integral types.");

    if (vector.size() < 2) { return; } 

    // Step 1: Find the maximum value to determine the number of digits
    T max_value = max(vector);

    // Step 2: Sort by each digit, from least significant to most significant
    for (size_t digit_place = 1; max_value / digit_place > 0; digit_place *= 10) {
        counting_sort_by_digit(vector, digit_place);

        // Prevent overflow when increasing digit_place
        if (digit_place > max_value / 10) {
            break;
        }
    }
} // Time complexity: O(d * (n + 10))

template<class T>
void Sorting<T>::bucket_sort(Vector<T>& vector) {
    static_assert(std::is_floating_point<T>::value, "Bucket sort can only be used with floating-point types.");

    if (vector.size() < 2) { return; } 

    // Step 1: Finds the maximum and minimum values
    T min_value = min(vector);
    T max_value = max(vector);

    // Step 2: Create buckets
    const size_t TARGET_BUCKET_SIZE = 256; // Target size for each bucket
    const size_t MAX_BUCKETS = 4096; // Maximum number of buckets

    size_t bucket_count = vector.size() / TARGET_BUCKET_SIZE;

    if (bucket_count == 0) {
        bucket_count = 1; // At least one bucket
    } else if (bucket_count > MAX_BUCKETS) {
        bucket_count = MAX_BUCKETS; // Limit to maximum buckets
    }

    size_t value_range = static_cast<size_t>(max_value - min_value + 1);

    if ( bucket_count > value_range) {
        bucket_count = value_range; // Limit to the range of values
    }

    Vector<Vector<T>> buckets(bucket_count); // Creates the buckets

    // Step 3: Distribute the elements into buckets
    for (size_t i = 0; i < vector.size(); ++i) {
        size_t index = static_cast<size_t>(((vector.at(i) - min_value) / range) * bucket_count);

        buckets.at(index).push_back(vector.at(i));
    }

    // Step 4: Sort each bucket
    for (size_t i = 0; i < bucket_count; ++i) {
        if (buckets.at(i).size() < 35) { // Threshold for using insertion sort
            insertion_sort(buckets.at(i));
        } else {
            quick_sort(buckets.at(i));
        }
    }

    // Step 5: Concatenate the sorted buckets back into the original vector
    size_t index = 0;

    for (size_t i = 0; i < bucket_count; ++i) {
        for (size_t j = 0; j < buckets.at(i).size(); ++j) {
            vector.at(index++) = buckets.at(i).at(j);
        }
    }
}


