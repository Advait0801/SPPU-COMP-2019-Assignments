class Graph:
    def __init__(self, num_nodes) -> None:
        self.num_nodes = num_nodes
        self.adj_list = [[] for i in range(self.num_nodes)]

    def add_edge(self, node1, node2):
        self.adj_list[node1].append(node2)
        self.adj_list[node2].append(node1)

    def display(self):
        print("Following is the adjacency list representation of the graph....")
        print()
        for i in range(self.num_nodes):
            print(str(i) + ' ---- ' + str(self.adj_list[i]))
        print()

    def dfs_iterative(self, key): #depth first search
        print('Depth First Search Iterative......')
        stack = [(0, 0)]
        visited = [(0, 0)]
        search_seq = []

        while len(stack) != 0:
            top = stack[-1]
            top_element = top[0]
            top_level = top[1]
            stack.pop()
            search_seq.append(top)

            if top_element == key:
                print("Element " + str(key) + " found in the graph !")
                break

            neighbours = self.adj_list[top_element]
            for neighbor in neighbours:
                if neighbor not in [visited_element[0] for visited_element in visited]:
                    visited.append((neighbor, top_level + 1))
                    stack.append((neighbor, top_level + 1))

        else:
            print("Element " + str(key) + ' doesnt exist in the graph')
        print("Following was the search sequence..." + str(search_seq))
        print()

    def bfs_iterative(self, key): #breadh first search
        print('Breadth First Search Iterative......')
        queue = [(0, 0)]
        visited = [(0, 0)]
        search_seq = []
        
        while len(queue) != 0:
            front = queue[0]
            front_element = front[0]
            front_level = front[1]
            queue.pop(0)
            search_seq.append(front)

            if front_element == key:
                print("Element " + str(key) + " found in the graph !")
                break
            
            neighbours = self.adj_list[front_element]
            for neighbor in neighbours:
                if neighbor not in visited:
                    visited.append((neighbor, front_level + 1))
                    queue.append((neighbor, front_level + 1))
        else:
            print("Element " + str(key) + ' doesntexist in the graph')
        print("Following was the searchsequence..." + str(search_seq))
        print()

    def dfs_recursive(self, key): #depth first search
        def solve(node, visited, key):
            print('Visited node ' + str(node))

            if node is None:
                return
            if node == key:
                print("Element " + str(key) + " found in the graph !")
                return
            
            for neighbor in self.adj_list[node]:
                if neighbor not in visited:
                    visited.append(neighbor)
                    solve(neighbor, visited, key)

        print('Depth First Search Recursive....')
        visited = []
        solve(0, visited, key)
        print()

    def bfs_recursive(self, key): #breadth first search
        def solve(queue, visited, key):
            if len(queue) == 0:
                return
            
            front = queue[0]
            queue.pop(0)
            print('Visited node ' + str(front))

            if front == key:
                print("Element " + str(key) + " found in the graph !")
                return
            
            visited.append(front)
            for neighbor in self.adj_list[front]:
                if neighbor not in visited:
                    queue.append(neighbor)
                solve(queue, visited, key)


        print('Breadth First Search Recursive.....')
        queue = [0]
        visited = [0]
        solve(queue, visited, key)
        print()
                
                

graph = Graph(5)
graph.add_edge(0, 1)
graph.add_edge(0, 2)
graph.add_edge(1, 3)
graph.add_edge(1, 4)
graph.display()

graph.bfs_iterative(3)
graph.dfs_iterative(3)

graph.dfs_recursive(3)
graph.bfs_recursive(3)
         
                