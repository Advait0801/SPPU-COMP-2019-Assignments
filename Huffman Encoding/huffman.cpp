#include<bits/stdc++.h>
using namespace std;

class Node {
public:
    int val;
    string symbol;
    string huffman;
    Node* left;
    Node* right;

    Node(int n, string s) {
        this -> val = n;
        this -> symbol = s;
        this -> left = nullptr;
        this -> right = nullptr;
        this -> huffman = "";
    }
};


struct Compare {
    bool operator()(const Node *l, const Node *r) {
        return l -> val > r -> val;
    }
};


class HuffmanEncoding {
    Node *root;
    priority_queue<Node *, vector<Node *>, Compare> pq;

    void printCodes(Node *node, const string& val = "") {
        string newVal = val + node -> huffman;

        if (node -> left != nullptr) {
            printCodes(node -> left, newVal);
        }

        if (node -> right != nullptr) {
            printCodes(node -> right, newVal);
        }

        if (node -> left == nullptr && node -> right == nullptr) {
            cout<<node -> symbol<<" -> "<<newVal<<endl;
        }
    }

public:
    HuffmanEncoding(vector<string> &arr, vector<int> &freq) {
        this -> root = nullptr;

        int n = arr.size();
        for(int i=0;i<n;i++) {
            Node *node = new Node(freq[i], arr[i]);
            pq.push(node);
        }
    }

    void buildTree() {
        while(pq.size() > 1) {
            Node *l = pq.top();
            pq.pop();
            Node *r = pq.top();
            pq.pop();
            l -> huffman = "0";
            r -> huffman = "1";

            Node *node = new Node(l -> val + r -> val, l -> symbol + r -> symbol);
            node -> left = l;
            node -> right = r;
            pq.push(node);
        }

        this -> root = pq.top();
        pq.pop();
    }

    void display() {
        if(this -> root != nullptr) {
            printCodes(this -> root);
        }
    }
};


int main() {
    vector<string> stringArr = {"a", "b", "c", "d", "e"};
    vector<int> freqArr = {100, 12, 24, 105, 38};

    HuffmanEncoding huffmanEncoding(stringArr, freqArr);
    huffmanEncoding.buildTree();
    huffmanEncoding.display();

    return 0;

}