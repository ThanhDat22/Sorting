#include "Sorting.h"

#include <iostream>
#include <iomanip>
#include <chrono>

// Function prototypes
const string sorting_name(int); // Gets the name of the sorting algorithms
void display_menu(); // Displays the menu of sorting algorithms
bool is_sorted(const Vector<int>&); // Checks if the vector is sorted
bool apply_sort(int, Vector<int>&); // Applies the sorting algorithm based on the choice
void experiment(int, const Vector<int>&); // Runs the experiment for the sorting algorithm
void run_experiments(int, const Vector<int>&); // Runs the experiments for the sorting algorithm

int main() {
    // Create a Sorting object
    Vector<int> vec = Sorting::generate_vector(20, 0, 99);

    int choice;
    while(true) {
        display_menu();
        if (!(cin >> choice)) {
            if (cin.eof()) {
                cout << "\nExiting program." << endl;
                break;
            }
            cin.clear(); // Clear the error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "Invalid input. Please enter a number." << endl;
            continue;
        }

        if (choice == 0) { break; }
        if (choice > 0 && choice < 13) {
            cout << "\nOriginal vector: " << vec << endl;
            experiment(choice, vec);
        } else if (choice == 13) {
            run_experiments(choice, vec);
        } else if (choice == 14) {
            cout << "Generating a new vector..." << endl;
            vec = Sorting::generate_vector(20, 0, 99);
            cout << "New vector generated: " << vec << endl;
        } else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }
    cout << "Program terminated." << endl;
    return 0;   
}

// Function definitions

/** Get the name of the sorting algorithm based on its choice.
    @param choice: the choice of the sorting algorithm
    @return: the name of the sorting algorithm
*/
const string sorting_name(int choice) {
    switch (choice) {
        case 1:
            return "Bubble Sort";
        case 2:
            return "Selection Sort";
        case 3:
            return "Insertion Sort";
        case 4:
            return "Shell Sort";
        case 5:
            return "Merge Sort";
        case 6:
            return "Quick Sort";
        case 7:
            return "Heap Sort";
        case 8:
            return "Counting Sort";
        case 9:
            return "Radix Sort";
        case 10:
            return "Bucket Sort";
        case 11:
            return "Tim Sort";
        case 12:
            return "Intro Sort";
        default:
            return "Unknown";
    }
} // Time complexity: O(1), Space complexity: O(1)

/** Display the menu of sorting algorithms.
*/
void display_menu() {
    cout << "Sorting Algorithms Menu:" << endl;
    for (size_t i = 1; i < 13; ++i) {
        cout << setw(2) << i << ". " << sorting_name(i) << endl;
        if (i > 2) {
            cout << "   (Not implemented yet)" << endl;
        }
    }
    cout << "13. Run experiments for all sorting algorithms" << endl;
    cout << "14. Generate a new vector" << endl;
    cout << " 0. Exit" << endl;
    cout << "Choose: ";
} // Time complexity: O(1), Space complexity: O(1)

/** Checks if the vector is sorted.
    @param vector: the vector to check
    @return: {true} if the vector is sorted, {false} otherwise
*/
bool is_sorted(const Vector<int>& vector) {
    for (size_t i = 1; i < vector.size(); ++i) {
        if (vector.at(i) < vector.at(i - 1)) {
            return false;
        }
    }
    return true;
} // Time complexity: O(n), Space complexity: O(1)

/** Applies a sorting algorithm to the vector.
    @param choice: the choice of the sorting algorithm
    @param vec: the vector to sort
    @return: {true} if the sorting was successful, {false} otherwise
*/
bool apply_sort(int choice, Vector<int>& vec) {
    switch (choice) {
        case 1:
            Sorting::bubble_sort(vec);
            break;
        case 2:
            Sorting::selection_sort(vec);
            break;
        case 3:
            Sorting::insertion_sort(vec);
            break;
        case 4:
            Sorting::shell_sort(vec);
            break;
        case 5:
            Sorting::merge_sort(vec);
            break;
        case 6:
            Sorting::quick_sort(vec);
            break;
        case 7:
            Sorting::heap_sort(vec);
            break;
        case 8:
            Sorting::counting_sort(vec);
            break;
        case 9:
            Sorting::radix_sort(vec);
            break;
        case 10:
            Sorting::bucket_sort(vec);
            break;
        case 11:
            Sorting::tim_sort(vec);
            break;
        case 12:
            Sorting::intro_sort(vec);
            break;
        default:
            return false; // Invalid choice
    }
    return true; // Valid choice
} 

/** Runs an experiment to test a sorting algorithm.
    @param choice: the choice of the sorting algorithm
    @param original_vec: the original vector to sort
*/
void experiment(int choice, const Vector<int>& original_vec) {
    if (choice < 1 || choice > 12) {
        cout << "Invalid choice for experiment." << endl;
        return;
    }

    Vector<int> current_vec = original_vec; // Copy the original vector
    const auto start_time = chrono::steady_clock::now(); // Start timing
    const bool implemented = apply_sort(choice, current_vec); // Apply the sorting algorithm
    const auto end_time = chrono::steady_clock::now(); // End timing

    cout << "\n" << sorting_name(choice) << ": ";
    if (!implemented) {
        cout << "Not implemented yet." << endl;
        return;
    }

    const auto duration = chrono::duration_cast<chrono::microseconds>(end_time - start_time).count();
    cout << "\nResult: " << current_vec << endl;
    cout << "Sorted: " << (is_sorted(current_vec) ? "Yes" : "No") << endl;
    cout << "Time taken: " << duration << " microseconds" << endl;
}

/** Runs an experiment to test a sorting algorithm.
    @param choice: the choice of the sorting algorithm
    @param original_vec: the original vector to sort
*/
void run_experiments(int choice, const Vector<int>& original_vec) {
    cout << "\nOriginal vector: " << original_vec << endl;
    for (size_t i = 1; i < 13; ++i) {
        experiment(i, original_vec);
    }
    cout << "\nAll experiments completed." << endl;
}