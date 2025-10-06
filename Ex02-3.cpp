#include "Ex02-1.cpp" // Include the header definition
#include <iostream>

// Helper function to print a Point object.
void print_point(const Point& p) {
    std::cout << "(" << p.x << ", " << p.y << ", " << p.z << ")";
}

// Main function to test the Queue implementation.
int main(void) {
    std::cout << "--- Queue Implementation Test ---" << std::endl;
    
    const int TEST_SIZE = 4;
    Queue q(TEST_SIZE); 
    std::cout << "Queue initialized with max size: " << TEST_SIZE << std::endl;
    std::cout << "Initial size: " << q.size() << ", Empty: " << (q.empty() ? "Yes" : "No") << std::endl;
    
    // 1. Enqueue points P1, P2, P3
    Point p1 = {10, 100, 1000};
    Point p2 = {20, 200, 2000};
    Point p3 = {30, 300, 3000};
    
    q.enqueue(p1);
    q.enqueue(p2);
    q.enqueue(p3);
    
    std::cout << "\n--- 1. Enqueue Test ---" << std::endl;
    std::cout << "Current size: " << q.size() << " (Expected: 3)" << std::endl;
    std::cout << "Front element (Expected P1): "; print_point(q.peek()); std::cout << std::endl;
    
    // 2. Dequeue and check FIFO order
    std::cout << "\n--- 2. Dequeue and FIFO Check ---" << std::endl;
    std::cout << "Dequeuing item 1: "; print_point(q.peek()); q.dequeue(); std::cout << std::endl; 
    std::cout << "Current size: " << q.size() << " (Expected: 2)" << std::endl;
    std::cout << "New front (Expected P2): "; print_point(q.peek()); std::cout << std::endl;
    
    // 3. Test circular buffer behavior by adding more elements (P4, P5)
    std::cout << "\n--- 3. Circular Buffer & Full Check ---" << std::endl;
    Point p4 = {40, 400, 4000};
    Point p5 = {50, 500, 5000};
    
    q.enqueue(p4); // Size 3
    q.enqueue(p5); // Size 4 (FULL)
    
    std::cout << "P4 and P5 enqueued. Current size: " << q.size() << " (Expected: 4)" << std::endl;
    std::cout << "Is Full: " << (q.full() ? "Yes" : "No") << " (Expected: Yes)" << std::endl;
    std::cout << "Front element (Expected P2): "; print_point(q.peek()); std::cout << std::endl;

    // 4. Empty the queue
    std::cout << "\n--- 4. Empty Queue ---" << std::endl;
    std::cout << "Dequeuing all elements in order (P2, P3, P4, P5):" << std::endl;
    
    for (int i = 0; i < TEST_SIZE; ++i) {
        std::cout << "  Item " << i + 1 << ": "; print_point(q.peek()); 
        q.dequeue();
        std::cout << std::endl;
    }
    
    std::cout << "Final size: " << q.size() << ", Empty: " << (q.empty() ? "Yes" : "No") << std::endl;

    std::cout << "\nAll normal operations tests completed successfully." << std::endl;
    
    return 0;
}
