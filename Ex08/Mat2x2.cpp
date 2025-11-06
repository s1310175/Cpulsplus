#include "Mat2x2.h"
#include <iomanip>

bool almost_equal(float a, float b) {
    return std::fabs(a - b) < EPSILON;
}

Mat2x2::Mat2x2() {
    m[0] = 1.0f; m[1] = 0.0f;
    m[2] = 0.0f; m[3] = 1.0f;
}

Mat2x2::Mat2x2(const float array[4]) {
    // Map column-major input to row-major internal storage
    m[0] = array[0];
    m[1] = array[2];
    m[2] = array[1];
    m[3] = array[3];
}

float& Mat2x2::operator()(int i, int j) {
    return m[i * 2 + j];
}

const float& Mat2x2::operator()(int i, int j) const {
    return m[i * 2 + j];
}

Mat2x2 Mat2x2::operator-() const {
    Mat2x2 result;
    for (int i = 0; i < 4; ++i) {
        result.m[i] = -m[i];
    }
    return result;
}

Mat2x2& Mat2x2::operator+=(const Mat2x2& other) {
    for (int i = 0; i < 4; ++i) {
        m[i] += other.m[i];
    }
    return *this;
}

Mat2x2& Mat2x2::operator-=(const Mat2x2& other) {
    *this += (-other);
    return *this;
}

Mat2x2& Mat2x2::operator*=(const Mat2x2& other) {
    Mat2x2 temp = *this;

    // Matrix multiplication
    m[0] = temp.m[0] * other.m[0] + temp.m[1] * other.m[2];
    m[1] = temp.m[0] * other.m[1] + temp.m[1] * other.m[3];
    m[2] = temp.m[2] * other.m[0] + temp.m[3] * other.m[2];
    m[3] = temp.m[2] * other.m[1] + temp.m[3] * other.m[3];
    
    return *this;
}

Mat2x2 operator+(const Mat2x2& a, const Mat2x2& b) {
    Mat2x2 result = a;
    result += b;
    return result;
}

Mat2x2 operator-(const Mat2x2& a, const Mat2x2& b) {
    Mat2x2 result = a;
    result -= b;
    return result;
}

Mat2x2 operator*(const Mat2x2& a, const Mat2x2& b) {
    Mat2x2 result = a;
    result *= b;
    return result;
}

bool operator==(const Mat2x2& a, const Mat2x2& b) {
    for (int i = 0; i < 4; ++i) {
        if (!almost_equal(a.m[i], b.m[i])) {
            return false;
        }
    }
    return true;
}

bool operator!=(const Mat2x2& a, const Mat2x2& b) {
    return !(a == b);
}

std::ostream& operator<<(std::ostream& os, const Mat2x2& m) {
    os << std::fixed << std::setprecision(2);
    
    // Output row 0 and row 1
    os << "|\t" << m.m[0] << "\t" << m.m[1] << "\t|" << std::endl;
    os << "|\t" << m.m[2] << "\t" << m.m[3] << "\t|";
    
    return os;
}
