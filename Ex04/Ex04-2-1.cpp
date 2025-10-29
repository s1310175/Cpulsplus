#include <iostream>

/**
 * @brief Calculates the cube of an integer.
 * * The 'constexpr' keyword ensures that, when possible (i.e., when 
 * all arguments are known at compile time), this function will be 
 * evaluated during the compilation process. This allows for faster 
 * execution and enables the result to be used in contexts requiring 
 * compile-time constants (like array dimensions).
 * * @param n The integer to be cubed.
 * @return The cube of n (n * n * n).
 */
constexpr int cube(int n) {
    return n * n * n;
}

int main() {
    // 1. Compile-time evaluation example:
    // The result is computed by the compiler before the program runs.
    constexpr int compile_time_result = cube(4); 
    std::cout << "Cube of 4 (Compile-time evaluation): " << compile_time_result << std::endl;

    // 2. Runtime evaluation example (The constexpr function can still be evaluated at runtime):
    int input = 5;
    // Since 'input' is not a compile-time constant, cube(input) is evaluated at runtime.
    int runtime_result = cube(input); 
    std::cout << "Cube of 5 (Runtime evaluation): " << runtime_result << std::endl;

    // 3. Demonstrating use in a context requiring a compile-time constant:
    // This array size (27) must be determined at compile time.
    // This would cause a compilation error if cube() was not defined as constexpr.
    int array_of_cubes[cube(3)];
    std::cout << "Array size based on cube(3) (27): " << sizeof(array_of_cubes) / sizeof(int) << std::endl;

    return 0;
}
