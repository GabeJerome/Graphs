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



int findSource( vector<vector<int>> &g );

bool isEmpty( vector<vector<int>> &g );

int findSmallestUnvisited( vector<bool> visited, vector<int> cost );


class myGraph
{
public:
    myGraph();
    myGraph(string graphName);
    myGraph( vector<vector<int>> g );       //This is here for testing purposes only
    myGraph( int size );
    ~myGraph();
    vector<int> findCycle();
    vector<int> topologicalSort( );
    vector<string> shortestPath( int start );
    vector<vector<int>> primsMST( int start );
    friend ostream& operator<<( ostream& out, myGraph &g );

private:
    vector<vector<int>> adjMatrix;
};



#endif //GRAPHS_MYGRAPH_H
