
#include "algorithms.h"
#include <cassert>
#include <iostream>
#include <vector>

int main() {
    // Normal search tests
    std::vector<int> nums = {1, 3, 5, 7, 9};

    assert(linearSearch(nums, 5) == 2);
    assert(linearSearch(nums, 4) == -1);
    assert(binarySearch(nums, 7) == 3);
    assert(binarySearch(nums, 4) == -1);

    // Empty array tests
    std::vector<int> empty;
    assert(linearSearch(empty, 1) == -1);
    assert(binarySearch(empty, 1) == -1);

    // Single element tests
    std::vector<int> single = {10};
    assert(binarySearch(single, 10) == 0);
    assert(binarySearch(single, 5) == -1);

    // Bubble sort tests
    std::vector<int> a = {5, 2, 4, 1, 3};
    bubbleSort(a);
    assert((a == std::vector<int>{1, 2, 3, 4, 5}));

    // Selection sort tests
    std::vector<int> b = {9, -1, 3, 3, 0};
    selectionSort(b);
    assert((b == std::vector<int>{-1, 0, 3, 3, 9}));

    // Already sorted and empty arrays
    std::vector<int> c = {1, 2, 3};
    bubbleSort(c);
    selectionSort(c);
    assert((c == std::vector<int>{1, 2, 3}));

    std::vector<int> d;
    bubbleSort(d);
    selectionSort(d);
    assert(d.empty());

    std::cout << "All tests passed successfully!\n";
    return 0;
}
