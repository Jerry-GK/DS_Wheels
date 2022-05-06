//This header implements a graph, represented by an adjacency list
#pragma once
#include<cstdio>
#include<vector>
#include<queue>
#include<stdlib.h>
#include <iostream>
using namespace std;

struct _vert
{
    int index;
    struct _vert *next;
    int weight;//
};
typedef struct _vert vert;
typedef struct PathAndLen//this structure contains a path array and an int length, using for function's return
{
    vector<int> path;
    int len;
}PathAndLen;

class alGraph
{
#define MAX_SIZE 1000
public:
    int vertex_num;
    int edge_num;
    int total_weight;
    vert* g[MAX_SIZE];

    alGraph(int ver_num);
    
    void AddEdge(int i, int j,int w);//add an edge i->j(with weight w, w=0 if no such a input parameter)
    void AddDoubleEdge(int i, int j,int w);//add an bidirectional edge i<->j(with weight w, w=0 if no such a input parameter)
    void ChangeWeight(int i, int j, int w);//change the weight of edge i->j to w
    int GetWeight(int i,int j);//get the weight of vertex i->j, return -1 if not adjacent
    void DeleteEdge(int i, int j);//add the edge i->j
    alGraph Copy();//return a copy of this graph
    alGraph Reverse();//return the reverse graph of G

    int GetOutDegree(int i);//get the outdegree of vertex i (i = 0, 1, 2 .... vertex_num - 1)
    int GetInDegree(int i);//get the indegree of vertex i (i = 0, 1, 2 .... vertex_num - 1)
    void ShowGraph();

    int WeaklyConnectedComponents();//get the number of weakly connected components
    int StronglyConnectedComponents();//get the number of strongly connected components
    int ArticulationVertices();//ouput and get the number of articulation vertices(vertex whose removal will disconnect the rest of the graph)
    //return -1 if the graph is not connected.

    bool isCyclic();//judge if there is a circle in the graph
    vector<int> TopSort();//do the topological sort for the graph, return a vector storing the sorting result. 

    PathAndLen UnweightedShortestPath(int i, int j);//get the shortest path and its length, regardless of weight.
    int Dijkstra(int i,int j,vector<int> *path);//get the shortest path(weighted) using Dijkstra algorithm,out put the path if ifOutput=="Output"
    int SecLen(int i,int j,vector<int> *path);//get the second shortest path(weighted), out put the path if ifOutput=="Output"
    int CriticalLen(int source,int end);//suppose that G is an AOE net, this function returns the length of the critical path of G
    int Diameter();//get the length(positively weighted) of the graph. return -1 if it's not acyclic

    int MaxFlow(int source, int end);//return the max flow from source to end (circle allowed) 

    alGraph MST_Prim();//use Prim's algorithm ro find the minimum spanning tree of the graph
    alGraph MST_Kruskal();//use Kruskal's algorithm ro find the minimum spanning tree of the graph
    bool EulerCircuit(int start);//return true if a Euler Circuit exisits, and output it with start as the starting vertex

    void DFS_TEST(int start);

private:
    int indeg[MAX_SIZE];//indegree array
    bool inRange(int i);//judge if a index of a vertex is legal
    void solve(int id,int MaxPath[MAX_SIZE],int ind[MAX_SIZE]);
    void DFS_SCC_1(int i,int* known,int* Num, int &counter);
    void DFS_SCC_2(alGraph& Gr,int i,int* known);
    void DFS_BCC(int i,int* knwon,alGraph& alg,int* Num,int* Parent,int& counter);
    int AssignLow(alGraph G,int i,int *Num,int* Low);
    void DFS_EC(alGraph& G, int start,int& maxTravel);
    int max(int a, int b);
};