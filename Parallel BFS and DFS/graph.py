import multiprocessing

class Graph:
    def __init__(self, vertices):
        self.num_vertices = vertices
        self.adj = [[] for _ in range(vertices)]

    def add_edge(self, u, v):
        self.adj[u].append(v)
        self.adj[v].append(u)

    def parallel_bfs(self, start_node):
        print(f"The parallel BFS of graph from {start_node} is....")

        manager = multiprocessing.Manager()
        visited = manager.list([False] * self.num_vertices)
        q = manager.Queue()
        q.put(start_node)
        visited[start_node] = True

        processes = []
        for _ in range(4):  # 4 parallel workers
            p = multiprocessing.Process(target=worker_bfs, args=(self.adj, visited, q))
            processes.append(p)
            p.start()

        for p in processes:
            p.join()
        print()

    def parallel_dfs(self, start_node):
        print(f"The parallel DFS of graph from {start_node} is....")

        manager = multiprocessing.Manager()
        visited = manager.list([False] * self.num_vertices)
        stack = manager.list([start_node])
        visited[start_node] = True
        lock = manager.Lock()  # Ensure only one process modifies the stack at a time

        processes = []
        for _ in range(4):  # 4 parallel workers
            p = multiprocessing.Process(target=worker_dfs, args=(self.adj, visited, stack, lock))
            processes.append(p)
            p.start()

        for p in processes:
            p.join()
        print()

def worker_bfs(adj, visited, q):
    while not q.empty():
        node = q.get()
        print(node, end=" ", flush=True)

        for neighbor in adj[node]:
            if not visited[neighbor]:
                visited[neighbor] = True
                q.put(neighbor)

def worker_dfs(adj, visited, stack, lock):
    while True:
        lock.acquire()
        if not stack:
            lock.release()
            return

        node = stack.pop()
        lock.release()
        
        print(node, end=" ", flush=True)

        for neighbor in adj[node]:
            if not visited[neighbor]:
                visited[neighbor] = True
                
                lock.acquire()
                stack.append(neighbor)
                lock.release()

if __name__ == "__main__":
    g = Graph(6)
    g.add_edge(0, 1)
    g.add_edge(0, 2)
    g.add_edge(1, 3)
    g.add_edge(1, 4)
    g.add_edge(2, 4)
    g.add_edge(3, 5)
    g.add_edge(4, 5)

    g.parallel_bfs(0)
    g.parallel_dfs(0)