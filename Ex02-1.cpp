#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <cstdlib> // For exit()

// Define a struct for representing three dimensional points with integral coordinates 
struct Point {
    int x; // X-coordinate
    int y; // Y-coordinate
    int z; // Z-coordinate
};


// Class for representing a queue implemented using a circular array
class Queue {
public:
 // Constructor: It allocates memory for an array of size max_size
 Queue(int max_size=1024) : _num_items(0), _max_size(max_size), 
   _first(0), _last(0), _items(new Point[max_size]) {}

 ~Queue() { delete[] _items; }

 // Prevent copy and move operations
 Queue(const Queue&) = delete;
 Queue& operator=(const Queue&) = delete;
 Queue(Queue&&) = delete;
 Queue& operator=(Queue&&) = delete;


 // Interface
 
 // Check whether the queue is empty 
 bool empty();

 // Check whether the queue is full
 bool full();

 // Return the number of elements in the queue 
 int size();

 // Insert an element in the queue (Enqueue)
 // Print an error message on std::cerr and exit in case of overflow
 void enqueue(Point);

 // Remove an element from the queue (Dequeue)
 // Print an error message on std::cerr and exit in case of underflow
 void dequeue();

 // Access the least recently added element (Peek)
 // Print an error message on std::cerr and exit in case of underflow
 Point peek();

private:
  int _num_items; // number of elements currently in the queue
  int _max_size; // capacity of the fixed-size queue
  int _first; // index to the first element of the queue (Head)
  int _last; // index of the next available slot (Tail)
  Point* _items; // data container (circular array)

};
#endif 
