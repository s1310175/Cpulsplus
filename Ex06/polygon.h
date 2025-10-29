#ifndef POLYGON_H
#define POLYGON_H

#include "shape.h"
#include <vector>

/**
 * @brief Represents a general Polygon. Implements the Shape interface.
 */
class Polygon : public Shape {
private:
    std::vector<Point> vertices_;
    int N_; // Vertex count.

public:
    Polygon(int N, const Point* points);
    Polygon() : N_(0) {}
    Polygon(const Polygon& other);

    // Overrides
    std::string get_name() const override;
    float compute_area() const override;

    // Covariant return
    Polygon* create() const override;
    Polygon* clone() const override;

    virtual ~Polygon() override;

private:
    // Helper for deep copy of vertices
    void copy_vertices(int N, const Point* points);
};

#endif // POLYGON_H
