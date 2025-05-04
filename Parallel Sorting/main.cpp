#include<bits/stdc++.h>
using namespace std;

template <typename E>
class ParallelSorting {
    vector<E> arr;

    void sequentialMergeSortHelper(int left, int right) {
        if(left >= right) return;

        int mid = left + (right - left) / 2;
        sequentialMergeSortHelper(left, mid);
        sequentialMergeSortHelper(mid + 1, right);
        merge(left, mid, right);
    }

    void parallelMergeSortHelper(int left, int right, int depth) {
        if(left >= right) return;

        int mid = left + (right - left) / 2;

        if(depth <= 4) {
            #pragma omp parallel sections
            {
                #pragma omp section
                parallelMergeSortHelper(left, mid, depth + 1);

                #pragma omp section
                parallelMergeSortHelper(mid + 1, right, depth + 1);
            }
        } else {
            parallelMergeSortHelper(left, mid, depth + 1);
            parallelMergeSortHelper(mid + 1, right, depth + 1);
        }

        merge(left, mid, right);
    }

    void merge(int left, int mid, int right) {
        //common to both parallel and sequential
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

    void sequentialBubbleSort() {
        auto start = chrono::high_resolution_clock::now();

        int n = arr.size();
        bool swapped = true;

        for(int i=0;i<n-1 && swapped;i++) {
            swapped = false;
            for(int j=0;j<n-1-i;j++) {
                if(arr[j] > arr[j+1]) {
                    swap(arr[j], arr[j+1]);
                    swapped = true;
                }
            }
        }

        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
        cout<<"Time taken for sequential bubble sort: "<<duration<<" microseconds"<<endl;
    }

    void parallelBubbleSort() {
        auto start = chrono::high_resolution_clock::now();

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

        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
        cout<<"Time taken for parallel bubble sort: "<<duration<<" microseconds"<<endl;
    }

    void parallelMergeSort() {
        int n = arr.size();

        auto start = chrono::high_resolution_clock::now();
        cout<<"Parallel Merge Sort..."<<endl;
        parallelMergeSortHelper(0, n-1, 0);
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
        cout<<"Time taken for parallel merge sort: "<<duration<<" microseconds"<<endl;
    }

    void sequentialMergeSort() {
        int n = arr.size();

        auto start = chrono::high_resolution_clock::now();
        cout<<"Sequential Merge Sort..."<<endl;
        sequentialMergeSortHelper(0, n-1);
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
        cout<<"Time taken for sequential merge sort: "<<duration<<" microseconds"<<endl;
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
    cout<<"The original array is..."<<endl;
    for(auto it : arr) {
        cout<<it<<" ";
    }

    ParallelSorting<int> ps1(arr);
    ps1.sequentialBubbleSort();
    ps1.printArray();

    ParallelSorting<int> ps2(arr);
    ps2.parallelBubbleSort();
    ps2.printArray();

    ParallelSorting<int> ps3(arr);
    ps3.sequentialMergeSort();
    ps3.printArray();

    ParallelSorting<int> ps4(arr); 
    ps4.parallelMergeSort();
    ps4.printArray();

    return 0;    
}