//
// Created by 7537969 on 11/14/2022.
//

#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
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
    bool operator<( const edge &rhs ) const { return !(cost <= rhs.cost); }
};



void pushSources( vector<vector<int>> &g, queue<edge> &Q );

bool isEmpty( vector<vector<int>> &g );

int findSmallestUnvisited( vector<bool> visited, vector<int> cost );

bool isSource( vector<vector<int>> &g, int vertex );


class myGraph
{
public:
    myGraph();
    myGraph(string graphName);
    myGraph( vector<vector<int>> g );       //This is here for testing purposes only
    myGraph( int size );
    ~myGraph();
    void addEdge( int from, int to, int weight = 1 );
    vector<int> findCycle();
    myGraph topologicalSort( );
    vector<string> shortestPath( int start );
    myGraph primsMST( int start );
    friend ostream& operator<<( ostream& out, myGraph &g );
    friend bool operator==( const myGraph &l, const myGraph &r );

private:
    vector<vector<int>> adjMatrix;
};



#endif //GRAPHS_MYGRAPH_H
