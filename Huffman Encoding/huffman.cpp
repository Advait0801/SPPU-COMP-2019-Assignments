#include<bits/stdc++.h>
using namespace std;

class Node {
public:
    int val;
    string symbol;
    string huffman;
    Node *left;
    Node *right;

    Node(int n, string s) {
        this -> val = n;
        this -> symbol = s;
        this -> huffman = "";
        this -> left = nullptr;
        this -> right = nullptr;
    }
};


struct Compare {
    bool operator()(const Node *a, const Node *b) {
        return a -> val > b -> val;
    }
};


class HuffmanEncoding {
    Node *root;
    string inputText;
    unordered_map<string, int> freqs;
    unordered_map<string, string> codes;
    priority_queue<Node *, vector<Node *>, Compare> pq;

    void encode(Node *node, const string &val = "") {
        string newVal = val + node -> huffman;

        if(node -> left != nullptr) {
            encode(node -> left, newVal);
        }
        if(node -> right != nullptr) {
            encode(node -> right, newVal);
        }

        if(node -> left == nullptr && node -> right == nullptr) {
            codes[node -> symbol] = newVal;
        }
    }

public:
    HuffmanEncoding(string text) {
        this -> inputText = text;
        this -> root = nullptr;

        for(char c : inputText) {
            string s(1, c);
            freqs[s]++;
        }

        for(auto it : freqs) {
            Node *node = new Node(it.second, it.first);
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

    void displayResult() {
        cout<<"The character coding is as follows: "<<endl;
        encode(root);
        for(auto it : codes) {
            cout<<it.first<<" --> "<<it.second<<endl;
        }
        cout<<endl;

        string encodedText = "";
        for(char c : inputText) {
            string s(1, c);
            encodedText += codes[s];
        }

        cout<<"The encoded text is.."<<endl;
        cout<<encodedText<<endl;
    }
};


int main() {
    string text;
    cout<<"Enter text to encode"<<endl;
    cin>>text;

    HuffmanEncoding he(text);
    he.buildTree();
    he.displayResult();

    return 0;
}