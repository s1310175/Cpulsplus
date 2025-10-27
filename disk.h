#ifndef DISK_H
#define DISK_H

#include "shape.h"

/**
 * @brief Represents a Disk. Implements the Shape interface.
 */
class Disk : public Shape {
private:
    Point center_;
    float radius_;

public:
    Disk(Point center, float radius);
    Disk(); 
    Disk(const Disk& other);

    // Overrides
    std::string get_name() const override;
    float compute_area() const override;

    // Covariant Return
    Disk* create() const override;
    Disk* clone() const override;

    virtual ~Disk() override;
};

#endif // DISK_H