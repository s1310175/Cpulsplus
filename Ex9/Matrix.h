#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
#include <stdexcept>
#include <type_traits> // Using type traits

// --- C++11 Compatible Helper Functions for Type Trait Selection ---

// 1. Get Epsilon value

// Overload for non-floating point types (returns 0)
template <typename T, typename std::enable_if<!std::is_floating_point<T>::value, int>::type = 0>
T get_epsilon() { return T(0); }

// Overload for floating point types (returns 1e-6)
template <typename T, typename std::enable_if<std::is_floating_point<T>::value, int>::type = 0>
T get_epsilon() { return 1e-6; }

// 2. Almost Equal Comparison 

// Overload for non-floating point types (performs strict equality)
template <typename T, typename std::enable_if<!std::is_floating_point<T>::value, int>::type = 0>
bool almost_equal(T a, T b) { return a == b; }

// Overload for floating point types (allows error tolerance)
template <typename T, typename std::enable_if<std::is_floating_point<T>::value, int>::type = 0>
bool almost_equal(T a, T b) { return std::fabs(a - b) < get_epsilon<T>(); }

// --- General Template Class: Matrix<T, N> (for N != 2) ---

template <typename T, size_t N>
class Matrix {
private:
    std::vector<T> m; // Matrix elements (Row-major)
    size_t index(size_t i, size_t j) const { return i * N + j; } // 1D index calculation helper

public:
    Matrix() : m(N * N) { // Initialize as Identity Matrix I
        for (size_t i = 0; i < N; ++i) { m[index(i, i)] = T(1); }
    }

    Matrix(const T* array) : m(N * N) { // Initialize from column-major array
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < N; ++j) { m[index(i, j)] = array[j * N + i]; }
        }
    }

    T& operator()(size_t i, size_t j) { // Element access (Non-const)
        if (i >= N || j >= N) throw std::out_of_range("Index is out of range.");
        return m[index(i, j)];
    }
    const T& operator()(size_t i, size_t j) const { // Element access (Const)
        if (i >= N || j >= N) throw std::out_of_range("Index is out of range.");
        return m[index(i, j)];
    }

    Matrix<T, N> operator-() const { // Unary minus: Inverts the sign of all elements
        Matrix<T, N> result;
        for (size_t i = 0; i < N * N; ++i) { result.m[i] = -m[i]; }
        return result;
    }

    // --- Compound assignment operators implemented as member functions ---
    Matrix<T, N>& operator+=(const Matrix<T, N>& other) { // Compound addition assignment
        for (size_t i = 0; i < N * N; ++i) { m[i] += other.m[i]; }
        return *this; // Return *this for chaining
    }

    Matrix<T, N>& operator-=(const Matrix<T, N>& other) { // Compound subtraction assignment
        *this += (-other); // Utilize += and unary minus
        return *this;
    }

    Matrix<T, N>& operator*=(const Matrix<T, N>& other) { // Compound multiplication assignment (Matrix product)
        Matrix<T, N> temp = *this; // Need a copy to avoid overwriting elements during calculation
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < N; ++j) {
                T sum = T(0);
                for (size_t k = 0; k < N; ++k) { sum += temp.m[temp.index(i, k)] * other.m[other.index(k, j)]; } // As per matrix multiplication definition
                m[index(i, j)] = sum;
            }
        }
        return *this;
    }

    // --- Friend functions (Definition of non-member operators) ---
    friend Matrix<T, N> operator+(const Matrix<T, N>& a, const Matrix<T, N>& b) {
        Matrix<T, N> result = a; result += b; return result;
    }
    friend Matrix<T, N> operator-(const Matrix<T, N>& a, const Matrix<T, N>& b) {
        Matrix<T, N> result = a; result -= b; return result;
    }
    friend Matrix<T, N> operator*(const Matrix<T, N>& a, const Matrix<T, N>& b) {
        Matrix<T, N> result = a; result *= b; return result;
    }
    friend bool operator==(const Matrix<T, N>& a, const Matrix<T, N>& b) { // Equality comparison supporting floating-point types
        for (size_t i = 0; i < N * N; ++i) { if (!almost_equal(a.m[i], b.m[i])) { return false; } }
        return true;
    }
    friend bool operator!=(const Matrix<T, N>& a, const Matrix<T, N>& b) { return !(a == b); }
    friend std::ostream& operator<<(std::ostream& os, const Matrix<T, N>& m) { // Stream insertion operator
        os << std::fixed << std::setprecision(2);
        for (size_t i = 0; i < N; ++i) {
            os << "|";
            for (size_t j = 0; j < N; ++j) { os << "\t" << m.m[m.index(i, j)]; }
            os << "\t|" << (i < N - 1 ? "\n" : ""); // Newline except for the last row
        }
        return os;
    }
};

// --- Partial Specialization: Matrix<T, 2> (Optimized for N=2) ---

template <typename T>
class Matrix<T, 2> {
private:
    T m00, m01, m10, m11; // Hold elements using individual members for loop unrolling optimization

public:
    Matrix() : m00(T(1)), m01(T(0)), m10(T(0)), m11(T(1)) {} // Identity Matrix I

    Matrix(const T* array) { // Initialize from column-major array
        m00 = array[0]; m10 = array[1]; // Column 1
        m01 = array[2]; m11 = array[3]; // Column 2
    }
    
private:
    Matrix(T a, T b, T c, T d) : m00(a), m01(b), m10(c), m11(d) {} // Helper constructor for internal operations
public:

    // Element Access: operator() (optimized via if/else)
    T& operator()(size_t i, size_t j) {
        if (i == 0 && j == 0) return m00;
        if (i == 0 && j == 1) return m01;
        if (i == 1 && j == 0) return m10;
        if (i == 1 && j == 1) return m11;
        throw std::out_of_range("Index out of range.");
    }
    const T& operator()(size_t i, size_t j) const { // Element access (const)
        if (i == 0 && j == 0) return m00;
        if (i == 0 && j == 1) return m01;
        if (i == 1 && j == 0) return m10;
        if (i == 1 && j == 1) return m11;
        throw std::out_of_range("Index out of range.");
    }

    Matrix<T, 2> operator-() const { // Unary minus (Unrolled for optimization)
        return Matrix<T, 2>(-m00, -m01, -m10, -m11);
    }

    Matrix<T, 2>& operator+=(const Matrix<T, 2>& other) { // Compound addition assignment (Unrolled)
        m00 += other.m00; m01 += other.m01;
        m10 += other.m10; m11 += other.m11;
        return *this;
    }

    Matrix<T, 2>& operator-=(const Matrix<T, 2>& other) { // Compound subtraction assignment (Unrolled)
        m00 -= other.m00; m01 -= other.m01;
        m10 -= other.m10; m11 -= other.m11;
        return *this;
    }

    Matrix<T, 2>& operator*=(const Matrix<T, 2>& B) { // Compound multiplication assignment (Matrix product, unrolled for max speed!)
        T a = m00, b = m01, c = m10, d = m11; // Backup current values before modification
        // Matrix multiplication calculation
        m00 = a * B.m00 + b * B.m10;
        m01 = a * B.m01 + b * B.m11;
        m10 = c * B.m00 + d * B.m10;
        m11 = c * B.m01 + d * B.m11;
        return *this;
    }

    // --- Friend functions (Definition of non-member operators) ---
    friend Matrix<T, 2> operator+(const Matrix<T, 2>& a, const Matrix<T, 2>& b) {
        Matrix<T, 2> result = a; result += b; return result;
    }
    friend Matrix<T, 2> operator-(const Matrix<T, 2>& a, const Matrix<T, 2>& b) {
        Matrix<T, 2> result = a; result -= b; return result;
    }
    friend Matrix<T, 2> operator*(const Matrix<T, 2>& a, const Matrix<T, 2>& b) {
        Matrix<T, 2> result = a; result *= b; return result;
    }
    friend bool operator==(const Matrix<T, 2>& a, const Matrix<T, 2>& b) { // Compare 4 elements individually with almost_equal
        return almost_equal(a.m00, b.m00) && almost_equal(a.m01, b.m01) &&
               almost_equal(a.m10, b.m10) && almost_equal(a.m11, b.m11);
    }
    friend bool operator!=(const Matrix<T, 2>& a, const Matrix<T, 2>& b) { return !(a == b); }
    friend std::ostream& operator<<(std::ostream& os, const Matrix<T, 2>& m) { // Stream insertion operator
        os << std::fixed << std::setprecision(2);
        os << "|\t" << m.m00 << "\t" << m.m01 << "\t|" << "\n";
        os << "|\t" << m.m10 << "\t" << m.m11 << "\t|";
        return os;
    }
};

#endif // MATRIX_H
