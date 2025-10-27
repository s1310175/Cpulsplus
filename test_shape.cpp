#include <iostream>
#include <memory> 
#include <cmath>
#include "shape.h"
#include "disk.h"
#include "polygon.h"

void test_disk_functionality() {
    std::cout << "--- Disk Test ---" << std::endl;
    
    Disk d1(Point(1.0f, 2.0f), 5.0f);

    std::cout << "Disk Name: " << d1.get_name() << std::endl;
    std::cout << "Disk Area (R=5): " << d1.compute_area() << std::endl;

    std::unique_ptr<Shape> d2_ptr(d1.clone());
    std::cout << "Cloned Disk Area: " << d2_ptr->compute_area() << std::endl;

    std::unique_ptr<Shape> d3_ptr(d1.create());
    std::cout << "Created Disk Area (default): " << d3_ptr->compute_area() << std::endl;
    std::cout << "-----------------" << std::endl;
}

void test_polygon_functionality() {
    std::cout << "--- Polygon Test (Square & Triangle) ---" << std::endl;
    
    // Square (Area = 16.0)
    Point square_points[] = { Point(0.0f, 0.0f), Point(4.0f, 0.0f), Point(4.0f, 4.0f), Point(0.0f, 4.0f) };
    Polygon p1(4, square_points);
    std::cout << "Polygon Name: " << p1.get_name() << std::endl;
    std::cout << "Square Area (4x4): " << p1.compute_area() << std::endl;

    // Triangle (Area = 6.0)
    Point triangle_points[] = { Point(0.0f, 0.0f), Point(4.0f, 0.0f), Point(2.0f, 3.0f) };
    Polygon p_tri(3, triangle_points);
    std::cout << "Triangle Area: " << p_tri.compute_area() << std::endl;

    // Verify cloning
    std::unique_ptr<Shape> p2_ptr(p1.clone());
    std::cout << "Cloned Polygon Area (Square): " << p2_ptr->compute_area() << std::endl;
    
    std::cout << "--------------------------------------" << std::endl;
}

void test_dynamic_polymorphism() {
    std::cout << "--- Dynamic Polymorphism Test ---" << std::endl;

    // Array of base class pointers
    Shape* shapes[2];
    shapes[0] = new Disk(Point(0.0f, 0.0f), 10.0f); // R=10 Disk 

    Point rect_points[] = { Point(0.0f, 0.0f), Point(2.0f, 0.0f), Point(2.0f, 1.0f), Point(0.0f, 1.0f) };
    shapes[1] = new Polygon(4, rect_points); // 2x1 Rectangle 

    // Dynamic dispatch
    for (int i = 0; i < 2; ++i) {
        std::cout << "Shape [" << i << "] Name: " << shapes[i]->get_name() 
                  << ", Area: " << shapes[i]->compute_area() << std::endl;
    }

    // Cleanup
    delete shapes[0];
    delete shapes[1];
    std::cout << "---------------------------------" << std::endl;
}

int main() {
    // Run all tests
    test_disk_functionality();
    test_polygon_functionality();
    test_dynamic_polymorphism();
    return 0;
}