import heapq

class Node:
    def __init__(self, val, symbol):
        self.val = val
        self.symbol = symbol
        self.huffman = ""
        self.left = None
        self.right = None

    def __lt__(self, other):
        return self.val < other.val
    

class HuffmanEncoding:
    def __init__(self, arr, freq):
        self.root = None
        self.pq = []

        for i in range(len(arr)):
            node = Node(freq[i], arr[i])
            heapq.heappush(self.pq, node)

    def build_tree(self):
        while len(self.pq) > 1:
            l = heapq.heappop(self.pq)
            r = heapq.heappop(self.pq)
            l.huffman = "0"
            r.huffman = "1"

            node = Node(l.val + r.val, l.symbol + r.symbol)
            node.left = l
            node.right = r
            heapq.heappush(self.pq, node)

        self.root = heapq.heappop(self.pq)

    def print_codes(self, node, val=""):
        new_val = val + node.huffman

        if node.left:
            self.print_codes(node.left, new_val)

        if node.right:
            self.print_codes(node.right, new_val)

        if not node.left and not node.right:
            print(f"{node.symbol} -> {new_val}")

    def display(self):
        if self.root:
            self.print_codes(self.root)



string_arr = ["a", "b", "c", "d", "e"]
freq_arr = [100, 12, 24, 105, 38]
huffman_encoding = HuffmanEncoding(string_arr, freq_arr)
huffman_encoding.build_tree()
huffman_encoding.display()