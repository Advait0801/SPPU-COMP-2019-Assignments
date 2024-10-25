class Item:
    def __init__(self, weight, value, idx):
        self.weight = weight
        self.value = value
        self.idx = idx
        self.ratio = value / weight

class Node:
    def __init__(self, level, value, weight, bound, items):
        self.level = level  # Level in decision tree
        self.value = value  # Current value
        self.weight = weight  # Current weight
        self.bound = bound  # Upper bound
        self.items = items  # Selected items

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
    
    def calculate_bound(self, node, N, capacity, items):
        """Calculate upper bound for a node using fractional knapsack"""
        if node.weight >= capacity:
            return 0

        value_bound = node.value
        weight = node.weight
        j = node.level + 1

        # Add items until capacity is reached
        while j < N and weight + items[j].weight <= capacity:
            weight += items[j].weight
            value_bound += items[j].value
            j += 1

        # Add fraction of next item if possible
        if j < N:
            value_bound += (capacity - weight) * items[j].ratio

        return value_bound

    def branch_and_bound(self, max_capacity, weights, values):
        """
        Solve 0/1 Knapsack using Branch and Bound
        Args:
            max_capacity: Maximum capacity of knapsack
            weights: Array of item weights
            values: Array of item values
        Returns:
            max_value: Maximum value possible
            selected_items: List of indices of selected items
        """
        N = len(weights)

        # Create items and sort by value/weight ratio
        items = [Item(weights[i], values[i], i) for i in range(N)]
        items.sort(key=lambda x: x.ratio, reverse=True)

        # Initialize queue with root node
        queue = []
        root = Node(-1, 0, 0, 0, [])
        root.bound = self.calculate_bound(root, N, max_capacity, items)
        queue.append(root)

        max_value = 0
        best_items = []
        nodes_explored = 0

        while queue:
            # Get node with highest bound
            curr = max(queue, key=lambda x: x.bound)
            queue.remove(curr)
            nodes_explored += 1

            # Skip if bound is less than current best
            if curr.bound <= max_value:
                continue

            level = curr.level + 1

            # Skip if we've processed all items
            if level >= N:
                continue

            # Include current item
            new_weight = curr.weight + items[level].weight
            if new_weight <= max_capacity:
                new_items = curr.items + [items[level].idx]
                include = Node(level, 
                             curr.value + items[level].value,
                             new_weight,
                             0,
                             new_items)
                include.bound = self.calculate_bound(include, N, max_capacity, items)

                if include.value > max_value and include.weight <= max_capacity:
                    max_value = include.value
                    best_items = include.items

                if include.bound > max_value:
                    queue.append(include)

            # Exclude current item
            exclude = Node(level,
                          curr.value,
                          curr.weight,
                          0,
                          curr.items)
            exclude.bound = self.calculate_bound(exclude, N, max_capacity, items)

            if exclude.bound > max_value:
                queue.append(exclude)

        best_items.sort()
        print("The max profit by branch and bound is " + str(max_value))
        print("The item selected are: " + str(best_items))
        


weights = [95, 4, 60, 32, 23, 72, 80, 62, 65, 46]
values = [55, 10, 47, 5, 4, 50, 8, 61, 85, 87]
max_capacity = 269

k = KnapSack()
k.memoization(max_capacity, weights, values)
k.tabulation(max_capacity, weights, values)
k.space_optimized(max_capacity, weights, values)
k.branch_and_bound(max_capacity, weights, values)