/*
You have a business with several offices; you want to lease phone lines to connect them up with each
other; and the phone company charges different amounts of money to connect different pairs of cities.
You want a set of lines that connects all your offices with a minimum total cost. Solve the problem 
by suggesting appropriate data structures.

Name : Advait Naik
Roll No : 21354
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Node{
    char name;
    int val;
    Node *next, *down;

public:
    Node(char c,int n){
        this -> name = c;
        this -> val = n;
        this -> next = nullptr;
        this -> down = nullptr;
    }

    friend class Graph;
};

class Edge{
    char vertex1, vertex2;
    int weight;

public:
    Edge(){
        this -> vertex1 = '\n';
        this -> vertex2 = '\n';
        this -> weight = 0;
    }

    Edge(char v1,char v2,int val){
        this -> vertex1 = v1;
        this -> vertex2 = v2;
        this -> weight = val;
    }

    friend class Graph;
};

class Graph{
    Node *head = nullptr;

    void addNode(char parentName,char childName,int weight){
        if(this -> head == nullptr){
            this -> head = new Node(parentName,0);
            Node *newNode = new Node(childName,weight);
            this -> head -> next = newNode;
        }
        else{
            Node *current = this -> head;
            Node *previous = nullptr;
            
            bool flag = false;
            while(current != nullptr){
                if(current -> name == parentName){
                    flag = true;
                    Node *neighbor = current;
                    while(neighbor -> next != nullptr){
                        neighbor = neighbor -> next;
                    }
                    Node *newNode = new Node(childName,weight);
                    neighbor -> next = newNode;
                    break;
                }
                previous = current;
                current = current -> down;
            }

            if(flag == false){
                Node *newParent = new Node(parentName,0);
                Node *newchild = new Node(childName,weight);
                previous -> down = newParent;
                newParent -> next = newchild;
            }
        }
    }

public:
    void insertEdge(char v1,char v2,int weight){
        addNode(v1,v2,weight);
        addNode(v2,v1,weight);
    }

    void display(){
        Node *parent = this -> head;
        while(parent != nullptr){
            cout<<parent -> name<<" ----> ";
            Node *child = parent -> next;
            while(child != nullptr){
                cout<<child -> name<<"("<<child -> val<<")"<<" - ";
                child = child -> next;
            }
            cout<<" NULL "<<endl;
            parent = parent -> down;
        }
    }

    void prims(){
        vector <char> visited;
        int minSpanningTreeCost = 0;
        visited.push_back(this -> head -> name);

        while(visited.size() < 5){
            int minCost = 9999;
            Edge minCostEdge;
            for(auto it : visited){
                Node *parent = this -> head;
                while(parent != nullptr){
                    if(parent -> name == it){
                        Node *child = parent -> next;
                        while(child != nullptr){
                            if(find(visited.begin() , visited.end() , child -> name) == visited.end()){
                                if(child -> val < minCost){
                                    minCostEdge.vertex1 = parent -> name;
                                    minCostEdge.vertex2 = child -> name;
                                    minCostEdge.weight = child -> val;
                                    minCost = child -> val;
                                }
                            }
                            child = child -> next;
                        }
                        break;
                    }
                    parent = parent -> down;
                }
            }
            cout<<"Edge Added : "<<minCostEdge.vertex1<<""<<minCostEdge.vertex2<<" Cost = "<<minCostEdge.weight<<endl;
            minSpanningTreeCost = minSpanningTreeCost + minCostEdge.weight;
            visited.push_back(minCostEdge.vertex2);
        }
        cout<<"Minimum Spanning Tree Cost = "<<minSpanningTreeCost<<endl;
    }
};

class graph{          ///////adjecency matrixxx
    vector<vector<int>> cost;

    bool isValidEdge(int v1,int v2,vector<bool> state){
        if(v1 == v2) return false;

        if(state[v1] == false && state[v2] == false) return false;

        if(state[v1] == true && state[v2] == true) return false;

        return true;
    }

public:
    graph(){
        cost = vector<vector<int>>(5,vector<int>(5,9999));
    }

    void insertEdge(int v1,int v2,int weight){
        cost[v1][v2] = weight;
        cost[v1][v2] = weight;
    }

    void prims(){
        vector <bool> visited(5,false);
        visited[0] = true;

        int edges = 0, minSpanningTreeCost = 0;
        while(edges < 4){
            int minCost = 9999;
            int v1 = -1, v2 = -1;
            for(int i=0;i<5;i++){
                for(int j=0;j<5;j++){
                    if(cost[i][j] < minCost){
                        if(isValidEdge(i,j,visited) == true){
                            minCost = cost[i][j];
                            v1 = i;
                            v2 = j;
                        }
                    }
                }
            }


            if(v1 != -1 && v2 != -1){
                cout<<"Edge added: "<<v1<<"-"<<v2<<" cost: "<<minCost<<endl;
                edges++;
                minSpanningTreeCost = minSpanningTreeCost + minCost;
                visited[v1] = true;
                visited[v2] = true;
            }
        }
        cout<<"Minimum Cost of spanning Tree is "<<minSpanningTreeCost<<endl;
    }

    void kruskal(){
        
    }
};

int main(){
    Graph g;
    g.insertEdge('A','B',4);
    g.insertEdge('A','C',3);
    g.insertEdge('A','D',2);
    g.insertEdge('B','C',3);
    g.insertEdge('B','E',6);
    g.insertEdge('C','D',2);
    g.insertEdge('C','E',5);

    g.display();
    g.prims();

    return 0;
}