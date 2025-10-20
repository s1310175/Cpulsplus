#include "Ex04-1-1.cpp" // Include the header definitions

// Checks if the queue is empty.
bool Queue::empty() const {
    return _num_items == 0;
}

// Checks if the queue is full (reached max capacity).
bool Queue::full() const {
    return _num_items == _max_size;
}

// Returns the current number of elements in the queue.
int Queue::size() const {
    return _num_items;
}

// Inserts a Point element at the back of the queue.
void Queue::enqueue(const Point& p) {
    if (full()) {
        std::cerr << "Error: Queue overflow. Cannot enqueue item." << std::endl;
        exit(EXIT_FAILURE); 
    }

    _items[_last] = p;
    _last = (_last + 1) % _max_size;
    _num_items++;
}

// Removes the element from the front of the queue.
void Queue::dequeue() {
    if (empty()) {
        std::cerr << "Error: Queue underflow. Cannot dequeue from empty queue." << std::endl;
        exit(EXIT_FAILURE);
    }
    
    _first = (_first + 1) % _max_size;
    _num_items--;
}

// Accesses the element at the front of the queue without removing it.
const Point& Queue::peek() const {
    if (empty()) {
        std::cerr << "Error: Queue underflow. Cannot peek into empty queue." << std::endl;
        exit(EXIT_FAILURE);
    }
    
    return _items[_first]; // Returns a const reference
}
