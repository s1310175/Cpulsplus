#include <iostream>
#include <vector>
#include <list>

namespace PL04 {


template <class FwdIt>
void sort(FwdIt begin, FwdIt end) {
    if (begin == end) {
        return;
    }

    bool swapped = true;
    while (swapped) {
        swapped = false;
        
        FwdIt current = begin;
        FwdIt next = begin;
        ++next;

        while (next != end) {
            if (*next < *current) {
               auto temp = *current;
                *current = *next;
                *next = temp;

                swapped = true;
            }
            ++current;
            ++next;
        }
     }
}

}


// --- Test code ---------------

template <class It>
void print_range(It first, It last) {
    std::cout << "[ ";
    for (It it = first; it != last; ++it) {
        std::cout << *it << " ";
    }
    std::cout << "]" << std::endl;
}

int main() {
    std::cout << "--- Test ---" << std::endl;

    std::vector<int> v = {8, 3, 10, 1, 6, 4};
    std::cout << "Before (vector): ";
    print_range(v.begin(), v.end());
    
    PL04::sort(v.begin(), v.end());
    
    std::cout << "After (vector):  ";
    print_range(v.begin(), v.end());
    std::cout << "(Expected: [ 1 3 4 6 8 10 ])" << std::endl;

    std::cout << "---" << std::endl;

    std::list<double> l = {1.5, 0.5, -2.0, 5.5, 0.0};
    std::cout << "Before (list):   ";
    print_range(l.begin(), l.end());

    PL04::sort(l.begin(), l.end());

    std::cout << "After (list):    ";
    print_range(l.begin(), l.end());
    std::cout << "(Expected: [ -2 0 0.5 1.5 5.5 ])" << std::endl;

    std::cout << "---" << std::endl;
    std::list<int> empty_l;
    std::cout << "Before (empty):  ";
    print_range(empty_l.begin(), empty_l.end());
    PL04::sort(empty_l.begin(), empty_l.end());
    std::cout << "After (empty):   ";
    print_range(empty_l.begin(), empty_l.end());
    std::cout << "(Expected: [ ])" << std::endl;

    return 0;
}
