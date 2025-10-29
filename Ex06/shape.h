#ifndef SHAPE_H
#define SHAPE_H

#include <string>

/**
 * @brief 2D Point structure. Used by all shape classes.
 */
struct Point {
    float x;
    float y;
    Point() : x(0.0f), y(0.0f) {}
    Point(float px, float py) : x(px), y(py) {}
};

/**
 * @brief Abstract base class (Interface) for 2D shapes.
 */
class Shape {
public:
    virtual std::string get_name() const = 0;
    virtual float compute_area() const = 0;
    
    // Factory methods (covariant return type required for derived classes)
    virtual Shape* create() const = 0; 
    virtual Shape* clone() const = 0; 

    // Essential virtual destructor
    virtual ~Shape() {}
};

#endif // SHAPE_H
