#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

class Graph{
    vector<vector<int>> adj;

    void bfs(int startVertex){
        vector <bool> visited(5,false);
        queue <int> q;
        visited[startVertex] = 1;
        q.push(startVertex);

        while(!q.empty()){
            int current = q.front();
            cout<<current<<" ";
            q.pop();

            for(int i=0;i<5;i++){
                if(adj[current][i] == 1 && visited[i] == false){
                    q.push(i);
                    visited[i] = true;
                }
            }
        }
        cout<<endl;
    }

    void dfsRecursive(int current,vector <bool> state){
        cout<<current<<" ";
        state[current] = true;

        for(int i=0;i<5;i++){
            if(adj[current][i] == 1 && state[i] == false){
                dfsRecursive(i,state);
            }
        }        
    }

public:
    Graph(){
        adj = vector<vector<int>>(5,vector<int>(5,0));
    }

    void insertEdge(int v1,int v2){
        adj[v1][v2] = 1;
        adj[v2][v1] = 1;
    }  

    void display(){
        int start;
        for(int i=0;i<5;i++){
            bool flag = false;
            for(int j=0;j<5;j++){
                if(adj[i][j] == 1){
                    flag = true;
                    break;
                }
            }

            if(flag){
                start = i;
                break;
            }
        }

        cout<<"The bfs traversal of the graph is..."<<endl;
        bfs(start);
        cout<<endl;

        vector <bool> visited(5,false);
        cout<<"the dfs traversal of the graph is..."<<endl;
        dfsRecursive(start,visited);
        cout<<endl;        
    }      
};

int main(){
    Graph g;
    g.insertEdge(0,1);
    g.insertEdge(0,2);
    g.insertEdge(1,4);
    g.insertEdge(2,3);
    g.display();

    return 0;
}