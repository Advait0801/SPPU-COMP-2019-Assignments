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

    def get_edge_distance(self, node1, node2):
        neighbors = self.adj_list[node1]
        for neighbor in neighbors:
            if neighbor[0] == node2:
                return neighbor[1]
        
        return None

    def display(self):
        self.adj_list = dict(sorted(self.adj_list.items()))
        print("Following is the adjacency list of the graph....")
        for node in self.adj_list.keys():
            print("Node " + str(node) + " : " + str(self.adj_list[node]))
        print()


def dijkstras_algorithm(graph: Graph, source):
    queue = []
    min_distances = {}  # min distance of each node from source
    previous_nodes = {}  # current min distance of each node from source

    for node in graph.adj_list.keys():
        min_distances[node] = 1e10     #infinity
        previous_nodes[node] = None    #not-defined
        queue.append(node)
    min_distances[source] = 0

    while len(queue) != 0:
        #find the node with minimum distance from source
        min_node = min([(n, min_distances[n]) for n in queue], key = lambda x:x[1])[0]
        queue.remove(min_node)

        for neighbor_node in [neighbor[0] for neighbor in graph.adj_list[min_node] if neighbor[0] in queue]:
            dist = min_distances[min_node] + graph.get_edge_distance(min_node, neighbor_node)

            if dist < min_distances[neighbor_node]:
                min_distances[neighbor_node] = dist
                previous_nodes[neighbor_node] = min_node

    paths = {}  #dictionary to store paths from source to a node
    paths[source] = None

    for node in previous_nodes.keys():
        if node == source:
            continue

        n = previous_nodes[node]
        path = node
        while n != None:
            path = n + '-' + path
            n = previous_nodes[n]

        paths[node] = path

    return min_distances, paths


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

source = input("Enter source node: ")
print()
distances, paths = dijkstras_algorithm(graph, source)
print("Dijkstras Algorithm as follows......")
print("Distances of nodes from " + str(source) + "......")
print(distances)
print()
print("Paths for the same nodes....")
print(paths)
