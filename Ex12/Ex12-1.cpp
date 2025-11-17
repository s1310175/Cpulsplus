#include <iostream>
#include <functional> 
#include <cmath>      
#include <iomanip>    
#include <cstdlib>    

using real = float;

std::function<real(real)> compose_functions(
    const std::function<real(real)>& f,
    const std::function<real(real)>& g)
{
    return [f, g](real x) -> real {
        return f(g(x));
    };
}

// --- Tests ---

void run_tests() {
    std::cout << "--- Tests ---" << std::endl;
    std::cout << std::fixed << std::setprecision(4);

    // 1. Test Case: Linear Functions
    // f(x) = 2x + 1, g(x) = x - 3
    // Expected composition: h(x) = 2(x - 3) + 1 = 2x - 5
    std::function<real(real)> f_linear = [](real x) { return 2.0f * x + 1.0f; };
    std::function<real(real)> g_linear = [](real x) { return x - 3.0f; };

    auto h_linear = compose_functions(f_linear, g_linear);

    real x_val_1 = 10.0f;
    real expected_1 = 2.0f * x_val_1 - 5.0f;
    real result_1 = h_linear(x_val_1);

    std::cout << "\n[Test 1: Simple Linear Functions]" << std::endl;
    std::cout << "  x = " << x_val_1 << std::endl;
    std::cout << "  Expected (2x-5) = " << expected_1 << std::endl;
    std::cout << "  Result = " << result_1 << std::endl;
    if (std::abs(result_1 - expected_1) < 1e-4) {
        std::cout << "  -> PASS" << std::endl;
    } else {
        std::cout << "  -> FAIL" << std::endl;
    }

    // 2. Test Case: Standard Mathematical Functions
    // f(x) = sin(x), g(x) = cos(x)
    // Expected composition: h(x) = sin(cos(x))
    
    std::function<real(real)> f_math = static_cast<real(*)(real)>(std::sin);
    std::function<real(real)> g_math = static_cast<real(*)(real)>(std::cos);

    auto h_math = compose_functions(f_math, g_math);

    real x_val_2 = 0.5f;
    real expected_2 = std::sin(std::cos(x_val_2));
    real result_2 = h_math(x_val_2);

    std::cout << "\n[Test 2: Mathematical Functions (sin and cos)]" << std::endl;
    std::cout << "  x = " << x_val_2 << std::endl;
    std::cout << "  Expected (sin(cos(x))) = " << expected_2 << std::endl;
    std::cout << "  Result = " << result_2 << std::endl;
    if (std::abs(result_2 - expected_2) < 1e-4) {
        std::cout << "  -> PASS" << std::endl;
    } else {
        std::cout << "  -> FAIL" << std::endl;
    }

    // 3. Test Case: Linear and Power Function (New Test)
    // f(x) = 5x, g(x) = x^2
    // Expected composition: h(x) = 5 * (x^2)
    std::function<real(real)> f_scale = [](real x) { return 5.0f * x; };
    std::function<real(real)> g_power = [](real x) { return x * x; }; // or std::pow(x, 2.0f)

    auto h_power_comp = compose_functions(f_scale, g_power);

    real x_val_3 = 3.0f;
    real expected_3 = 5.0f * (x_val_3 * x_val_3); // 5 * 9 = 45
    real result_3 = h_power_comp(x_val_3);

    std::cout << "\n[Test 3: Linear and Power Function]" << std::endl;
    std::cout << "  x = " << x_val_3 << std::endl;
    std::cout << "  Expected (5 * x^2) = " << expected_3 << std::endl;
    std::cout << "  Result = " << result_3 << std::endl;
    if (std::abs(result_3 - expected_3) < 1e-4) {
        std::cout << "  -> PASS" << std::endl;
    } else {
        std::cout << "  -> FAIL" << std::endl;
    }

    std::cout << "\n--- Tests Complete ---" << std::endl;
}

int main() {
    run_tests();
    return 0;
}
