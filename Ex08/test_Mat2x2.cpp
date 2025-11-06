#include "Mat2x2.h"
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

void print_test_result(const string& test_name, bool result) {
    cout << "[" << (result ? "OK" : "FAIL") << "] " << test_name << endl;
}

int main() {
    cout << "--- Mat2x2 Operator Overloading Test Suite ---" << endl;
    cout << "Floating Point Epsilon (EPSILON): " << EPSILON << endl << endl;

    float a_coeffs[] = {1.0f, 3.0f, 2.0f, 4.0f};
    float b_coeffs[] = {5.0f, 7.0f, 6.0f, 8.0f};

    Mat2x2 A(a_coeffs);
    Mat2x2 B(b_coeffs);
    Mat2x2 I;

    cout << "Initial Matrices:" << endl;
    cout << "Matrix A:\n" << A << endl;
    cout << "Matrix B:\n" << B << endl;
    cout << "Identity Matrix I:\n" << I << endl << endl;

    // --- Section 1: Basic Functionality ---
    Mat2x2 I_copy;
    print_test_result("T1: Default Constructor (Identity) Verification", I == I_copy);

    bool t2_check = almost_equal(A(0, 0), 1.0f) && almost_equal(A(1, 1), 4.0f);
    print_test_result("T2: Element Access A(0,0) & A(1,1)", t2_check);
    
    A(0, 0) = 9.0f;
    bool t2_mod = almost_equal(A(0, 0), 9.0f);
    print_test_result("T2_mod: Element Writing Verification", t2_mod);
    A(0, 0) = 1.0f;

    Mat2x2 C = -A;
    float expected_minus_a[] = {-1.0f, -3.0f, -2.0f, -4.0f};
    Mat2x2 Expected_MinusA(expected_minus_a);
    print_test_result("T3: Unary Minus (-A) Verification", C == Expected_MinusA);
    cout << endl;

    // --- Section 2: Binary Operators ---
    C = A + B;
    float expected_add[] = {6.0f, 10.0f, 8.0f, 12.0f};
    Mat2x2 Expected_Add(expected_add);
    print_test_result("T4: Addition (A + B) Verification", C == Expected_Add);

    C = A - B;
    float expected_sub[] = {-4.0f, -4.0f, -4.0f, -4.0f};
    Mat2x2 Expected_Sub(expected_sub);
    print_test_result("T5: Subtraction (A - B) Verification", C == Expected_Sub);

    C = A * B;
    float expected_mul[] = {19.0f, 43.0f, 22.0f, 50.0f};
    Mat2x2 Expected_Mul(expected_mul);
    print_test_result("T8: Matrix Multiplication (A * B) Verification", C == Expected_Mul);

    Mat2x2 AI = A * I;
    print_test_result("T11: A * I == A Verification", AI == A);
    cout << endl;

    // --- Section 3: Compound Assignment Operators ---
    Mat2x2 A_copy1 = A;
    A_copy1 += B;
    print_test_result("T6: Compound Addition (A += B) Verification", A_copy1 == Expected_Add);

    Mat2x2 A_copy2 = A;
    A_copy2 -= B;
    print_test_result("T7: Compound Subtraction (A -= B) Verification", A_copy2 == Expected_Sub);

    Mat2x2 A_copy3 = A;
    A_copy3 *= B;
    print_test_result("T9: Compound Multiplication (A *= B) Verification", A_copy3 == Expected_Mul);
    cout << endl;

    // --- Section 4: Comparison and Stream ---
    print_test_result("T10: Inequality Comparison (A != B) Verification", A != B);

    cout << "\n[T12: Stream Insertion Operator (Manual Inspection Required)]" << endl;
    cout << "------------------------------------------" << endl;
    cout << "Matrix A:\n" << A << endl;
    cout << "\nMatrix I:\n" << I << endl;
    cout << "------------------------------------------" << endl;
    print_test_result("T12: Stream Insertion Operator", true);

    return 0;
}
