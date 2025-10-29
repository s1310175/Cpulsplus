#include "polygon.h"
#include <cmath>
#include <algorithm>

// Copies vertices from the raw array
void Polygon::copy_vertices(int N, const Point* points) {
    N_ = N;
    vertices_.clear();
    vertices_.reserve(N_);
    for (int i = 0; i < N_; ++i) {
        vertices_.push_back(points[i]);
    }
}

// Constructor (handles validation and copy)
Polygon::Polygon(int N, const Point* points) {
    if (N < 3 || points == nullptr) {
        N_ = 0;
        return;
    }
    copy_vertices(N, points);
}

// Copy constructor
Polygon::Polygon(const Polygon& other)
    : N_(other.N_), vertices_(other.vertices_) {}

std::string Polygon::get_name() const {
    return "polygon";
}

// Area using Shoelace Formula
float Polygon::compute_area() const {
    if (N_ < 3) return 0.0f;

    float sum = 0.0f;
    for (int i = 0; i < N_; ++i) {
        const Point& p_i = vertices_[i];
        const Point& p_next = vertices_[(i + 1) % N_]; // Wrap around to P_0

        sum += (p_i.x * p_next.y - p_i.y * p_next.x);
    }

    return std::abs(sum / 2.0f);
}

Polygon* Polygon::create() const {
    return new Polygon();
}

Polygon* Polygon::clone() const {
    return new Polygon(*this);
}

Polygon::~Polygon() {}
