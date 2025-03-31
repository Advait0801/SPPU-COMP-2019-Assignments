#include<bits/stdc++.h>
using namespace std;

class Graph {
    int numVertices;
    vector<vector<int>> adj;

public:
    Graph(int vertices) {
        this -> numVertices = vertices;
        this -> adj.resize(vertices);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void parallelBFS(int startNode) {
        cout<<"The parallel BFS of graph from "<<startNode<<" is...."<<endl;

        vector<bool> visited(numVertices, false);
        queue<int> q;

        #pragma omp critical
        {
            q.push(startNode);
            visited[startNode] = true;
        }

        #pragma omp parallel
        {
            while(!q.empty()) {
                int node = -1;

                #pragma omp critical
                {
                    if(!q.empty()) {
                        node = q.front();
                        q.pop();
                        cout << node << " ";
                    }
                }

                if(node == -1) break;
                
                vector<int> neighbors;
                {
                    #pragma omp critical
                    neighbors = adj[node];
                }

                for(int neighbor : neighbors) {
                    #pragma omp critical
                    {
                        if (!visited[neighbor]) {
                            visited[neighbor] = true;
                            q.push(neighbor);
                        }
                    }
                }
            }
        }
        cout<<endl;
    }

    void parallelDFS(int startNode) {
        cout<<"The parallel DFS of graph from "<<startNode<<" is...."<<endl;

        vector<bool> visited(numVertices, false);
        stack<int> s;

        #pragma omp critical
        {
            s.push(startNode);
            visited[startNode] = true;
        }

        #pragma omp parallel
        {
            while(!s.empty()) {
                int node = -1;

                #pragma omp critical
                {
                    if (!s.empty()) {
                        node = s.top();
                        s.pop();
                        cout << node << " ";
                    }
                }

                if(node == -1) break;

                vector<int> neighbors;
                {
                    #pragma omp critical
                    neighbors = adj[node];
                }

                for(int neighbor : neighbors) {
                    #pragma omp critical
                    {
                        if (!visited[neighbor]) {
                            visited[neighbor] = true;
                            s.push(neighbor);
                        }
                    }
                }
            }
        }
        cout<<endl;
    }
};

int main() {
    Graph g(6);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 4);
    g.addEdge(3, 5);
    g.addEdge(4, 5);

    g.parallelBFS(0);
    g.parallelDFS(0);

    return 0;
}

// Compile with: g++ -fopenmp -o graph graph.cpp
// Run with: ./graph