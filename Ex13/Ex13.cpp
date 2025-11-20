#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

float compute_median(vector<float> vec) {
    // Handle empty vector case
    if (vec.empty()) {
        return 0.0f;
    }

    int n = vec.size();
    int mid = n / 2;

    // Time complexity: O(N)

    if (n % 2 != 0) {
        // Odd case
        nth_element(vec.begin(), vec.begin() + mid, vec.end());
        return vec[mid];
    } else {
        // Even case
        
        nth_element(vec.begin(), vec.begin() + mid, vec.end());
        float val1 = vec[mid];

        nth_element(vec.begin(), vec.begin() + mid - 1, vec.begin() + mid);
        float val2 = vec[mid - 1];

        return (val1 + val2) / 2.0f;
    }
}

int main() {
    // Test case 1: Odd number of elements
    vector<float> v1 = {1.0, 3.0, 2.0};
    cout << "Test 1 (Odd): " << compute_median(v1) << " (Expected: 2)" << endl;

    // Test case 2: Even number of elements
    vector<float> v2 = {1.0, 4.0, 2.0, 3.0};
    cout << "Test 2 (Even): " << compute_median(v2) << " (Expected: 2.5)" << endl;

    // Test case 3: Larger number of elements (Odd)
    vector<float> v3 = {10.0, 5.0, 2.0, 8.0, 3.0};
    cout << "Test 3 (Odd, larger): " << compute_median(v3) << " (Expected: 5)" << endl;

    // Test case 4: Larger number of elements (Even)
    vector<float> v4 = {7.0, 2.0, 10.0, 5.0, 1.0, 8.0};
    cout << "Test 4 (Even, larger): " << compute_median(v4) << " (Expected: 6)" << endl;

    // Edge case: Already sorted
    vector<float> v5 = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
    cout << "Test 5 (Sorted): " << compute_median(v5) << " (Expected: 3.5)" << endl;

    // Edge case: Contains duplicate values
    vector<float> v6 = {1.0, 1.0, 5.0, 2.0, 2.0};
    cout << "Test 6 (Duplicates): " << compute_median(v6) << " (Expected: 2)" << endl;

    // Edge case: Only one element
    vector<float> v7 = {42.0};
    cout << "Test 7 (Single): " << compute_median(v7) << " (Expected: 42)" << endl;

    // Edge case: Empty vector
    vector<float> v8 = {};
    cout << "Test 8 (Empty): " << compute_median(v8) << " (Expected: 0)" << endl;

    return 0;
}
