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

    def get_edge(self, node1, node2):
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


def 