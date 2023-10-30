import sys

INF = sys.maxsize

def print_distance_vector(distance):
    print("Distance Vector:", end=' ')
    for dist in distance:
        if dist == INF:
            print("INF", end=' ')
        else:
            print(dist, end=' ')
    print()

def dijkstra(graph_points, graph, source):
    distance = [INF] * graph_points
    visited = [False] * graph_points
    parent = [-1] * graph_points

    distance[source] = 0

    for count in range(graph_points - 1):
        u = -1
        for i in range(graph_points):
            if not visited[i] and (u == -1 or distance[i] < distance[u]):
                u = i

        visited[u] = True

        for v in range(graph_points):
            if not visited[v] and graph[u][v] != -1 and distance[u] != INF and distance[u] + graph[u][v] < distance[v]:
                distance[v] = distance[u] + graph[u][v]
                parent[v] = u

        print("Iteration", count + 1, ":")
        print_distance_vector(distance)
        print()

    print("Optimal path from node", source, "to every other node:")
    print("Node\tDistance\tPath")
    for i in range(graph_points):
        print(i, end='\t')
        if distance[i] == INF:
            print("INF", end='')
        else:
            print(distance[i], end='')

        print('\t', end='')

        node = i
        path = []
        while node != -1:
            path.insert(0, node)
            node = parent[node]

        for j in range(len(path)):
            print(path[j], end='')
            if j < len(path) - 1:
                print(" ->", end=' ')
        print()


graph_points = int(input("Enter the number of nodes in the network: "))
graph = [[-1] * graph_points for _ in range(graph_points)]
for i in range(graph_points):
    for j in range(graph_points):
        if i != j:
            distance = int(input("Enter the distance between node {} and node {}: ".format(i, j)))
            graph[i][j] = distance
print()
print()
for source in range(graph_points):
    print("Starting from node", source, ":")
    dijkstra(graph_points, graph, source)
    print()
    print()

