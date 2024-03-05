#include<iostream>
#include<queue>
#include<stack>
#include<vector>
#include<algorithm>
using namespace std;

class Node{
    string name = "";
    Node *next = nullptr;
    Node *down = nullptr;

public:
    Node(string n) {
        this -> name = n;
    }

    friend class Graph;
};


class Graph{
    Node *head = nullptr;

    void addEdge(string node1, string node2){
        if(head == nullptr){
            head = new Node(node1);
            head -> next = new Node(node2);
            numNodes++;
        }
        else{
            Node *node = findNode(node1);

            if(node != nullptr){
                while(node -> next != nullptr){
                    node = node -> next;
                }

                node -> next = new Node(node2);
            }
            else {
                node = head;
                while(node -> down != nullptr){
                    node = node -> down;
                } 

                node -> down = new Node(node1);
                node -> down -> next = new Node(node2);
                numNodes++;
            }
        }
    }

    Node *findNode(string name){
        Node *curr = head;

        while(curr != nullptr){
            if(curr -> name == name){
                return curr;
            }

            curr = curr -> down;
        }

        return nullptr;
    }

public:
    int numNodes = 0, numEdges = 0;
    
    void print(){
        Node *currDown = head;

        while(currDown != nullptr){
            Node *curr = currDown;

            while(curr != nullptr){
                cout<<curr -> name<<" ";
                curr = curr -> next;
            }

            cout<<endl;
            currDown = currDown -> down;
        }
    }    

    void addEdges(string node1, string node2){
        addEdge(node1, node2);
        addEdge(node2, node1);
        numEdges++;
    }

    void dfsSolve(Node *node, vector<string> &visited){
        if(node == nullptr) return;

        cout<<node -> name<<" ";
        visited.push_back(node -> name);

        Node *n = findNode(node -> name);
        if(n != nullptr){
            Node *neighbor = n -> next;

            while(neighbor != nullptr){
                if(find(visited.begin(), visited.end(), neighbor -> name) == visited.end()) {
                    dfsSolve(neighbor, visited);
                }

                neighbor = neighbor -> next;
            }
        }
    }

    void dfsRecursive(){
        vector<string> visited;
        dfsSolve(head, visited);
        cout<<endl;
    }

    Node *dfsIterative(string nodeName){
        Node *node = head;
        if(node -> name == nodeName) return node;

        stack<Node *> s;
        vector<Node *> visited;
        s.push(node);

        while(true){
            if(s.empty()) return nullptr;

            node = s.top();
            s.pop();
            visited.push_back(node);

            Node *curr = node -> next;
            while(curr != nullptr){
                if(find(visited.begin(), visited.end(), curr) == visited.end()){
                    if(curr -> name == nodeName) return curr;
                    s.push(curr);
                }

                curr = curr -> next;
            }
        }

        return nullptr;
    }

    void bfsSolve(queue<string> &q, vector<string> &visited){
        if(q.empty()) return;

        string currNodeName = q.front();
        cout<<currNodeName<<" ";
        q.pop();
        visited.push_back(currNodeName);

        Node *node = findNode(currNodeName);
        if(node != nullptr){
            Node *neighbor = node -> next;

            while(neighbor != nullptr){
                if(find(visited.begin(), visited.end(), neighbor -> name) == visited.end()){
                    q.push(neighbor -> name);
                }

                neighbor = neighbor -> next;
            }
        }

        bfsSolve(q, visited);
    }

    Node *bfsIterative(string nodeName){
        Node *node = head;

        if(node -> name == nodeName) return node;

        queue<Node *> q;
        vector<Node *> visited;
        q.push(node);

        while(true){
            if(q.empty()) return nullptr;

            node = q.front();
            q.pop();
            visited.push_back(node);

            Node *curr = node -> next;
            while(curr != nullptr){
                if(find(visited.begin(), visited.end(), curr) == visited.end()){
                    if(curr -> name == nodeName) return curr;
                    q.push(curr);
                }

                curr = curr -> next;
            }
        }
    }
};


int main(){
    Graph g ; 
    g.addEdges( "a" , "b" ) ; 
    g.addEdges( "a" , "c" ) ; 
    g.addEdges( "b" , "d" ) ; 

    std::cout << "Number of nodes: " << g.numNodes << endl ; 
    std::cout << "Number of edges: " << g.numEdges << endl ; 

    std::cout << "Adjacency List" << endl ; 
    g.print() ; 

    std::string dst_node_name ; 
    std::cout << "Enter node name to search: " << endl ; 
    std::cin >> dst_node_name ; 
    Node* solution = g.dfsIterative( dst_node_name ) ; 
    if( solution ) {
        std::cout << "Node found -> " << solution << endl ; 
    }
    else {
        std::cout << "Node not found" << endl ; 
    }

    solution = g.bfsIterative( dst_node_name ) ; 
    if( solution ) {
        std::cout << "Node found -> " << solution << endl ; 
    }
    else {
        std::cout << "Node not found" << endl ; 
    }

    return 0;
}

