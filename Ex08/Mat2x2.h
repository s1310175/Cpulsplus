#ifndef MAT2X2_H
#define MAT2X2_H

#include <iostream>
#include <cmath>

const float EPSILON = 1e-6f;

bool almost_equal(float a, float b);

class Mat2x2 {
private:
    /* Row-major order: m00, m01, m10, m11 */
    float m[4];

public:
    Mat2x2(); // Identity Matrix
    Mat2x2(const float array[4]); // Column-major input

    // Compound assignment operators
    Mat2x2& operator+=(const Mat2x2& other);
    Mat2x2& operator-=(const Mat2x2& other);
    Mat2x2& operator*=(const Mat2x2& other);

    Mat2x2 operator-() const; // Unary minus

    // Element access operator
    float& operator()(int i, int j);
    const float& operator()(int i, int j) const;

    // Friend functions
    friend std::ostream& operator<<(std::ostream& os, const Mat2x2& m);
    friend bool operator==(const Mat2x2& a, const Mat2x2& b);
};

// Binary arithmetic operators
Mat2x2 operator+(const Mat2x2& a, const Mat2x2& b);
Mat2x2 operator-(const Mat2x2& a, const Mat2x2& b);
Mat2x2 operator*(const Mat2x2& a, const Mat2x2& b);

// Comparison operator
bool operator!=(const Mat2x2& a, const Mat2x2& b);

#endif // MAT2X2_H
