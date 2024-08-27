#include<iostream>
using namespace std;

class Fibonacci {
    int fibSolve(int n) {
        if(n < 2) return n;

        return fibSolve(n-1) + fibSolve(n-2);
    }

public:
    void fibonacciRecursive(int n) {
        cout<<"The fibonacci series by recursive algorithm is......"<<endl;

        for(int i=0;i<n;i++) {
            cout<<fibSolve(i)<<" ";
        }

        cout<<endl;
    }

    void fibonacciIterative(int n) {
        cout<<"The fibonacci series by iterative algorithm is......"<<endl;

        int f1 = 0, f2 = 1;
        cout<<f1<<" "<<f2<<" ";

        for(int i=0;i<n-2;i++) {
            int f3 = f1 + f2;
            cout<<f3<<" ";
            f1 = f2;
            f2 = f3;
        }

        cout<<endl;
    }
};


int main() {
    Fibonacci f;
    f.fibonacciRecursive(10);
    f.fibonacciIterative(10);

    return 0;
}