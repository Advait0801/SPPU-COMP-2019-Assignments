#include<bits/stdc++.h>
using namespace std;

bool isSafe(vector<int> &board, int row, int col) {
    for(int i=0;i<row;i++) {
        if(board[i] == col || abs(board[i] - col) == abs(i - row)) return false;
    }

    return true;
}

void solveNQueens(vector<vector<int>> &solutions, vector<int> &board, int row, int n) {
    if(row == n) {
        solutions.push_back(board);
        return;
    }

    for(int col=0;col<n;col++) {
        if(isSafe(board, row, col) == true) {
            board[row] = col;
            solveNQueens(solutions, board, row + 1, n);
            board[row] = -1;
        }
    }
}

void printBoard(vector<int> solution) {
    int n = solution.size();

    for(int i=0;i<n;i++) {
        for(int j=0;j<n;j++) {
            if(solution[i] == j) {
                cout<<"Q ";
            } else {
                cout<<"* ";
            }
        }
        cout<<endl;
    }
    cout<<endl;
}

void nQueensBackTracking(int n) {
    vector<vector<int>> solutions;
    vector<int> board(n, -1);
    solveNQueens(solutions, board, 0, n);

    cout<<"Number of solutions for "<<n<<"-queens: "<<solutions.size()<<endl;
    for(auto solution : solutions) {
        printBoard(solution);
    }
}

int main() {
    nQueensBackTracking(5);

    return 0;
}