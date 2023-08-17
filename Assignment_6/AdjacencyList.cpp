/*
Represent a given graph using adjacency list to perform DFS and BFS traversal.Use map of the area around the college as the
graph. Identify the prominent landmarks as nodes and perform following operations:
1. create graph
2. display graph
3. DFS traversal
4. BFS traversal
5. Is the graph connected
6. InDegrees and OutDegrees

Name : Advait Naik
Roll No : 21354
*/

#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <queue>
#include <stack>
using namespace std;

class Node{
    string name;
    Node *next, *down;

public:
    Node(string n){
        this -> name = n;
        this -> next = nullptr;
        this -> down = nullptr;
    }

    friend class Graph;
};

class Graph{
    Node *head = nullptr;

    void addNode(string parent,string child){
        if(this -> head == nullptr){
            this -> head = new Node(parent);
            Node *newNode = new Node(child);

            this -> head -> next = newNode;
        }
        else{
            Node *current = this -> head;
            Node *previous = nullptr;
            
            bool flag = false;
            while(current != nullptr){
                if(current -> name == parent){
                    flag = true;
                    Node *neighbor = current;
                    while(neighbor -> next != nullptr){
                        neighbor = neighbor -> next;
                    }
                    Node *newNode = new Node(child);
                    neighbor -> next = newNode;
                    break;
                }
                previous = current;
                current = current -> down;
            }

            if(flag == false){
                Node *newParent = new Node(parent);
                Node *newChild = new Node(child);
                previous -> down = newParent;
                newParent -> next = newChild;
            }
        }        
    }

public:
    void insertEdge(string v1,string v2){
        addNode(v1,v2);
        addNode(v2,v1);
    }

    void print(){
        Node *parent = this -> head;
        while(parent != nullptr){
            cout<<parent -> name<<" ------> ";
            Node *child = parent -> next;
            while(child != nullptr){
                cout<<child -> name<<" - ";
                child = child -> next;
            }
            cout<<" NULL "<<endl;
            parent = parent -> down;
        }
    }

    void degrees(){
        Node *parent = this -> head;
        while(parent != nullptr){
            int degree = 0;
            Node *child = parent -> next;
            while(child != nullptr){
                degree++;
                child = child -> next;
            }
            cout<<parent -> name<<" - "<<degree<<endl;
            parent = parent -> down;
        }
    }

    void bfsTraversal(){
        queue <string> q;
        vector <string> visited;
        q.push(this -> head -> name);
        visited.push_back(this -> head -> name);

        while(true){
            string currentName;
            if(!q.empty()){
                currentName = q.front();
                cout<<currentName<<" ";
                q.pop();
            }

            Node *current = this -> head;
            while(current != nullptr){
                if(current -> name == currentName) break;
                current = current -> down;
            }

            Node *child = current -> next;
            while(child != nullptr){
                if(find(visited.begin() , visited.end() , child -> name) == visited.end()){
                    visited.push_back(child -> name);
                    q.push(child -> name);
                }
                child = child -> next;
            }

            if(q.empty()) return;
        }
    }

    void dfsTraversal(){
        stack <string> s;
        vector <string> visited;
        s.push(this -> head -> name);
        visited.push_back(this -> head -> name);

        while(true){
            string currentName;
            if(!s.empty()){
                currentName = s.top();
                cout<<currentName<<" ";
                s.pop();
            }

            Node *current = this -> head;
            while(current != nullptr){
                if(current -> name == currentName) break;
                current = current -> down;
            }

            Node *child = current -> next;
            while(child != nullptr){
                if(find(visited.begin() , visited.end() , child -> name) == visited.end()){
                    visited.push_back(child -> name);
                    s.push(child -> name);
                }
                child = child -> next;
            }

            if(s.empty()) return;
        }
    }
};

int main(){
    Graph g;
    g.insertEdge( "Katraj" , "PICT" ) ;
    g.insertEdge( "Bharti" , "PICT" ) ; 
    g.insertEdge( "Temple" , "Bharti" ) ;     
    g.print() ; 
    g.degrees() ;
    g.bfsTraversal();
    cout<<endl;
    g.dfsTraversal();

    return 0;
}
