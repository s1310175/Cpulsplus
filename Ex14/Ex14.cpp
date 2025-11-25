#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <thread>
#include <mutex>
#include <functional>
#include <cmath>

std::mutex mtx;

void split(std::size_t nele, std::size_t nthreads,
           std::vector<std::size_t>& lower, std::vector<std::size_t>& upper) {
    
    std::size_t chunk = nele / nthreads; 
    std::size_t remainder = nele % nthreads; 
    
    std::size_t current = 0;
    
    for (std::size_t i = 0; i < nthreads; ++i) {
        lower.push_back(current);
        
        std::size_t size = chunk + (i < remainder ? 1 : 0);
        
        current += size;
        upper.push_back(current);
    }
}

void dot_product(const std::vector<float>& v1, const std::vector<float>& v2,
                 std::size_t lower, std::size_t higher, float* result) {
    float local_sum = 0;
    

    for (std::size_t i = lower; i < higher; ++i) {
        local_sum += v1[i] * v2[i];
    }

    std::lock_guard<std::mutex> lock(mtx);
    *result += local_sum;
}

float parallel_dot_product(const std::vector<float>& v1, const std::vector<float>& v2,
                           std::size_t nthreads) {
    if (v1.size() != v2.size()) {
        std::cerr << "Error: sizes do not match" << std::endl;
        exit(1);
    }
    
    std::size_t nele = v1.size();
    float result = 0;

    std::vector<std::size_t> lower;
    std::vector<std::size_t> higher;
    split(nele, nthreads, lower, higher);
    std::vector<std::thread> threads;
    for (std::size_t i = 0; i < nthreads; ++i) {
        threads.push_back(std::thread(dot_product, std::ref(v1), std::ref(v2), lower[i], higher[i], &result));
    }
    for (auto& t : threads) {
        t.join();
    }

    return result;
}


float serial_dot_product(const std::vector<float>& v1, const std::vector<float>& v2) {
    float sum = 0;
    for (size_t i = 0; i < v1.size(); ++i) {
        sum += v1[i] * v2[i];
    }
    return sum;
}

void usage(const char* pname) {
    std::cout << "Usage: " << pname << " nele nthreads" << std::endl;
    exit(1);
}

int main(int argc, char** argv) {
    if (argc != 3) usage(argv[0]);

    std::size_t nele = std::stoi(argv[1]);
    std::size_t nthreads = std::stoi(argv[2]);


    std::vector<float> v1(nele);
    std::vector<float> v2(nele);
    for (size_t i = 0; i < nele; ++i) {
        v1[i] = float(rand()) / float(RAND_MAX);
        v2[i] = float(rand()) / float(RAND_MAX);
    }


    std::cout << "Starting parallel dot product (" << nthreads << " threads)..." << std::endl;
    auto start = std::chrono::steady_clock::now();
    
    float result = parallel_dot_product(v1, v2, nthreads);
    
    auto stop = std::chrono::steady_clock::now();
    auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();

    std::cout << "Result: " << result << " / Time: " << diff << " ms" << std::endl;

    
    if (nele <= 100000) {
        std::cout << "Verifying..." << std::endl;
        float expected = serial_dot_product(v1, v2);
        
        if (std::abs(result - expected) < 1.0f) { 
            std::cout << "OK! Serial result: " << expected << std::endl;
        } else {
            std::cout << "NG! Serial result: " << expected << std::endl;
        }
    } else {
        std::cout << "Skipping verification (too large)." << std::endl;
    }

    return 0;
}
