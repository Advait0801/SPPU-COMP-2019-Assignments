class Graph:
    def __init__(self, num_nodes):
        self.num_nodes = num_nodes
        self.adj_list = [[] for i in range(self.num_nodes)]
        self.edges = []

    def add_edge(self, node1, node2, weight):
        self.adj_list[node1].append((node2, weight))
        self.adj_list[node2].append((node1, weight))
        self.edges.append((node1, node2, weight))

    def check_cycle(self, source, destination):
        queue = [source]
        visited = [source]

        while len(queue) != 0:
            front = queue[0]
            queue.pop(0)
            if front == destination:
                return True
            
            neighbors = self.adj_list[front]
            for neighbor in neighbors:
                if neighbor[0] not in visited:
                    visited.append(neighbor[0])
                    queue.append(neighbor[0])

        return False
    
    def bfs(self):
        queue = [0]
        visited = [0]
        travel_seq = []

        while len(queue) != 0:
            front = queue[0]
            queue.pop(0)
            travel_seq.append(front)
            neighbors = self.adj_list[front]

            for neighbor in neighbors:
                if neighbor[0] not in visited:
                    visited.append(neighbor[0])
                    queue.append(neighbor[0])

        print(travel_seq)


def prims(graph: Graph):
    curr_node = 0
    tree_num_nodes = 1
    min_cost = 0
    visited = [curr_node]
    spanning_tree = Graph(graph.num_nodes)

    while tree_num_nodes != graph.num_nodes:
        min_weight_edge = min([neighbor for neighbor in graph.adj_list[curr_node] if neighbor[0] not in visited], key=lambda x: x[1])

        spanning_tree.add_edge(curr_node, min_weight_edge[0], min_weight_edge[1])
        min_cost += min_weight_edge[1]
        curr_node = min_weight_edge[0]
        tree_num_nodes += 1
        visited.append(min_weight_edge[0])
    
    graph.bfs()
    print(min_cost)


def kruskals(graph: Graph):
    ordered_edges = list(sorted(graph.edges, key=lambda edge: edge[2]))
    spanning_tree = Graph(graph.num_nodes)
    min_cost = 0

    for edge in ordered_edges:
        if spanning_tree.check_cycle(edge[0], edge[1]):
            continue

        spanning_tree.add_edge(*edge) 
        min_cost += edge[2]
    
    spanning_tree.bfs()
    print(min_cost)
      



graph = Graph( 5 )
graph.add_edge( 0 , 1 , 1 )
graph.add_edge( 1 , 2 , 3 )
graph.add_edge( 2 , 3 , 4 )
graph.add_edge( 0 , 2 , 7 )
graph.add_edge( 0 , 3 , 10 )
graph.add_edge( 3 , 4 , 2 )
graph.add_edge( 0 , 4 , 5 )

prims(graph)
print()
kruskals(graph)
 