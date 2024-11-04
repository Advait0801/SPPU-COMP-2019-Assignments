import heapq

class Node:
    def __init__(self, n, s) -> None:
        self.val = n
        self.symbol = s
        self.huffman = ''
        self.left = None
        self.right = None

    def __lt__(self, other):
        return self.val < other.val
    

class HuffmanEncoding:
    def __init__(self, text) -> None:
        self.root = None
        self.input_text = text
        self.codes = {}
        self.pq = []

        self.freqs = {}
        for char in self.input_text:
            if char in self.freqs:
                self.freqs[char] += 1
            else:
                self.freqs[char] = 1

        for key, value in self.freqs.items():
            node = Node(value, key)
            heapq.heappush(self.pq, node)

    def encode(self, node: Node, val=""):
        new_val = val + node.huffman

        if node.left:
            self.encode(node.left, new_val)
        if node.right:
            self.encode(node.right, new_val)

        if not node.left and not node.right:
            self.codes[node.symbol] = new_val

    def build_tree(self):
        while len(self.pq) > 1:
            l = heapq.heappop(self.pq)
            r = heapq.heappop(self.pq)

            l.huffman = '0'
            r.huffman = '1'

            node = Node(l.val + r.val, l.symbol + r.symbol)
            node.left = l
            node.right = r
            heapq.heappush(self.pq, node)

        self.root = heapq.heappop(self.pq)

    def display_result(self):
        print("The character coding is as follows:")
        self.encode(self.root)
        for key, value in self.codes.items():
            print(key + " --> " + value)        

        encoded_text = ''
        for char in self.input_text:
            encoded_text += self.codes.get(char, 0)
        
        print("The encoded text is...")
        print(encoded_text)


text = input("Enter text to encode")
he = HuffmanEncoding(text)
he.build_tree()
he.display_result()