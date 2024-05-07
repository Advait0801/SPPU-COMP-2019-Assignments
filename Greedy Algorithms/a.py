import pprint
class Graph:
    def __init__(self):
        self.adj_list: dict[str, list[(str, int)]] = {}
        self.edges = []

    def add_edge(self, node_1: str, node_2: str, weight: int):
        if node_1 not in self.adj_list:
            self.adj_list[node_1] = []
        self.adj_list[node_1].append((node_2, weight))
        if node_2 not in self.adj_list:
            self.adj_list[node_2] = []
        self.adj_list[node_2].append((node_1, weight))
        self.edges.append((node_1, node_2, weight))

    def get_edge(self , node_1: str, node_2: str) -> int:
        neighbors = self.adj_list[node_1]
        for n in neighbors:
            if n[0] == node_2:
                return n[1]
        return None

    def __str__(self) -> str:
        str_repr = ""
        for key, val in self.adj_list.items():
            str_repr += f"{key} {self.adj_list[key]}\n"
        return str_repr

def single_source_shortest_path( graph: Graph , src: str ) -> dict[str,int]:
    Q: list[str] = []

    dist: dict[str,int] = {} # min distance of each node from src
    prev: dict[str,int] = {} # current min distance of each node from src
    for n in graph.adj_list.keys():
        dist[n] = 1e10      # dist[n] = infinity
        prev[n] = None      # prev[n] = UNDEFINED
        Q.append( n )
    dist[src] = 0

    while len( Q ) != 0:
        u = min( 
            [ (n,dist[n]) for n in Q ] , 
            key=lambda x: x[1] 
        )[0]
        Q.remove( u )
        for v in [ neighbor[0] for neighbor in graph.adj_list[u] if neighbor[0] in Q ]:
            alt = dist[u] + graph.get_edge(u, v)
            if alt < dist[v]:
                dist[v] = alt
                prev[v] = u
    return dist , prev

graph = Graph()

while True:
    print("Add edge to the graph: ")
    node_a = input("Enter first node: ")
    node_b = input("Enter second node: ")
    if node_a == node_b == "-":
        break
    weight = int(input("Enter weight of the edge: "))
    graph.add_edge(node_a, node_b, weight)

src = input( "Enter src node: " )

print("Graph adjacency list: ")
print(graph)
dists , paths = single_source_shortest_path(graph, src)
print( f"Distance of all nodes from source node {src}" )
pprint.pprint( dists )
print( f"Shortest paths of all nodes from source node {src}" )
pprint.pprint( paths )