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

class Knapsack:
    def __init__(self) -> None:
        pass

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
        

weights = [3, 4, 6, 5]
values = [2, 3, 1, 4]
k = Knapsack()
k.branch_and_bound(8, weights, values)