#include<bits/stdc++.h>
using namespace std;

class QuickSort {
    int partition(vector<int> &arr, int low, int high) {
        int pivot = arr[low]; //pivot as first element
        int i = low + 1;
        int j = high;

        while (true) {
            while (i <= high && arr[i] <= pivot) {
                i++;
            }

            while (j > low && arr[j] > pivot) {
                j--;
            }

            if (i >= j) {
                break;
            }

            swap(arr[i], arr[j]);
        }

        swap(arr[low], arr[j]);
        return j;
    }

public:
    void deterministicQuickSort(vector<int> &arr, int low, int high) {
        if(low < high) {
            int pivot = partition(arr, low, high);
            deterministicQuickSort(arr, low, pivot);
            deterministicQuickSort(arr, pivot + 1, high);
        }
    }

    void randomQuickSort(vector<int> &arr, int low, int high) {
        if(low < high) {
            int r = low + rand() % (high - low + 1);
            swap(arr[r], arr[low]);
            int pivot = partition(arr, low, high);
            randomQuickSort(arr, low, pivot);
            randomQuickSort(arr, pivot + 1, high);
        }
    }
};


int main() {
    srand(time(0));
    QuickSort qs;

    vector<int> x = {15, 10, 12, 20, 1, 4, 17, 16, 11};
    int n = x.size();

    qs.deterministicQuickSort(x, 0, n-1);
    for (auto i : x)
        cout << i << " ";
    cout << endl;

    x = {5, 4, 1, 2, 3};
    n = x.size();
    qs.randomQuickSort(x, 0, n-1);
    for (auto i : x)
        cout << i << " ";
    cout << endl;

    return 0;
}