#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;

class Graph
{
public:
    int numNodes;
    vector<vector<pair<int, int>>> adjList;
    vector<tuple<int, int, int>> edges;

    Graph(int n)
    {
        this->numNodes = n;
        this->adjList = vector(n, vector<pair<int, int>>());
    }

    void addEdge(int node1, int node2, int weight)
    {
        adjList[node1].push_back(make_pair(node2, weight));
        adjList[node2].push_back(make_pair(node1, weight));
        edges.push_back(make_tuple(node1, node2, weight));
    }

    bool checkCycle(int source, int destination)
    {
        vector<int> queue = {source};
        vector<int> visited = {source};

        while (!queue.empty())
        {
            int front = queue[0];
            queue.erase(queue.begin());
            if (front == destination)
                return true;

            vector<pair<int, int>> neighbors = adjList[front];
            for (pair<int, int> neighbor : neighbors)
            {
                int item = neighbor.first;

                if (find(visited.begin(), visited.end(), item) == visited.end())
                {
                    visited.push_back(item);
                    queue.push_back(item);
                }
            }
        }

        return false;
    }

    void bfs()
    {
        vector<int> queue = {0};
        vector<int> visited = {0};
        vector<int> travelSequence;

        while (!queue.empty())
        {
            int front = queue[0];
            queue.erase(queue.begin());
            travelSequence.push_back(front);
            vector<pair<int, int>> neighbors = adjList[front];

            for (pair<int, int> neighbor : neighbors)
            {
                int item = neighbor.first;

                if (find(visited.begin(), visited.end(), item) == visited.end())
                {
                    visited.push_back(item);
                    queue.push_back(item);
                }
            }
        }

        for (int i = 0; i < travelSequence.size(); i++)
        {
            cout << travelSequence[i] << " ";
        }
        cout << endl;
    }
};

void prims(Graph graph)
{
    int currNode = 0;
    int treeNumNodes = 1;
    int minCost = 0;
    vector<int> visited = {0};
    Graph spanningTree(graph.numNodes);

    while (treeNumNodes != graph.numNodes)
    {
        pair<int, int> minWeightEdge = {-1, INT_MAX};

        for (auto neighbor : graph.adjList[currNode])
        {
            if (find(visited.begin(), visited.end(), neighbor.first) == visited.end() && neighbor.second < minWeightEdge.second)
            {
                minWeightEdge = neighbor;
            }
        }

        spanningTree.addEdge(currNode, minWeightEdge.first, minWeightEdge.second);
        minCost += minWeightEdge.second;
        currNode = minWeightEdge.first;
        treeNumNodes++;
        visited.push_back(minWeightEdge.first);
    }

    graph.bfs();
    cout << minCost << endl;
}

void kruskals(Graph graph)
{
    sort(graph.edges.begin(), graph.edges.end());
    Graph spanningTree(graph.numNodes);
    int minCost = 0;

    for (auto edge : graph.edges)
    {
        int node1 = get<0>(edge);
        int node2 = get<0>(edge);
        int weight = get<2>(edge);

        if (spanningTree.checkCycle(node1, node2) == false)
        {
            spanningTree.addEdge(node1, node2, weight);
            minCost += weight;
        }
    }

    spanningTree.bfs();
    cout << minCost << endl;
}

int main()
{
    Graph graph(5);
    graph.addEdge(0, 1, 1);
    graph.addEdge(1, 2, 3);
    graph.addEdge(2, 3, 4);
    graph.addEdge(0, 2, 7);
    graph.addEdge(0, 3, 10);
    graph.addEdge(3, 4, 2);
    graph.addEdge(0, 4, 5);

    prims(graph);
    cout << endl;
    kruskals(graph);

    return 0;
}