#include<iostream>
#include<vector>
#include<tuple>
#include<algorithm>
using namespace std;

class Graph{
public:
    int numNodes;
    vector<vector<pair<int, int>>> adjList;
    vector<tuple<int, int, int>> edges;

    Graph(int n){
        this -> numNodes = n;
        this -> adjList = vector(n, vector<pair<int, int>>());
    }

    void addEdge(int node1, int node2, int weight){
        adjList[node1].push_back(make_pair(node2, weight));
        adjList[node2].push_back(make_pair(node1, weight));
        edges.push_back(make_tuple(node1, node2, weight));
    }

    bool checkCycle(int source, int destination){
        vector<int> queue = {source};
        vector<int> visited = {source};

        while(!queue.empty()){
            int front = queue[0];
            queue.erase(queue.begin());
            if(front == destination) return true;

            vector<pair<int, int>> neighbors = adjList[front];
            for(pair<int, int> neighbor : neighbors){
                int item = neighbor.first;

                if(find(visited.begin(), visited.end(), item) == visited.end()){
                    visited.push_back(item);
                    queue.push_back(item);
                }
            }
        }

        return false;
    }

    void bfs(){
        vector<int> queue = {0};
        vector<int> visited = {0};
        vector<int> travelSequence;

        while(!queue.empty()){
            int front = queue[0];
            queue.erase(queue.begin());
            travelSequence.push_back(front);
            vector<pair<int, int>> neighbors = adjList[front];

            for(pair<int, int> neighbor : neighbors){
                int item = neighbor.first;

                if(find(visited.begin(), visited.end(), item) == visited.end()){
                    visited.push_back(item);
                    queue.push_back(item);
                }
            }
        }

        for(int i=0;i<travelSequence.size();i++){
            cout<<travelSequence[i]<<" ";
        }
        cout<<endl;
    }
};


void prims(Graph graph){
    int currNode = 0;
    int treeNumNodes = 1;
    int minCost = 0;
    vector<int> visited = {0};
    Graph spanningTree(graph.numNodes);

    while(treeNumNodes != graph.numNodes){
        
    }
}