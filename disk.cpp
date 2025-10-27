#include "disk.h"
#include <cmath> 

#ifndef M_PI
#define M_PI 3.14159265358979323846f
#endif

// Main constructor
Disk::Disk(Point center, float radius)
    : center_(center), radius_(radius) {}

// Default constructor (required for create())
Disk::Disk()
    : center_(0.0f, 0.0f), radius_(0.0f) {}

// Copy constructor
Disk::Disk(const Disk& other)
    : center_(other.center_), radius_(other.radius_) {}

std::string Disk::get_name() const {
    return "disk";
}

// Area = pi * r^2
float Disk::compute_area() const {
    return M_PI * radius_ * radius_;
}

// Factory (Covariant)
Disk* Disk::create() const {
    return new Disk();
}

// Cloner (Covariant)
Disk* Disk::clone() const {
    return new Disk(*this);
}

// Destructor
Disk::~Disk() {}