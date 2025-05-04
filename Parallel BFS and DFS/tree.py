import multiprocessing
import time

class TreeNode:
    """ Node structure for the binary tree. """
    def __init__(self, val):
        self.val = val
        self.left = None
        self.right = None

class BinaryTree:
    """ Binary tree with parallel BFS and DFS implementations. """
    def __init__(self):
        self.root = None

    def insert(self, val):
        """ Insert a new node into the tree (level-order). """
        if not self.root:
            self.root = TreeNode(val)
            return
        
        queue = [self.root]
        while queue:
            node = queue.pop(0)
            if not node.left:
                node.left = TreeNode(val)
                return
            else:
                queue.append(node.left)
            if not node.right:
                node.right = TreeNode(val)
                return
            else:
                queue.append(node.right)

    def sequential_bfs(self):
        """ Perform sequential BFS. """
        start = time.time()

        if not self.root:
            return
        
        print("Sequential BFS:", end=" ", flush=True)
        queue = [self.root]
        visited = set()

        while queue:
            node = queue.pop(0)
            if node.val not in visited:
                visited.add(node.val)
                print(node.val, end=" ", flush=True)
                if node.left:
                    queue.append(node.left)
                if node.right:
                    queue.append(node.right)

        print()

        end = time.time()
        elapsed_time = (end - start) * 1000  # Convert to milliseconds
        print(f"Time taken: {elapsed_time:.3f} milliseconds")

    def parallel_bfs(self):
        """ Perform parallel BFS using multiprocessing. """
        start = time.time()

        if not self.root:
            return
        
        print("Parallel BFS:", end=" ", flush=True)
        manager = multiprocessing.Manager()
        queue = manager.list([self.root])  # Shared queue for BFS
        visited = manager.dict()
        lock = manager.Lock()

        processes = [multiprocessing.Process(target=bfs_worker, args=(queue, visited, lock)) for _ in range(4)]
        for p in processes:
            p.start()
        for p in processes:
            p.join()
        
        print()

        end = time.time()
        elapsed_time = (end - start) * 1000  # Convert to milliseconds
        print(f"Time taken: {elapsed_time:.3f} milliseconds")

    def sequential_dfs(self):
        """ Perform sequential DFS. """
        start = time.time()

        if not self.root:
            return
        
        print("Sequential DFS:", end=" ", flush=True)
        stack = [self.root]
        visited = set()

        while stack:
            node = stack.pop()
            if node.val not in visited:
                visited.add(node.val)
                print(node.val, end=" ", flush=True)
                if node.right:
                    stack.append(node.right)
                if node.left:
                    stack.append(node.left)

        print()

        end = time.time()
        elapsed_time = (end - start) * 1000  # Convert to milliseconds
        print(f"Time taken: {elapsed_time:.3f} milliseconds")

    def parallel_dfs(self):
        """ Perform parallel DFS using multiprocessing. """
        start = time.time()

        if not self.root:
            return
        
        print("Parallel DFS:", end=" ", flush=True)
        manager = multiprocessing.Manager()
        stack = manager.list([self.root])  # Shared stack for DFS
        visited = manager.dict()
        lock = manager.Lock()

        processes = [multiprocessing.Process(target=dfs_worker, args=(stack, visited, lock)) for _ in range(4)]
        for p in processes:
            p.start()
        for p in processes:
            p.join()

        print()

        end = time.time()
        elapsed_time = (end - start) * 1000  # Convert to milliseconds
        print(f"Time taken: {elapsed_time:.3f} milliseconds")

def bfs_worker(queue, visited, lock):
    """ Parallel BFS Worker function. """
    while True:
        with lock:
            if not queue:
                return
            node = queue.pop(0)

        if node and node.val not in visited:
            visited[node.val] = True
            print(node.val, end=" ", flush=True)
            
            with lock:
                if node.left:
                    queue.append(node.left)
                if node.right:
                    queue.append(node.right)

def dfs_worker(stack, visited, lock):
    """ Parallel DFS Worker function. """
    while True:
        with lock:
            if not stack:
                return
            node = stack.pop()

        if node and node.val not in visited:
            visited[node.val] = True
            print(node.val, end=" ", flush=True)
            
            with lock:
                if node.right:
                    stack.append(node.right)
                if node.left:
                    stack.append(node.left)

if __name__ == "__main__":
    tree = BinaryTree()
    for val in range(1, 8):
        tree.insert(val)

    tree.parallel_bfs()
    tree.sequential_bfs()
    tree.parallel_dfs()
    tree.sequential_dfs()