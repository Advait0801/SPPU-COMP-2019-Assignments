#include<bits/stdc++.h>
using namespace std;

class KnapSack {
    int solve(int i, int capacity, vector<int> &weights, vector<int> &values, vector<vector<int>> &dp) {
        if(i == 0) {
            if(weights[0] <= capacity) return values[0];
            return 0;
        }
        if(dp[i][capacity] != -1) return dp[i][capacity];

        int notTaken = solve(i-1, capacity, weights, values, dp);
        int taken = INT_MIN;
        if(weights[i] <= capacity) taken = values[i] + solve(i-1, capacity - weights[i], weights, values, dp);

        return dp[i][capacity] = max(taken, notTaken);
    }

    void getSelectedItems(int n, int capacity, vector<int> &weights, vector<vector<int>> &dp, vector<int> &selectedItems) {
        int i = n - 1, w = capacity;

        while (i >= 0 && w > 0) {
            if (i == 0) {
                if (dp[i][w] != 0) selectedItems.push_back(i);
                break;
            }

            if (dp[i][w] != dp[i - 1][w]) {
                selectedItems.push_back(i);
                w -= weights[i];
            }
            
            i--;
        }

        reverse(selectedItems.begin(), selectedItems.end());
    }


public:
    void memoization(int maxCapacity, vector<int> &weights, vector<int> &values) {
        int n = weights.size();
        vector<vector<int>> dp(n, vector<int> (maxCapacity + 1, -1));
        int maxProfit = solve(n-1, maxCapacity, weights, values, dp);

        cout<<"The max profit by recursion-memoization is "<<maxProfit<<endl;  

        vector<int> items;
        getSelectedItems(n, maxCapacity, weights, dp, items);
        cout<<"Items selected: ";
        for(int i : items) {
            cout<<i<<" ";
        }
        cout<<endl;
    }

    void tabulation(int maxCapacity, vector<int> &weights, vector<int> &values) {
        int n = weights.size();
        vector<vector<int>> dp(n, vector<int> (maxCapacity + 1, 0));
        for(int w=weights[0];w<=maxCapacity;w++) {
            dp[0][w] = values[0];
        }

        for(int i=1;i<n;i++) {
            for(int w=0;w<=maxCapacity;w++) {
                int notTaken = dp[i-1][w];
                int taken = INT_MIN;
                if(weights[i] <= w) taken = values[i] + dp[i-1][w - weights[i]];
                dp[i][w] = max(taken, notTaken); 
            }
        }

        cout<<"The max profit by tabulation is "<<dp[n-1][maxCapacity]<<endl;

        vector<int> items;
        getSelectedItems(n, maxCapacity, weights, dp, items);
        cout<<"Items selected: ";
        for(int i : items) {
            cout<<i<<" ";
        }
        cout<<endl;
    }

    void spaceOptimized(int maxCapacity, vector<int> &weights, vector<int> &values) {
        int n = weights.size();
        vector<int> prev(maxCapacity + 1, 0);
        for(int w=weights[0];w<=maxCapacity;w++) {
            prev[w] = values[0];
        }

        for(int i=1;i<n;i++) {
            vector<int> curr(maxCapacity + 1, 0);
            for(int w=0;w<=maxCapacity;w++) {
                int notTaken = prev[w];
                int taken = INT_MIN;
                if(weights[i] <= w) taken = values[i] + prev[w - weights[i]];
                curr[w] = max(taken, notTaken); 
            }
            prev = curr;
        }

        cout<<"The max profit by space optimization is "<<prev[maxCapacity]<<endl;
    }
};

int main() {
    vector<int> weights = {95, 4, 60, 32, 23, 72, 80, 62, 65, 46};
    vector<int> values = {55, 10, 47, 5, 4, 50, 8, 61, 85, 87};
    int capacity = 269;

    KnapSack k;
    k.memoization(capacity, weights, values);
    k.tabulation(capacity, weights, values);
    k.spaceOptimized(capacity, weights, values);

    return 0;
}