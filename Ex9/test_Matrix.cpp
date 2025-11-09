#include "Matrix.h"
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

// Helper function to print test results
template <typename T>
void print_test_result(const string& test_name, bool result, T expected, T actual) {
    cout << "[" << (result ? "OK" : "FAIL") << "] " << test_name;
    if (!result) {
        cout << " (Expected: " << expected << ", Actual: " << actual << ")"; // Output expected vs actual on failure
    }
    cout << endl;
}

// Test function for N x N matrix (Verifying the general template)
void test_N3_matrix() {
    cout << "\n=== Testing Matrix<float, 3> (General Template) ===" << endl;

    // Coefficients for a 3x3 matrix (Column-major)
    float a_coeffs[] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f};
    
    Matrix<float, 3> A(a_coeffs);
    Matrix<float, 3> I; // Identity Matrix

    cout << "Matrix A:\n" << A << endl;
    cout << "Identity Matrix I:\n" << I << endl;

    // T1: Element access
    print_test_result("T1: Element Access A(1, 1)", almost_equal(A(1, 1), 5.0f), 5.0f, A(1, 1));
    
    // T2-T3: Addition A + I
    Matrix<float, 3> B = A + I;
    print_test_result("T2: Addition B(0, 0)", almost_equal(B(0, 0), 2.0f), 2.0f, B(0, 0));
    print_test_result("T3: Addition B(0, 1)", almost_equal(B(0, 1), 4.0f), 4.0f, B(0, 1));

    // T4: Multiplication A * I (Verify that matrix multiplication results in A)
    Matrix<float, 3> C = A * I;
    print_test_result("T4: Multiplication A * I == A", C == A, 1, 1);
}

// Test function for 2 x 2 matrix (Verifying the partial specialization)
void test_N2_matrix() {
    cout << "\n=== Testing Matrix<int, 2> (Partial Specialization, Unrolled Loops) ===" << endl;
    
    // Coefficients for 2x2 matrix (Column-major)
    int a_coeffs[] = {1, 3, 2, 4};
    int b_coeffs[] = {5, 7, 6, 8};

    Matrix<int, 2> A(a_coeffs);
    Matrix<int, 2> B(b_coeffs);

    cout << "Matrix A (int):\n" << A << endl;
    cout << "Matrix B (int):\n" << B << endl;

    // T5: Addition (Unrolled loop check)
    Matrix<int, 2> C = A + B;
    print_test_result("T5: Addition C(1, 0)", C(1, 0) == 10, 10, C(1, 0)); 

    // T6: Compound subtraction assignment (Unrolled loop check)
    Matrix<int, 2> A_copy = A;
    A_copy -= B;
    print_test_result("T6: Compound Subtraction A_copy(0, 1)", A_copy(0, 1) == -4, -4, A_copy(0, 1)); 

    // T7-T8: Multiplication (Unrolled loop check)
    C = A * B;
    print_test_result("T7: Multiplication C(0, 0)", C(0, 0) == 19, 19, C(0, 0));
    print_test_result("T8: Multiplication C(1, 1)", C(1, 1) == 50, 50, C(1, 1));
}

int main() {
    test_N3_matrix(); // First the general case
    test_N2_matrix(); // Then the optimized N=2 case

    cout << "\nAll tests completed." << endl;
    return 0;
}
