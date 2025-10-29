#include <iostream>

/**
 * @brief Calculates the cube of an integer (redefined for self-contained file).
 * @param n The integer to be cubed.
 * @return The cube of n.
 */
constexpr int cube(int n) {
    return n * n * n;
}

int main() {
    // Verification Method: Using static_assert
    
    // static_assert checks its condition during compilation. The condition 
    // must be a compile-time constant expression.
    //
    // If cube(2) were NOT evaluated at compile time, the compiler would 
    // fail to compile this line, as static_assert requires a constant expression.
    // The successful compilation of this assert is a robust proof that 
    // cube(2) was evaluated during compilation.
    static_assert(cube(2) == 8, "Compile-time evaluation failed for cube(2)");

    std::cout << "The static_assert passed, confirming 'cube(2)' was evaluated at compile-time." << std::endl;
    
    // (Note) Uncommenting the line below would intentionally cause a compile error, 
    // demonstrating that static_assert only accepts compile-time constants.
    // static_assert(cube(2) == 9, "Test Compile Error"); 

    return 0;
}
