// ArrayQueue.h

#include <string>
#include <iostream>

#ifndef ARRAY_QUEUE_H
#define ARRAY_QUEUE_H

class ArrayQueue {
private:
    int _num_items;        // number of items in the queue
    int _allocated_size;   // size of memory allocated
    int _first;            // index to the first element of the queue 
    int _last;             // index of the next available slot 
    std::string* _items;   // container 
    
    // Helper function to dynamically change the size of the underlying array
    void resize(int max_size) {
        // Ensure a minimum size of 1 if max_size is calculated as 0
        if (max_size == 0) max_size = 1; 

        // Move data to a new array of size max_size
        std::string* temp = new std::string[max_size];
        
        // Copy elements in logical FIFO order
        for (int i = 0; i < _num_items; ++i) {
            // Calculate the index in the old array using modulo arithmetic
            temp[i] = _items[(i + _first) % _allocated_size];
        }
        
        // Deallocate the old memory
        delete[] _items;
        
        // Update members to point to the new array
        _items = temp;

        // Reset indices for the new non-circular layout
        _first = 0; 
        _last = _num_items;
        _allocated_size = max_size;
    }

public:
    // Constructors:
    // Default constructor 
    ArrayQueue() 
    /* COMPLETE ... Create an empty queue */
    : _num_items(0), _allocated_size(10), _first(0), _last(0), _items(new std::string[10])
    {}

    explicit ArrayQueue(int allocated_size) 
    /* COMPLETE ... Create an empty queue with memory allocated 
     * to store 'allocated_size' items 
     */
    : _num_items(0), _first(0), _last(0)
    {
        // Ensure minimum allocation size is 1
        _allocated_size = (allocated_size > 0) ? allocated_size : 1;
        _items = new std::string[_allocated_size];
    }

    // Destructor:
    ~ArrayQueue() {
        // COMPLETE: Deallocate the dynamically allocated array
        delete[] _items;
    }

    // Add an item to the queue 
    void enqueue(const std::string& item) {
        if (_num_items == _allocated_size) resize(2*_allocated_size);
        _items[_last++] = item; 
        if (_last == _allocated_size) _last = 0; // wrap 
        _num_items++; 
    }

    // Remove the item that was least recently added 
    void dequeue() {
        if (_num_items == 0) {
            // Optional: Handle attempt to dequeue from an empty queue (e.g., throw exception or print error)
            std::cerr << "Error: Attempt to dequeue from an empty queue." << std::endl;
            return;
        }
        _num_items--;
        _first++; 
        if (_first == _allocated_size) _first = 0; // wrap 
        
        // Shrink the array if the usage drops to 1/4 of the capacity (but not below a small minimum size, e.g., 4)
        if (_num_items > 0 && _allocated_size > 4 && _num_items == _allocated_size/4) {
             resize(_allocated_size/2);
        }
    }

    // Access the first item 
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

    // Helper function for testing (not part of the standard interface)
    int allocated_size() const { return _allocated_size; }
};

#endif // ARRAY_QUEUE_H
