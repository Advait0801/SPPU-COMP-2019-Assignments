class Graph:
    def __init__(self):
        self.adjacecy_list = {}
        
    def add_edge(self, node1, node2):
        if node1 not in self.adjacecy_list:
            self.adjacecy_list[node1] = [node2]
        else:
            self.adjacecy_list[node1].append(node2)

        if node2 not in self.adjacecy_list:
            self.adjacecy_list[node2] = [node1]
        else:
            self.adjacecy_list[node2].append(node1)

    def display(self):
        print("Following is the adjacency list of the graph....")
        for node in self.adjacecy_list.keys():
            print("Node " + str(node) + " : " + str(self.adjacecy_list[node]))
        print()
    
    def depth_first_search(self, key, start_node):
        def solve(node, key, visited, level):
            print("Visited " + str(node) + ", level = " + str(level))
            if node == key:
                print("Element " + str(key) + " found in the graph at level " + str(level))
                return True
            
            visited.append(node)
            neighbors = self.adjacecy_list.get(node, [])
            for neighbor in neighbors:
                if neighbor not in visited:
                    found = solve(neighbor, key, visited, level + 1)
                    if found:
                        return True
                    
            return False
        
        visited = []
        found = solve(start_node, key, visited, 0)
        if not found:
            print("Element " + str(key) + ' doesnt exist in the graph')

        
    def breadth_first_search(self, key, start_node):
        def solve(frontier, frontier_levels, key, visited):
            if not frontier:
                return False
            
            node = frontier[0]
            frontier.pop(0)
            level = frontier_levels[0]
            frontier_levels.pop(0)
            print("Visited " + str(node) + ", level = " + str(level))
            if node == key:
                print("Element " + str(key) + " found in the graph at level " + str(level))
                return True
            
            visited.append(node)
            neighbors = self.adjacecy_list.get(node, [])
            for neighbor in neighbors:
                if neighbor not in visited:
                    frontier.append(neighbor)
                    frontier_levels.append(level + 1)
            
            return solve(frontier, frontier_levels, key, visited)
        
        visited = []
        frontier = [start_node]
        frontier_levels = [0]
        found = solve(frontier, frontier_levels, key, visited)
        if not found:
            print("Element " + str(key) + ' doesnt exist in the graph')


graph = Graph()
print("Enter node-pairs o the graph.....")
while True:
    node1 = input("Node 1: ")
    node2 = input("Node 2: ")
    if node1 == "-" and node2 == "-":
        break
    graph.add_edge(node1, node2)
    print("Edge added: " + str(node1) + " - " + str(node2))
print()
graph.display()
key = input("Enter key to search: ")

start_node = input("Enter start node: ")
print()
graph.depth_first_search(key, start_node)
print()
graph.breadth_first_search(key, start_node)