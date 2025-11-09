#include <iostream>
#include <string>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <cmath>
#include <algorithm>

// Helper function to perform the arithmetic operation
float do_op(char op, float val2, float val1) {
    switch (op) {
        case '+': return val1 + val2;
        case '-': return val1 - val2;
        case '*': return val1 * val2;
        case '/':
            if (std::abs(val2) < 1e-6) {
                throw std::runtime_error("Error: Division by zero.");
            }
            return val1 / val2;
        default:
            throw std::runtime_error("Error: Unknown operator.");
    }
}

// Evaluates a fully parenthesized arithmetic expression using Dijkstra's 2-stack algorithm
float evaluate(const std::string& expression) {
    
    std::stack<float> vals;
    std::stack<char> ops;
    std::stringstream ss(expression);
    std::string token;

    while (ss >> token) {
        if (token == "(") {
            continue;
        } else if (token.length() == 1 && std::string("+-*/").find(token[0]) != std::string::npos) {
            // It's an operator
            ops.push(token[0]);
        } else if (token == ")") {
            // Evaluate operation
            if (ops.empty() || vals.size() < 2) {
                throw std::runtime_error("Error: Malformed expression (unbalanced ')' or missing op/vals).");
            }

            char op = ops.top(); ops.pop();
            
            float val2 = vals.top(); vals.pop();
            float val1 = vals.top(); vals.pop();

            vals.push(do_op(op, val2, val1));
        } else {
            
            try {
                vals.push(std::stof(token));
            } catch (const std::exception& e) {
                throw std::runtime_error("Error: Invalid operand or token: " + token);
            }
        }
    }

    if (vals.size() == 1 && ops.empty()) {
        return vals.top();
    } else {
        throw std::runtime_error("Error: Malformed expression (unbalanced or not fully parenthesized).");
    }
}

void test_evaluate() {
    std::cout << "--- Dijkstra's 2-Stack Evaluation Test ---\n";

    // Test Cases
    std::string tests[] = {
        "( 1.0 + ( 2.0 * 3.0 ) )",
        "( ( 4.0 - 2.0 ) / 0.5 )",
        "( ( 5.0 + 3.0 ) * ( 1.0 + 1.0 ) )",
        "( ( 10.0 / 2.0 ) - 1.0 )",
        "( 123.4 / 10.0 )"
    };

    for (const auto& expr : tests) {
        try {
            float result = evaluate(expr);
            std::cout << "Expr: " << expr << " = " << result << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Expr: " << expr << " -> Error: " << e.what() << std::endl;
        }
    }

    // Error Test Cases
    std::cout << "\n--- Error Test Cases (Expecting Exception) ---\n";
    std::string error_tests[] = {
        // Not fully parenthesized (should fail final check)
        "( 1.0 + 2.0 )", 
        // Unbalanced parentheses (should fail final check)
        "( ( 4.0 + 5.0 )", 
        // Division by zero
        "( 1.0 + ( 2.0 / 0.0 ) )",
        // Invalid token
        "( 1.0 + ( 2.0 $ 3.0 ) )",
        // Missing operand
        "( 1.0 + ( 2.0 * ) )" 
    };

    for (const auto& expr : error_tests) {
        try {
            float result = evaluate(expr);
            std::cout << "Expr: " << expr << " = " << result << " (SHOULD FAIL)" << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Expr: " << expr << " -> Caught Error: " << e.what() << std::endl;
        }
    }
}

int main() {
    test_evaluate();
    return 0;
}
