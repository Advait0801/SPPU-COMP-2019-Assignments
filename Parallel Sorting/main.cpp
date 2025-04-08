#include<bits/stdc++.h>
using namespace std;

template <typename E>
class ParallelSorting {
    vector<E> arr;

    void mergeSortHelper(int left, int right, int depth) {
        if(left >= right) return;

        int mid = left + (right - left) / 2;

        if(depth <= 4) {
            #pragma omp parallel sections
            {
                #pragma omp section
                mergeSortHelper(left, mid, depth + 1);

                #pragma omp section
                mergeSortHelper(mid + 1, right, depth + 1);
            }
        } else {
            mergeSortHelper(left, mid, depth + 1);
            mergeSortHelper(mid + 1, right, depth + 1);
        }

        merge(left, mid, right);
    }

    void merge(int left, int mid, int right) {
        vector<E> temp(right - left + 1);
        int i = left, j = mid + 1, k = 0;

        while(i <= mid && j <= right) {
            if (arr[i] <= arr[j]) temp[k++] = arr[i++];
            else temp[k++] = arr[j++];
        }

        while (i <= mid) temp[k++] = arr[i++];
        while (j <= right) temp[k++] = arr[j++];

        for (int i = left, k = 0; i <= right; i++, k++) arr[i] = temp[k];
    }

public:
    ParallelSorting(const vector<E> & inputArr) : arr(inputArr) {}

    void bubbleSort() {
        int n = arr.size();
        bool swapped = true;

        for(int i=0;i<n-1 && swapped;i++) {
            swapped = false;

            #pragma omp parallel for shared(swapped)
            for(int j=0;j<n-1;j+=2) {
                if(arr[j] > arr[j+1]) {
                    swap(arr[j], arr[j+1]);
                    swapped = true;
                }
            }

            #pragma omp parallel for shared(swapped)
            for(int j=1;j<n-1;j+=2) {
                if(arr[j] > arr[j+1]) {
                    swap(arr[j], arr[j+1]);
                    swapped = true;
                }
            }
        }
    }

    void mergeSort() {
        int n = arr.size();

        mergeSortHelper(0, n-1, 0);
    }

    void printArray() {
        cout<<"The elements of the array are..."<<endl;
        for(auto it : arr) {
            cout<<it<<" ";
        }
        cout<<endl;
    }
};


int main() {
    vector<int> arr = {5, 3, 10, 20, 0, -1};
    ParallelSorting<int> ps1(arr);

    cout<<"Original array....."<<endl;
    ps1.printArray();

    cout<<"Bubble Sort..."<<endl;
    ps1.bubbleSort();
    ps1.printArray();

    arr = {5, 3, 10, 20, 0, -1};
    ParallelSorting<int> ps2(arr);
    cout<<"Merge Sort...."<<endl;
    ps2.mergeSort();
    ps2.printArray();

    return 0;    
}