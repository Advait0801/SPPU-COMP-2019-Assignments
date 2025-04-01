#include<bits/stdc++.h>
using namespace std;

template <typename E>
class ParallelReduction {
    std::vector<E> arr;

public:
    ParallelReduction(const std::vector<E>& inputArr) : arr(inputArr) {}

    E sum() {
        E sum = 0;
        #pragma omp parallel for reduction(+:sum)
        for(size_t i = 0; i < arr.size(); i++) {
            sum += arr[i];
        }
        return sum;
    }

    E min() {
        E minElement = std::numeric_limits<E>::max();
        #pragma omp parallel for reduction(min: minElement)
        for(size_t i = 0; i < arr.size(); i++) {
            minElement = std::min(minElement, arr[i]);
        }
        return minElement;
    }

    E max() {
        E maxElement = std::numeric_limits<E>::min();
        #pragma omp parallel for reduction(max: maxElement)
        for(size_t i = 0; i < arr.size(); i++) {
            maxElement = std::max(maxElement, arr[i]);
        }
        return maxElement;
    }

    double mean() {
        E sumValue = sum();
        return static_cast<double>(sumValue) / arr.size(); // Cast sum to double for accurate mean calculation
    }
};

int main() {
    std::vector<int> arr = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    ParallelReduction<int> pr(arr);

    int sumValue = pr.sum();
    std::cout << "Sum: " << sumValue << '\n';

    int maxValue = pr.max();
    std::cout << "Max: " << maxValue << '\n';

    int minValue = pr.min();
    std::cout << "Min: " << minValue << '\n';

    double meanValue = pr.mean();
    std::cout << "Mean: " << meanValue << '\n';

    return 0;
}
