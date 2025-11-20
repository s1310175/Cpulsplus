#include <iostream>
#include <cmath>
#include <functional>

std::function<double(double)> derivative(std::function<double(double)> f) {
    double h = 1e-5;
    return [f, h](double x) {
        return (f(x + h) - f(x)) / h;
    };
}

double fixed_point(std::function<double(double)> f, double x0) {
    double x_curr = x0;
    double x_next = f(x_curr);
    double tolerance = 1e-6;
    int max_iter = 1000;
    int iter = 0;

    while (std::abs(x_next - x_curr) > tolerance && iter < max_iter) {
        x_curr = x_next;
        x_next = f(x_curr);
        iter++;
    }
    return x_next;
}

std::function<double(double)> Newton_transform(std::function<double(double)> g) {
    auto g_prime = derivative(g);
   
    return [g, g_prime](double x) {
        return x - (g(x) / g_prime(x));
    };
}

double Newton_method(std::function<double(double)> g, double x0) {
    auto f = Newton_transform(g);
    return fixed_point(f, x0);
}

int main() {
    std::cout << "--- Test ---" << std::endl;

    // Test 1: x^2 - 2 = 0
    auto g1 = [](double x) { return x * x - 2.0; };
    double result1 = Newton_method(g1, 1.0);
    
    std::cout << "Test 1 (x^2 - 2): " << result1 << std::endl;
    std::cout << "Expected: " << std::sqrt(2) << std::endl;

    // Test 2: x^2 - 4 = 0
    auto g2 = [](double x) { return x * x - 4.0; };
    double result2 = Newton_method(g2, 1.0);

    std::cout << "Test 2 (x^2 - 4): " << result2 << std::endl;
    std::cout << "Expected: " << std::sqrt(4) << std::endl;

    // Test 3: cos(x) - x = 0
    auto g3 = [](double x) { return std::cos(x) - x; };
    double result3 = Newton_method(g3, 1.0);

    std::cout << "Test 3 (cos(x) - x): " << result3 << std::endl;

    return 0;
}
