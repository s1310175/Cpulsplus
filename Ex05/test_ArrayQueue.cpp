// test_ArrayQueue.cpp
#include "ArrayQueue.h"
#include <vector>
#include <stdexcept>
#include <cassert>

using namespace std;

void print_queue_status(const ArrayQueue& q, const string& name) {
    cout << "[" << name << "] Size: " << q.size() 
         << ", Capacity: " << q.allocated_size()
         << (q.empty() ? " (EMPTY)" : "") << endl;
    if (!q.empty()) {
        cout << "   Front item (peek): " << q.peek() << endl;
    }
}

// Function to run a specific test case
void run_test(const string& test_name, void (*test_func)()) {
    cout << "\n--- Starting Test: " << test_name << " ---" << endl;
    try {
        test_func();
        cout << "--- Test Passed: " << test_name << " ---" << endl;
    } catch (const exception& e) {
        cerr << "--- Test FAILED: " << test_name << " ---" << endl;
        cerr << "  Exception caught: " << e.what() << endl;
    } catch (...) {
        cerr << "--- Test FAILED: " << test_name << " ---" << endl;
        cerr << "  Unknown error caught." << endl;
    }
}

// Test Case 1: Basic Enqueue, Dequeue, Peek, and Empty/Size
void test_basic_operations() {
    ArrayQueue q; // Default constructor test
    print_queue_status(q, "q");
    assert(q.empty() && q.size() == 0);

    q.enqueue("Alpha");
    q.enqueue("Beta");
    print_queue_status(q, "q");
    assert(!q.empty() && q.size() == 2);
    assert(q.peek() == "Alpha");

    q.dequeue();
    print_queue_status(q, "q");
    assert(q.size() == 1);
    assert(q.peek() == "Beta");

    q.dequeue();
    print_queue_status(q, "q");
    assert(q.empty() && q.size() == 0);

    // Should handle silent dequeue on empty (due to added check in ArrayQueue.h)
    q.dequeue(); 
    print_queue_status(q, "q");
    assert(q.empty());
}

// Test Case 2: Resizing (Doubling Capacity)
void test_resizing() {
    ArrayQueue q(2); // Start with capacity 2
    print_queue_status(q, "ResizeQueue");
    assert(q.allocated_size() == 2);

    q.enqueue("One");
    q.enqueue("Two");
    print_queue_status(q, "ResizeQueue");
    assert(q.allocated_size() == 2); // Full

    // Enqueue 3rd item - should trigger resize(4)
    q.enqueue("Three");
    cout << "--- Triggered Resize to 4 ---" << endl;
    print_queue_status(q, "ResizeQueue");
    assert(q.allocated_size() == 4);
    assert(q.size() == 3);
    assert(q.peek() == "One");

    q.enqueue("Four");
    q.enqueue("Five");
    print_queue_status(q, "ResizeQueue");
    assert(q.allocated_size() == 4); // Full
    
    // Enqueue 6th item - should trigger resize(8)
    q.enqueue("Six");
    cout << "--- Triggered Resize to 8 ---" << endl;
    print_queue_status(q, "ResizeQueue");
    assert(q.allocated_size() == 8);
    assert(q.size() == 6);
    assert(q.peek() == "One");
}

// Test Case 3: Circular Array (Wrap-around)
void test_wrap_around() {
    ArrayQueue q(4); // Start with capacity 4
    
    // Fill up and dequeue some to move _first/_last
    q.enqueue("A"); // _first=0, _last=1
    q.enqueue("B"); // _last=2
    q.dequeue();    // _first=1
    q.dequeue();    // _first=2
    
    // Current state: size 0, capacity 4, _first=2, _last=2
    
    // Enqueue 1 (should be at index 2)
    q.enqueue("C"); // _last=3
    // Enqueue 2 (should be at index 3)
    q.enqueue("D"); // _last=0 (WRAP!)
    
    cout << "--- Testing Wrap-around ---" << endl;
    print_queue_status(q, "WrapQueue");
    assert(q.size() == 2);
    assert(q.peek() == "C");

    // Enqueue 3 (should be at index 0)
    q.enqueue("E"); // _last=1
    print_queue_status(q, "WrapQueue");
    assert(q.size() == 3);

    // Dequeue C (_first=2 -> 3)
    q.dequeue();
    // Dequeue D (_first=3 -> 0 - WRAP!)
    q.dequeue();
    
    print_queue_status(q, "WrapQueue");
    assert(q.size() == 1);
    assert(q.peek() == "E");
}

// Test Case 4: Shrinking (Halving Capacity)
void test_shrinking() {
    // Start with capacity 8
    ArrayQueue q(8);
    cout << "Initial Capacity: " << q.allocated_size() << endl;

    // Fill to size 7 (Capacity 8)
    for (int i = 0; i < 7; ++i) {
        q.enqueue("Item" + to_string(i));
    }
    print_queue_status(q, "ShrinkQueue");
    assert(q.allocated_size() == 8 && q.size() == 7);

    // Dequeue 5 items. Size becomes 2. 2 is not 8/4. No shrink.
    for (int i = 0; i < 5; ++i) {
        q.dequeue();
    }
    print_queue_status(q, "ShrinkQueue");
    assert(q.allocated_size() == 8 && q.size() == 2);

    // Dequeue 1 more item. Size becomes 1. 1 is 8/4. Shrink to 4.
    q.dequeue(); 
    cout << "--- Triggered Shrink to 4 (size 1 is 8/4) ---" << endl;
    print_queue_status(q, "ShrinkQueue");
    assert(q.allocated_size() == 4 && q.size() == 1);
    assert(q.peek() == "Item6");
    
    // Dequeue 1 more item. Size becomes 0. No shrink.
    q.dequeue();
    print_queue_status(q, "ShrinkQueue");
    assert(q.allocated_size() == 4 && q.size() == 0);
    
    // Enqueue 1 item.
    q.enqueue("Final");
    print_queue_status(q, "ShrinkQueue");
    assert(q.allocated_size() == 4 && q.size() == 1);
}


int main(void) {
    cout << "Starting ArrayQueue Test Suite..." << endl;
    
    run_test("Basic Operations (Default Constructor)", test_basic_operations);
    run_test("Resizing (Doubling)", test_resizing);
    run_test("Circular Array (Wrap-around)", test_wrap_around);
    run_test("Shrinking (Halving)", test_shrinking);

    return 0;
}
