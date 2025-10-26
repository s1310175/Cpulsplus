// ArrayQueue.h

#include <string>
#include <iostream>
#include <utility> // Necessary for std::swap and std::move
#include <stdexcept>

#ifndef ARRAY_QUEUE_H
#define ARRAY_QUEUE_H

class ArrayQueue {
private:
    int _num_items;        // Number of elements currently in the queue
    int _allocated_size;   // Size of the allocated memory (capacity)
    int _first;            // Index of the front element (the next one to dequeue)
    int _last;             // Index of the next available slot
    std::string* _items;   // The dynamic array holding the elements
    
    // Helper to dynamically change the size of the underlying array. Copies data to a new array.
    void resize(int max_size) {
        if (max_size == 0) max_size = 1; // Ensure minimum size

        std::string* temp = new std::string[max_size];
        
        // Copy elements in logical FIFO order, resolving the circular layout
        for (int i = 0; i < _num_items; ++i) {
            temp[i] = _items[(i + _first) % _allocated_size];
        }
        
        delete[] _items;
        
        _items = temp;
        // Reset indices for the new non-circular layout
        _first = 0; 
        _last = _num_items;
        _allocated_size = max_size;
    }

public:
    // Default constructor
    ArrayQueue() 
    : _num_items(0), _allocated_size(10), _first(0), _last(0), _items(new std::string[10])
    {}

    // Constructor to specify initial capacity
    explicit ArrayQueue(int allocated_size) 
    : _num_items(0), _first(0), _last(0)
    {
        _allocated_size = (allocated_size > 0) ? allocated_size : 1; // Ensure minimum size
        _items = new std::string[_allocated_size];
    }

    // Destructor: Free the dynamically allocated memory
    ~ArrayQueue() {
        delete[] _items;
    }

    // Copy Constructor (Performs a deep copy)
    ArrayQueue(const ArrayQueue& other) 
    : _num_items(other._num_items),
      _allocated_size(other._allocated_size),
      _first(0), // The copy starts at index 0 for simplicity
      _last(other._num_items)
    {
        _items = new std::string[_allocated_size];

        // Copy all elements
        for (int i = 0; i < _num_items; ++i) {
            _items[i] = other._items[(i + other._first) % other._allocated_size];
        }
    }

    // Copy Assignment Operator (Using the copy-and-swap idiom)
    ArrayQueue& operator=(const ArrayQueue& other) {
        ArrayQueue temp = other; // Create a temporary copy
        
        // Swap resources between *this and temp
        std::swap(_num_items, temp._num_items);
        std::swap(_allocated_size, temp._allocated_size);
        std::swap(_first, temp._first);
        std::swap(_last, temp._last);
        std::swap(_items, temp._items); // Swap the raw pointers!

        return *this;
        // temp's destructor safely cleans up the old resources of *this
    }

    // Move Constructor (Transfers resource ownership)
    ArrayQueue(ArrayQueue&& other) noexcept
    : _num_items(other._num_items),
      _allocated_size(other._allocated_size),
      _first(other._first),
      _last(other._last),
      _items(other._items) // Steal the pointer
    {
        // Nullify the source to leave it in a valid, destructible state
        other._num_items = 0;
        other._allocated_size = 0;
        other._first = 0;
        other._last = 0;
        other._items = nullptr; // Prevent double-free
    }

    // Move Assignment Operator (Transfers resource ownership)
    ArrayQueue& operator=(ArrayQueue&& other) noexcept {
        if (this != &other) {
            delete[] _items; // Release own resources 

            // Move data from the source
            _num_items = other._num_items;
            _allocated_size = other._allocated_size;
            _first = other._first;
            _last = other._last;
            _items = other._items;

            // Nullify the source
            other._num_items = 0;
            other._allocated_size = 0;
            other._first = 0;
            other._last = 0;
            other._items = nullptr;
        }
        return *this;
    }

    // Add an element to the back of the queue
    void enqueue(const std::string& item) {
        if (_num_items == _allocated_size) resize(2*_allocated_size); // Double capacity if full
        _items[_last++] = item; 
        if (_last == _allocated_size) _last = 0; // Wrap around
        _num_items++; 
    }

    // Remove the element from the front of the queue
    void dequeue() {
        if (_num_items == 0) {
            std::cerr << "Error: Attempt to dequeue from an empty queue." << std::endl;
            return;
        }
        _num_items--;
        _first++; 
        if (_first == _allocated_size) _first = 0; // Wrap around
        
        // Shrink array by half if usage drops to 1/4 of capacity (and capacity > 4)
        if (_num_items > 0 && _allocated_size > 4 && _num_items == _allocated_size/4) {
             resize(_allocated_size/2);
        }
    }

    // Peek at the front element without removing it
    std::string peek() const {
        if (_num_items == 0) {
            throw std::runtime_error("Attempt to peek into an empty queue.");
        }
        return _items[_first];
    }

    // Check if the queue is empty
    bool empty() const { return _num_items == 0; }

    // Return the number of elements in the queue
    int size() const { return _num_items; }

    // Return the current allocated memory capacity (Helper for testing)
    int allocated_size() const { return _allocated_size; }
};

#endif // ARRAY_QUEUE_H
