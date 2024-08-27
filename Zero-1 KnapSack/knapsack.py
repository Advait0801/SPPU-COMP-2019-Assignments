class KnapSack:
    def __init__(self) -> None:
        pass

    def solve(self, i, capacity, weights, values, dp):
        if i == 0:
            if weights[0] <= capacity:
                return values[0]
            return 0
        
        if dp[i][capacity] != -1:
            return dp[i][capacity]
        
        not_taken = self.solve(i-1, capacity, weights, values, dp)
        taken = float('-inf')
        if weights[i] <= capacity:
            taken = values[i] + self.solve(i-1, capacity - weights[i], weights, values, dp)

        dp[i][capacity] = max(taken, not_taken)
        return max(taken, not_taken)
    
    def memoization(self, max_capacity, weights, values):
        n = len(weights)
        dp = [[-1 for _ in range(max_capacity + 1)] for _ in range(n)]
        max_profit = self.solve(n-1, max_capacity, weights, values, dp)

        print("The max profit by recursion-memoization is " + str(max_profit))

    def tabulation(self, max_capacity, weights, values):
        n = len(weights)
        dp = [[0 for _ in range(max_capacity + 1)] for _ in range(n)]
        for w in range(weights[0], max_capacity + 1):
            dp[0][w] = values[0]

        for i in range(1, n):
            for w in range(max_capacity + 1):
                not_taken = dp[i-1][w]
                taken = float('-inf')
                if weights[i] <= w:
                    taken = values[i] + dp[i-1][w - weights[i]]
                dp[i][w] = max(taken, not_taken)
        
        print("The max profit by tabulation is " + str(dp[n-1][max_capacity]))

    def space_optimized(self, max_capacity, weights, values):
        n = len(weights)
        prev = [0 for _ in range(max_capacity + 1)]
        for w in range(weights[0], max_capacity + 1):
            prev[w] = values[0]

        for i in range(1, n):
            curr = [0 for _ in range(max_capacity + 1)]
            for w in range(max_capacity + 1):
                not_taken = prev[w]
                taken = float('-inf')
                if weights[i] <= w:
                    taken = values[i] + prev[w - weights[i]]
                curr[w] = max(taken, not_taken)
            prev = curr

        print("The max profit by space optimization is " + str(prev[max_capacity]))



weights = [95, 4, 60, 32, 23, 72, 80, 62, 65, 46]
values = [55, 10, 47, 5, 4, 50, 8, 61, 85, 87]
max_capacity = 269

k = KnapSack()
k.memoization(max_capacity, weights, values)
k.tabulation(max_capacity, weights, values)
k.space_optimized(max_capacity, weights, values)