// test_ArrayQueue.cpp
#include "ArrayQueue.h"
#include <vector>
#include <stdexcept>
#include <cassert>
#include <utility> 

using namespace std;

// Helper function to display the current state of the queue
void print_queue_status(const ArrayQueue& q, const string& name) {
    cout << "[" << name << "] Size: " << q.size() 
         << ", Capacity: " << q.allocated_size()
         << (q.empty() ? " (EMPTY)" : "") << endl;
    if (!q.empty()) {
        cout << "   Front item (peek): " << q.peek() << endl;
    }
}

// Wrapper to run a specific test function and catch/display exceptions
void run_test(const string& test_name, void (*test_func)()) {
    cout << "\n--- Starting Test: " << test_name << " ---" << endl;
    try {
        test_func();
        cout << "--- Test Passed: " << test_name << " ---" << endl;
    } catch (const exception& e) {
        cerr << "--- Test FAILED: " << test_name << " ---" << endl;
        cerr << "   Exception caught: " << e.what() << endl;
    } catch (...) {
        cerr << "--- Test FAILED: " << test_name << " ---" << endl;
        cerr << "   Unknown error caught." << endl;
    }
}

// --- Question 1 Tests ---

// Test basic Enqueue, Dequeue, and Peek operations
void test_basic_operations() {
    ArrayQueue q; 
    assert(q.empty() && q.size() == 0);

    q.enqueue("Alpha");
    q.enqueue("Beta");
    assert(q.peek() == "Alpha");

    q.dequeue();
    assert(q.peek() == "Beta");

    q.dequeue();
    assert(q.empty());

    q.dequeue(); // Test dequeuing from an empty queue (should print error/no crash)
    assert(q.empty());
}

// Test capacity doubling upon reaching limit
void test_resizing() {
    ArrayQueue q(2); 

    q.enqueue("One");
    q.enqueue("Two");
    
    // Add 3rd item -> Should resize from 2 to 4
    q.enqueue("Three");
    cout << "--- Triggered Resize to 4 ---" << endl;
    assert(q.allocated_size() == 4); 

    q.enqueue("Four"); 
    q.enqueue("Five"); // Add 5th item -> Should resize from 4 to 8
    assert(q.allocated_size() == 8); 
    
    q.enqueue("Six"); 
    assert(q.allocated_size() == 8);
    assert(q.peek() == "One");
}

// Test wrap-around behavior of indices in the circular array
void test_wrap_around() {
    ArrayQueue q(4); 
    
    // Move indices to start wrap-around test
    q.enqueue("A"); 
    q.enqueue("B"); 
    q.dequeue(); 
    q.dequeue(); 
    
    q.enqueue("C"); // Index 2
    q.enqueue("D"); // Index 3 -> next_last = 0 (Wrapped!)
    
    cout << "--- Testing Wrap-around ---" << endl;
    assert(q.peek() == "C");

    q.enqueue("E"); // Index 0
    q.dequeue(); // next_first = 3
    q.dequeue(); // next_first = 0 (Wrapped!)
    
    assert(q.peek() == "E");
}

// Test capacity halving when usage is low
void test_shrinking() {
    ArrayQueue q(8);
    cout << "Initial Capacity: " << q.allocated_size() << endl;

    // Fill to size 7
    for (int i = 0; i < 7; ++i) {
        q.enqueue("Item" + to_string(i));
    }
    
    // Dequeue 5 times -> Size becomes 2. 
    // Since Size (2) == Capacity (8) / 4, shrinking to 4 is triggered here.
    for (int i = 0; i < 5; ++i) {
        q.dequeue();
    }
    
    // Confirm capacity reduced from 8 to 4, size is 2
    assert(q.allocated_size() == 4 && q.size() == 2); 

    // Dequeue 1 more time -> Size becomes 1. 
    // Capacity is 4, so no further shrinking occurs (_allocated_size > 4 check fails).
    q.dequeue(); 
    cout << "--- Shrink not triggered (Capacity is 4) ---" << endl;

    assert(q.allocated_size() == 4 && q.size() == 1);
    
    q.dequeue(); // Size 0
    assert(q.allocated_size() == 4 && q.size() == 0);
}

// --- Question 2 Tests (Copy Semantics) ---

// Test the deep copy behavior of the copy constructor
void test_copy_constructor() {
    ArrayQueue q1(4);
    q1.enqueue("One"); q1.enqueue("Two"); q1.dequeue(); 
    q1.enqueue("Three"); q1.enqueue("Four"); 
    
    ArrayQueue q2 = q1; // Call copy constructor

    // Verify q1 and q2 match initially
    assert(q1.size() == q2.size());
    
    // Modify q1 and verify q2 is independent (deep copy check)
    q1.dequeue(); 
    q1.enqueue("Five");
    cout << "--- q1 modified ---" << endl;
    
    assert(q1.peek() == "Three");
    assert(q2.peek() == "Two"); // q2 must remain unchanged
}

// Test the copy assignment operator, including self-assignment
void test_copy_assignment() {
    ArrayQueue q1(2);
    q1.enqueue("A"); q1.enqueue("B");
    ArrayQueue q2(10);
    q2.enqueue("Y"); 

    q2 = q1; // Copy assignment

    // Verify deep copy: modify q1 and check q2's independence
    q1.dequeue(); 
    cout << "--- q1 modified ---" << endl;
    assert(q2.peek() == "A"); 
    
    // Test self-assignment
    q1 = q1; 
    cout << "--- q1 = q1 self-assignment done ---" << endl;
    assert(q1.peek() == "B"); 
}

// --- Question 3 Tests (Move Semantics) ---

// Test the transfer of ownership using the move constructor
void test_move_constructor() {
    ArrayQueue q1(8);
    q1.enqueue("MoveMe1"); q1.enqueue("MoveMe2"); q1.dequeue(); 
    int original_capacity = q1.allocated_size();
    
    ArrayQueue q2 = std::move(q1); // Call move constructor
    cout << "--- q2 = std::move(q1) done ---" << endl;

    // Verify q2 has the data and capacity
    assert(q2.size() == 1);
    assert(q2.peek() == "MoveMe2");
    assert(q2.allocated_size() == original_capacity); 

    // Verify q1 is empty and reusable
    assert(q1.empty());
    q1.enqueue("NewData"); 
    assert(q1.peek() == "NewData");
}

// Test the transfer of ownership using the move assignment operator
void test_move_assignment() {
    ArrayQueue q1(8);
    q1.enqueue("SourceA"); q1.enqueue("SourceB");
    ArrayQueue q2(4);
    q2.enqueue("TargetX");
    
    q2 = std::move(q1); // Move assignment
    cout << "--- q2 = std::move(q1) assignment done ---" << endl;

    // Verify q2 received the resources and q1 is nulled
    assert(q2.size() == 2);
    assert(q2.peek() == "SourceA"); 
    assert(q1.empty());
    
    // Test self-move assignment
    q2 = std::move(q2); 
    cout << "--- q2 = std::move(q2) self-move-assignment done ---" << endl;
    assert(q2.size() == 2); 
    assert(q2.peek() == "SourceA");
}


int main(void) {
    cout << "Starting ArrayQueue Test Suite..." << endl;
    
    run_test("Basic Operations (Default Constructor)", test_basic_operations);
    run_test("Resizing (Doubling)", test_resizing);
    run_test("Circular Array (Wrap-around)", test_wrap_around);
    run_test("Shrinking (Halving)", test_shrinking);

    run_test("Copy Constructor (Deep Copy)", test_copy_constructor);
    run_test("Copy Assignment Operator (Deep Copy)", test_copy_assignment);

    run_test("Move Constructor (Transfer Ownership)", test_move_constructor);
    run_test("Move Assignment Operator (Transfer Ownership)", test_move_assignment);

    return 0;
}
