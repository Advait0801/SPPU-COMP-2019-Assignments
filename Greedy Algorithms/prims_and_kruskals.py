class Graph:
    def __init__(self):
        self.adj_list = {}
        self.edges = []

    def add_edge(self, node1, node2, weight):
        if node1 not in self.adj_list:
            self.adj_list[node1] = [(node2, weight)]
        else:
            self.adj_list[node1].append((node2, weight))

        if node2 not in self.adj_list:
            self.adj_list[node2] = [(node1, weight)]
        else:
            self.adj_list[node2].append((node1, weight))

        self.edges.append((node1, node2, weight))

    def display(self):
        self.adj_list = dict(sorted(self.adj_list.items()))
        print("Following is the adjacency list of the graph....")
        for node in self.adj_list.keys():
            print("Node " + str(node) + " : " + str(self.adj_list[node]))
        print()

    def check_cycle(self, source, destination):
        if source not in self.adj_list or destination not in self.adj_list:
            return False
        
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

def prims(graph: Graph):
    print("Prims algorithm works as follows.....")
    curr_node = list(graph.adj_list.keys())[0]
    graph_num_nodes = len(graph.adj_list)
    tree_num_edges = 1
    min_cost = 0
    visited = [curr_node]
    spanning_tree = Graph()

    while tree_num_edges <= graph_num_nodes - 1:
        min_weight_edge = min([neighbor for neighbor in graph.adj_list[curr_node] if neighbor[0] not in visited], key=lambda x: x[1], default = None)
        if min_weight_edge is None:
            continue

        print("Edge added to spanning tree ---> " + str(curr_node) + "-" + str(min_weight_edge[0]) + "-" + str(min_weight_edge[1]))
        spanning_tree.add_edge(curr_node, min_weight_edge[0], min_weight_edge[1])
        min_cost += min_weight_edge[1]
        curr_node = min_weight_edge[0]
        tree_num_edges += 1
        visited.append(min_weight_edge[0])
    
    print("Minimum Cost of Spanning Tree by Prim's algorithm is " + str(min_cost))

def kruskals(graph: Graph):
    print("Kruskal's algorithm works as follows....")
    ordered_edges = list(sorted(graph.edges, key=lambda edge: edge[2]))
    spanning_tree = Graph()
    min_cost = 0

    for edge in ordered_edges:
        if spanning_tree.check_cycle(edge[0], edge[1]):
            continue

        print("Edge added to spanning tree ---> " + str(edge[0]) + "-" + str(edge[1]) + "-" + str(edge[2]))
        spanning_tree.add_edge(*edge) 
        min_cost += edge[2]
    
    print("Minimum Cost of Spanning Tree by Kruskal's algorithm is " + str(min_cost))
    print()
      

graph = Graph()
print("Enter node-pairs of the graph.....")
while True:
    node1 = input("Node 1: ")
    node2 = input("Node 2: ")
    if node1 == "-" and node2 == "-":
        break
    weight = int(input("Enter weight of the edge: "))
    graph.add_edge(node1, node2, weight)
    print("Edge added: " + str(node1) + " - " + str(node2) + " Weight = " + str(weight))
print()
graph.display()

prims(graph)
print()
kruskals(graph)
 