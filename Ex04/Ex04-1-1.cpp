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
 // Does not modify object -> const member function
 bool empty() const;

 // Check whether the queue is full
 // Does not modify object -> const member function
 bool full() const;

 // Return the number of elements in the queue 
 // Does not modify object -> const member function
 int size() const;

 // Insert an element in the queue (Enqueue)
 // Takes a const reference to avoid copy and ensure argument isn't modified
 // Modifies object -> NOT const
 void enqueue(const Point& p);

 // Remove an element from the queue (Dequeue)
 // Modifies object -> NOT const
 void dequeue();

 // Access the least recently added element (Peek)
 // Does not modify object -> const member function
 // Also returns a const Point& for safety (prevents external modification of queue contents via the return value)
 const Point& peek() const;

private:
  int _num_items; // number of elements currently in the queue
  int _max_size; // capacity of the fixed-size queue
  int _first; // index to the first element of the queue (Head)
  int _last; // index of the next available slot (Tail)
  Point* _items; // data container (circular array)

};
#endif 
