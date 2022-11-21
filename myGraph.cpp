//
// Created by 7537969 on 11/14/2022.
//

#include "myGraph.h"



myGraph::myGraph ( )
= default;


//creates graph from file.
//file format is an adjacency matrix with weights and -1 to mark the
//  end of a row.
myGraph::myGraph ( string graphName )
{
    ifstream fin;
    int x;
    vector<int> tmp;

    /********** Change this between VS and CLion **********/
    fin.open("../../../" + graphName );
    if(!fin.is_open())
    {
        cout << "Cannot open file: " << graphName << endl;
        return;
    }

    //read a single value in
    while(fin >> x)
    {
        //if -1 it is the end of the row
        if ( x == -1 )
        {
            //push row and clear
            adjMatrix.push_back( tmp );
            tmp.clear( );
        }
        //push to temp
        else
            tmp.push_back( x );
    }
}



myGraph::myGraph( vector<vector<int>> g )
{
    adjMatrix = g;
}

myGraph::myGraph( int size )
{
    int i, j;
    vector<int> tmp;

    for ( i = 0; i < size; i++ )
    {
        for ( j = 0; j < size; j++ )
            tmp.push_back( 0 );
        adjMatrix.push_back( tmp );
        tmp.clear( );
    }
}



myGraph::~myGraph ( )
{
}

void myGraph::addEdge( int from, int to, int weight )
{
    adjMatrix[from][to] = weight;
}



vector<int> myGraph::findCycle ( )
{
    vector<vector<int>> tmpMatrix = adjMatrix;
    vector<int> result;
    queue<int> Q;
    int *inDegree = nullptr;
    int size = adjMatrix.size();
    int i, j, tmp;

    //allocate array
    inDegree = new (nothrow) int[size];
    if ( inDegree == nullptr )
    {
        cout << "error allocating memory in findCycle" << endl;
        return vector<int>( );
    }

    //initialize to zero
    for ( i = 0; i < size; i++ )
        inDegree[i] = 0;
    

    //compute in-degree of each vertex
    for(i = 0; i < size; i++)
    {
        for(j = 0; j < size; j++)
        {
            if(tmpMatrix[i][j] != 0)
                inDegree[j]++;
        }
    }

    //fill queue with vertices of in-degree 0
    for ( i = 0; i < size; i++ )
    {
        if ( inDegree[i] == 0 )
            Q.push( i );
    }

    //loop until queue is empty
    while ( !Q.empty( ) )
    {
        //pop and top queue
        tmp = Q.front( );
        Q.pop( );

        //decrement self
        inDegree[tmp]--;

        //loop through current row
        for ( i = 0; i < size; i++ )
        {
            //if there is an edge decrement and push to queue if it becomes zero
            if ( tmpMatrix[tmp][i] > 0 && --inDegree[i] == 0 )
                Q.push( i );
        }
    }

    //push all vertices that were not completely explored
    //will be empty ifno cycle
    for ( i = 0; i < size; i++ )
    {
        if ( inDegree[i] >= 0 )
            result.push_back( i );
    }

    return result;
}

vector<int> myGraph::topologicalSort( )
{
    vector<vector<int>> tmpMatrix;
    vector<int> result;
    int i, j, size = adjMatrix.size( );
    
    //determine if it is acyclic
    if (!findCycle( ).empty( ) )
        return vector<int>( );

    //created a temp matrix to preserve original
    tmpMatrix = adjMatrix;
    
    //loop until matrix is all -1
    while ( !isEmpty(tmpMatrix) )
    {
        //locate the index of the source
        i = findSource( tmpMatrix );
        if ( i == -1 )
            return vector<int>( );

        //push back source and delete the row and column
        result.push_back( i );
        for ( j = 0; j < size; j++ )
        {
            if(tmpMatrix[i][j] != -1 )
                tmpMatrix[i][j] = 0;
            tmpMatrix[j][i] = -1;
        }
    }

    return result;
}

vector<string> myGraph::shortestPath( int start )
{
    vector<vector<int>> tmpMatrix = adjMatrix;
    vector<string> result;
    vector<bool> visited;
    vector<int> distance;
    queue<int> Q;
    int i, j, curr, size = adjMatrix.size( );

    //initialize all structures
    for ( i = 0; i < size; i++ )
    {
        result.push_back( "" + start );
        visited.push_back( false );
        distance.push_back( INT_MAX );
    }

    //set start
    distance[start] = 0;
    result[start] = to_string(start);

    //push start to queue
    Q.push( start );

    //while the queue is not empty
    while ( !Q.empty( ) )
    {
        //pop and top queue
        curr = Q.front( );
        Q.pop( );

        //iterate through row for out-edges
        for ( i = 0; i < size; i++ )
        {
            //if an edge exists, push it to the queue
            if ( tmpMatrix[curr][i] > 0 && !visited[i] )
                Q.push( i );

            //if the new distance is smaller than the current distance, replace
            if ( tmpMatrix[curr][i] > 0 && distance[curr] + 1 < distance[i] )
            {
                distance[i] = distance[curr] + 1;
                result[i] = result[curr] + " " + to_string(i);
            }
        }

        //set visited to true for current vertex
        visited[curr] = true;
    }

    return result;
}



vector<vector<int>> myGraph::primsMST( int start )
{
    int i, j, size = adjMatrix.size();

    //use struct edge for second?
    priority_queue<edge> PQ;
    //set<int> S;
    edge tmp, next;
    vector<int> cost( size );
    vector<bool> visited( size );
    vector<string> paths( size );
    vector<vector<int>> result(size, vector<int>(size) );

    if ( start >= size || start < 0 )
        return result;

    /*tmp.from = start;
    tmp.to = start;
    tmp.cost = 0;*/

    //PQ.push( tmp );
    //S.insert( start );

    for ( i = 0; i < size; i++ )
    {
        if ( adjMatrix[start][i] )
        {
            tmp.from = start;
            tmp.to = i;
            tmp.cost = adjMatrix[start][i];
            PQ.push( tmp );
        }
    }

    visited[start] = true;

    while ( !PQ.empty( ) )
    {
        tmp = PQ.top( );
        PQ.pop( );

        if ( !visited[tmp.to] )
        {
            //S.insert(tmp.second.to);
            //cost[tmp.second] = tmp.first;

            //add tmp to graph
            result[tmp.from][tmp.to] = tmp.cost;
            result[tmp.to][tmp.from] = tmp.cost;

            //push all out edges from tmp
            for ( i = 0; i < size; i++ )
            {
                if ( adjMatrix[tmp.to][i] && !visited[i] )
                {
                    next.from = tmp.to;
                    next.to = i;
                    next.cost = adjMatrix[tmp.to][i];
                    PQ.push( next );
                }
            }

            //result[tmp.second.from][tmp.second.to] = tmp.first;

            visited[tmp.to] = true;
        }
    }
    

    /*for ( i = 0; i < size; i++ )
    {
        cost.push_back( INT_MAX );
        visited.push_back( false );
        paths.push_back( "" );
    }
    cost[start] = 0;
    paths[start] = to_string(start );
*/

    //while ( find( visited.begin( ), visited.end( ), false ) != visited.end( ) )
    //{/*
    //    curr = findSmallestUnvisited( visited, cost );
    //    if ( curr == -1 )
    //        return paths;*/

    //    curr = 0;
    //    while ( visited[curr] || cost[curr] == INT_MAX )
    //    {
    //        if ( ++curr >= size )
    //            return paths;
    //    }
    //    for ( i = 0; i < size; i++ )
    //    {
    //        if ( adjMatrix[curr][i] != 0 && cost[curr] + adjMatrix[curr][i] < cost[i] )
    //        {
    //            cost[i] = cost[curr] + adjMatrix[curr][i];
    //            paths[i] = paths[curr] + " " + to_string(i);
    //        }
    //    }
    //    visited[curr] = true;
    //}

    ///*for ( i = 0; i < size; i++ )
    //    paths[i] = paths[i] + " cost: " + to_string(cost[i]);*/

    return result;
}




int findSource( vector<vector<int>> &g )
{
    int i, j, size = g.size();
    bool found = false;
    
    //column loop
    for ( i = 0; i < size; i++ )
    {
        //row loop
        for ( j = 0; !found && j < size; j++ )
        {
            //set found if not zero
            if ( g[j][i] != 0 )
                found = true;
        }
        
        //return column if it has all zeroes
        if ( !found )
            return i;

        //reset found to false
        found = false;
    }

    //return -1 if no source
    return -1;
}

bool isEmpty( vector<vector<int>> &g )
{
    int i, j, size = g.size( );

    //row loop
    for ( i = 0; i < size; i++ )
    {
        //column loop
        for ( j = 0; j < size; j++ )
        {
            //check for all -1's
            if ( g[i][j] != -1 )
                return false;
        }
    }

    return true;
}



int findSmallestUnvisited( vector<bool> visited, vector<int> cost )
{
    int i, size = visited.size( ), min = 0;
    bool found = false;

    while ( cost[min] == INT_MAX || visited[min] )
        min++;

    for ( i = 0; i < size; i++ )
    {
        if ( !visited[i] && cost[i] <= cost[min] )
        {
            min = i;
            found = true;
        }
    }

    if ( found )
        return min;
    else
        return -1;
}



ostream &operator<< ( ostream &out, myGraph &g )
{
    int size = g.adjMatrix.size();
    int i, j;

    //row loop
    for(i = 0; i < size; i++)
    {
        //column loop
        for(j = 0; j < size; j++)
        {
            //output with formatting
            out << g.adjMatrix[i][j];
            if(j == size - 1)
                out << '\n';
            else
                out << "  ";
        }
    }

    //return ostream
    return out;
}
