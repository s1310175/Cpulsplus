#include <iostream>
#include <vector>
#include <list>
 
template <class FwdIt, class T_X>
typename FwdIt::value_type poly_eval(FwdIt first, FwdIt last, const T_X& x) {
    // Handle the empty coefficient list
    if (first == last) {
        return typename FwdIt::value_type(); 
    }

    // Horner's rule initialization
    typename FwdIt::value_type result = *first;
    ++first; 

    // Horner's rule iteration
    while (first != last) {
        result = (result * x) + *first;
        ++first;
    }

    return result;
}

// --- Test Implementation ---
void run_tests() {
    std::cout << "--- poly_eval Tests ---" << std::endl;

    // Example: P(x) = 4x^4 + 7x^3 - x^2 + 27x - 3
    std::vector<int> coeffs = {4, 7, -1, 27, -3};
    int x_val = 2; 

    // Test 1: vector<int> (Expected: 167)
    int result1 = poly_eval(coeffs.begin(), coeffs.end(), x_val);
    std::cout << "P(x) = 4x^4 + 7x^3 - x^2 + 27x - 3, x = " << x_val << std::endl;
    std::cout << "Result (vector<int>): " << result1 << " (Expected: 167)" << std::endl;

    // Test 2: list<double> (Expected: 6.5)
    std::list<double> coeffs_double = {1.0, 0.0, -2.5}; // Q(x) = x^2 - 2.5
    double x_val_double = 3.0; 
    double result2 = poly_eval(coeffs_double.begin(), coeffs_double.end(), x_val_double);
    std::cout << "\nQ(x) = 1.0x^2 - 2.5, x = " << x_val_double << std::endl;
    std::cout << "Result (list<double>): " << result2 << " (Expected: 6.5)" << std::endl;

    // Test 3: Constant polynomial (Expected: 5)
    std::vector<int> coeffs_const = {5};
    int result3 = poly_eval(coeffs_const.begin(), coeffs_const.end(), 100);
    std::cout << "\nR(x) = 5, x = 100" << std::endl;
    std::cout << "Result (Constant): " << result3 << " (Expected: 5)" << std::endl;
}

int main() {
    run_tests();
    return 0;
}
