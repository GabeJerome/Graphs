//
// Created by 7537969 on 11/14/2022.
//

#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <string>
#include <algorithm>
#include <set>
#include <utility>


using namespace std;

#ifndef GRAPHS_MYGRAPH_H
#define GRAPHS_MYGRAPH_H

struct edge
{
    int from = 0;
    int to = 0;
    int cost = 0;
    bool operator<( const edge &rhs ) const { return cost < rhs.cost; }
    bool operator>( const edge &rhs ) const { return cost > rhs.cost; }
};



void pushSources( vector<vector<int>> &g, queue<edge> &Q );

bool isEmpty( vector<vector<int>> &g );

bool isSource( vector<vector<int>> &g, int vertex );




class myGraph
{
public:
    myGraph();
    myGraph(string filName);
    myGraph( vector<vector<int>> g );       //This is here for testing purposes only
    myGraph( int size );
    ~myGraph();
    void addEdge( int from, int to, int weight = 1 );
    void removeEdge( int from, int to );
    vector<int> findCycle();
    myGraph topologicalSort( );
    vector<string> shortestPath( int start );
    myGraph primsMST( int start );
    vector<string> Dijkstra( int start );
    int FordFulkerson( int s, int t );
    vector<int> BFS( int s, int t );
    myGraph kruskalsMST( );
    bool isCyclicUndirected( int v, vector<bool> visited, int last );

    friend ostream& operator<<( ostream& out, myGraph &g );
    friend bool operator==( const myGraph &l, const myGraph &r );
    friend void readDot( ifstream &fin, myGraph &g );
    friend void readAdjMatrix( ifstream &fin, myGraph &g );

private:
    vector<vector<int>> adjMatrix;
};



#endif //GRAPHS_MYGRAPH_H
