// Created by ThanhDat Nguyen (tnrbf@umsystem.edu) on 2024-10-22

// Last updated by ThanhDat Nguyen (tnrbf@umsystem.edu) on 2024-10-29

#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <string>
#include <stdexcept>

using std::exception;
using std::ostream;
using std::to_string;
using std::runtime_error;

/** A vector without iterators */
template<class T>
class Vector {
public:
    // Constructors
    Vector();  // Default constructor
    Vector(size_t);  // Constructs a vector with specified initial size.
    Vector(size_t, const T&);  // Constructs a vector with specified initial size and filling value.
    Vector(const Vector<T>&);  // Copy constructor

    // Destructor
    ~Vector();

    // Operators
    const Vector<T>& operator = (const Vector<T>&);  // Deep-copy assignment operator
    T& operator [] (size_t);  // Subscript operator (l-value)
    const T& operator [] (size_t) const;  // Subscript operator (r-value)

    // Class-member functions
    size_t size() const;  // Returns the size of the vector.
    bool empty() const;  // Tests whether the vector is empty or not.
    T& at(size_t);  // Returns the element at specified index (l-value).
    const T& at(size_t) const;  // Returns the element at specified index (r-value).
    T& front();  // Returns the first element in the vector (l-value).
    const T& front() const;  // Returns the last element in the vector (r-value).
    T& back();  // Returns the last element in the vector (l-value).
    const T& back() const;  // Returns the last element in the vector (r-value).
    void push_back(const T&);  // Adds a new element to the rear end of the vector.
    void pop_back();  // Deletes the last element in the vector.

private:
    // Constant
    static const size_t DEFAULT_CAPACITY;  // Default capacity used when capacity is not specified

    // Data fields
    T* data;  // Stores the elements in the vector.
    size_t capacity;  // Stores the length of the array "data".
    size_t num_of_items;  // Stores the number of elements in the vector.

    // Class-member function
    void resize();  // Doubles the capacity of the vector without changing the current data stored in it.
};

// Implementation of class Vector

// Static variable
template<class T>
const size_t Vector<T>::DEFAULT_CAPACITY = 10;

// Constructors

// Default constructor
template<class T>
Vector<T>::Vector() : capacity(DEFAULT_CAPACITY), num_of_items(0) {
    data = new T[DEFAULT_CAPACITY];
}  // Time complexity: O(1)

// Constructs a vector with specified initial size.
template<class T>
Vector<T>::Vector(size_t initial_size) : num_of_items(initial_size) {
    capacity = initial_size < DEFAULT_CAPACITY ? DEFAULT_CAPACITY : initial_size;
    data = new T[capacity];
}  // Time complexity: O(1)

// Constructs a vector with specified initial size and filling value.
template<class T>
Vector<T>::Vector(size_t initial_size, const T& filling_value) : num_of_items(initial_size) {
    capacity = initial_size < DEFAULT_CAPACITY ? DEFAULT_CAPACITY : initial_size;
    data = new T[capacity];
    for (size_t i = 0; i < num_of_items; i++) { data[i] = filling_value; }
}  // Time complexity: O(n)

// Copy constructor
template<class T>
Vector<T>::Vector(const Vector<T>& other) {
    data = NULL;
    *this = other;
}  // Time complexity: O(n)

// Destructor
template<class T>
Vector<T>::~Vector() {
    if (data) { delete[] data; }
}  // Time complexity: O(1)

// Operators

/** Deep-copy assignment operator.
    Creates a deep copy of the contents from another Vector into this one, ensuring an independent copy.
    @param rhs: the source Vector from which to copy.
    @return a reference to this Vector with updated contents from rhs.
*/
template<class T>
const Vector<T>& Vector<T>::operator = (const Vector<T>& rhs) {
    // Step 1: avoid self-assignment
    if (this != &rhs) {
        // Step 2: delete current dynamic memory
        if (data) {
            delete[] data;
            data = NULL; // Never forget to set a pointer to safe value after deleting it
        }
        // Step 3: copy static data fields.
        capacity = rhs.capacity;
        num_of_items = rhs.num_of_items;
        // Step 4: copy dynamic data fields.
        if (capacity) {
            data = new T[capacity];
            for (size_t i = 0; i < num_of_items; i++) { data[i] = rhs.data[i]; }
        }
    }
    //Step 5: return.
    return *this;
}  // Time complexity: O(n)

/** Subscript operator (l-value).
    Provides access to an element at the specified index, allowing modification.
    @param index: the position of the element to access in the Vector.
    @return a reference to the element at the specified index, allowing it to be modified.
*/
template<class T>
T& Vector<T>::operator [] (size_t index) { return data[index]; }  // Time complexity: O(1)

/** Subscript operator (r-value).
    Provides read-only access to an element at the specified index.
    @param index: the position of the element to access in the Vector.
    @return a const reference to the element at the specified index, preventing modification.
*/
template<class T>
const T& Vector<T>::operator [] (size_t index) const { return data[index]; }  // Time complexity: O(1)

// Class-member functions

/** Returns the size of the vector.
    @return: size of the vector
*/
template<class T>
size_t Vector<T>::size() const { return num_of_items; }  // Time complexity: O(1)

/** Tests whether the vector is empty or not.
    @return: {true} if the vector is empty; {false} otherwise
*/
template<class T>
bool Vector<T>::empty() const { return !size(); }  // Time complexity: O(1)

/** Returns the element at specified index (l-value).
    @param index: specified index
    @return: element at specified index
    @throw exception: index >= size()
*/
template<class T>
T& Vector<T>::at(size_t index) {
    if (index >= size()) { throw runtime_error("Index out of range: " + to_string(index)); }
    return data[index];
}  // Time complexity: O(1)

/** Returns the element at specified index (r-value).
    @param index: specified index
    @return: element at specified index
    @throw exception: index >= size()
*/
template<class T>
const T& Vector<T>::at(size_t index) const {
    if (index >= size()) { throw runtime_error("Index out of range: " + to_string(index)); }
    return data[index];
}  // Time complexity: O(1)

/** Returns the first element in the vector (l-value).
    @return: first element in the vector
    @throw exception: vector is empty.
*/
template<class T>
T& Vector<T>::front() {
    if (empty()) { throw exception("Accessing empty vector"); }
    return at(0);
}  // Time complexity: O(1)

/** Returns the first element in the vector (r-value).
    @return: first element in the vector
    @throw exception: vector is empty.
*/
template<class T>
const T& Vector<T>::front() const {
    if (empty()) { throw exception("Accessing empty vector"); }
    return at(0);
}  // Time complexity: O(1)

/** Returns the last element in the vector (l-value).
    @return: first element in the vector
    @throw exception: vector is empty.
*/
template<class T>
T& Vector<T>::back() {
    if (empty()) { throw exception("Accessing empty vector"); }
    return at(size() - 1);
}  // Time complexity: O(1)

/** Returns the last element in the vector (r-value).
    @return: first element in the vector
    @throw exception: vector is empty.
*/
template<class T>
const T& Vector<T>::back() const {
    if (empty()) { throw exception("Accessing empty vector"); }
    return at(size() - 1);
}  // Time complexity: O(1)

/** Doubles the capacity of the vector without changing the current data stored in it. */
template<class T>
void Vector<T>::resize() {
    capacity *= 2;
    T* new_data = new T[capacity];
    for (size_t i = 0; i < size(); i++) { new_data[i] = data[i]; }
    delete[] data;
    data = new_data;
}  // Time complexity: O(n)

/** Adds a new element to the rear end of the vector.
    @param item: new element to add to the vector
*/
template<class T>
void Vector<T>::push_back(const T& item) {
    if (size() == capacity) { resize(); }
    data[num_of_items++] = item;
}  // Time complexity: O(1)

/** Deletes the last element in the vector.
    @throw exception: vector is empty.
*/
template<class T>
void Vector<T>::pop_back() {
    if (empty()) { throw runtime_error("Accessing empty vector"); }
    num_of_items--;
}  // Time complexity: O(1)

/** Stream insertion operator.
    Outputs the contents of the Vector to an output stream.
    @param out: the output stream to insert the Vector's contents into.
    @param vec: the Vector object to output.
    @return the output stream, allowing chaining of stream operations.
*/
template<class T>
ostream& operator << (ostream& out, const Vector<T>& vec) {
    out << '[';
    for (size_t i = 0; i < vec.size(); i++) {
        out << vec.at(i);
        if (i != vec.size() - 1) { out << ", "; }
    }
    return out << ']';
}  // Time complexity: O(n)

#endif