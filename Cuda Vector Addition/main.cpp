#include <bits/stdc++.h>
using namespace std;

__global__ void vecAdd(int* A, int *B, int *C, int size) {
    int tid = blockIdx.x*blockDim.x + threadIdx.x;

    if(tid < size)
        C[tid] = B[tid] + A[tid];
}

void addition(vector<int>& vecA, vector<int>& vecB, vector<int>& vecC, const int& size) {
    for(int i = 0; i < size; i++)
        vecC[i] = vecA[i] + vecB[i];
}

void Print(vector<int>& vc) {
    for (auto x : vc)
        cout << x << "\t";

    cout << endl;
}

int main() {

    const int size = 7;

    vector<int> A = {2, 3, 4, 5, 6, 7, 8};
    vector<int> B = {4, 5, 6, 12, 34, 54, 2};
    vector<int> C;
    C.resize(size);

    cout << "Vec A: \t\t";
    Print(A);
    cout << "Vec B: \t\t";
    Print(B);

    cout << endl;
    addition(A, B, C, size);
    cout << "Seq Vec C: \t";
    Print(C);


    // PARALLEL STUFF
    int totalBytesAllcation = A.size()*sizeof(int);

    int *X, *Y, *Z;
    cudaMalloc(&X, totalBytesAllcation);
    cudaMalloc(&Y, totalBytesAllcation);
    cudaMalloc(&Z, totalBytesAllcation);

    cudaMemcpy(X, A.data(), totalBytesAllcation, cudaMemcpyHostToDevice);
    cudaMemcpy(Y, B.data(), totalBytesAllcation, cudaMemcpyHostToDevice);

    vecAdd<<<1,255>>>(X, Y, Z, size);

    cudaMemcpy(C.data(), Z, totalBytesAllcation, cudaMemcpyDeviceToHost);

    cout << "Par Vec C: \t";
    Print(C);
}