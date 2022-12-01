//
// Created by 7537969 on 11/14/2022.
//

#include "myGraph.h"


//default constructor
myGraph::myGraph ( )
= default;


//creates graph from file.
//file format is an adjacency matrix with weights and -1 to mark the
//  end of a row.
myGraph::myGraph ( string fileName )
{
    ifstream fin;
    string tmp;

    /********** Change this between VS and CLion **********/
    fin.open("../../../" + fileName );
    if(!fin.is_open())
    {
        cout << "Cannot open file: " << fileName << endl;
        return;
    }

    //read file extension and call appropriate function
    if ( fileName.substr( fileName.find( '.' ), string::npos ) == ".gv" )
        readDot( fin, *this );
    else
        readAdjMatrix( fin, *this );
}



myGraph::myGraph( vector<vector<int>> g )
{
    adjMatrix = g;
}

myGraph::myGraph( int size )
{
    int i, j;
    vector<int> tmp;

    //create empty graph with given size
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
    //set point to given cost
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

myGraph myGraph::topologicalSort( )
{
    vector<vector<int>> tmpMatrix;
    vector<int> tmpSource;
    int i, j, size = adjMatrix.size( );
    myGraph result(size);
    queue<edge> Q;
    edge curr, tmpEdge;
    bool found;
    
    //determine if it is acyclic
    if (!findCycle( ).empty( ) )
        return result;

    //create a temp matrix to preserve original
    tmpMatrix = adjMatrix;

    pushSources( tmpMatrix, Q );
    

    //loop until queue is empty
    while ( !Q.empty() )
    {
        //top and pop queue
        curr = Q.front( );
        Q.pop( );

        //add the current edge to the result
        result.addEdge( curr.from, curr.to, curr.cost );

        //search current vertex for outgoing edges
        for ( i = 0; i < size; i++ )
        {
            //if there is an outgoing edge
            if ( tmpMatrix[curr.to][i] != 0 )
            {
                //set cost of edge and delete edge
                tmpEdge.cost = tmpMatrix[curr.to][i];
                tmpMatrix[curr.to][i] = 0;

                //if the destination vertex is a new source, add to queue
                if ( isSource( tmpMatrix, i ) )
                {
                    tmpEdge.from = curr.to;
                    tmpEdge.to = i;
                    Q.push( tmpEdge );
                }
            }
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



/* This is Prim's algorithm to find the minimum spanning tree
of a graph. I used a priority queue to keep track of my edges
because it takes care of find the smallest edge for me. This
way, I do not have to perform my own search throug the edges. */
myGraph myGraph::primsMST( int start )
{
    int i, j, size = adjMatrix.size();
    priority_queue<edge> PQ;
    edge tmp, next;
    vector<int> cost( size );
    vector<bool> visited( size );
    vector<string> paths( size );
    myGraph result( size );

    //check for valid starting point
    if ( start >= size || start < 0 )
        return result;

    //check starting vertex for outgoing edges
    for ( i = 0; i < size; i++ )
    {
        //if this is an outgoing edge push it to the queue
        if ( adjMatrix[start][i] )
        {
            tmp.from = start;
            tmp.to = i;
            tmp.cost = adjMatrix[start][i];
            PQ.push( tmp );
        }
    }

    //set visited to true
    visited[start] = true;

    //loop until the priority queue is empty
    while ( !PQ.empty( ) )
    {
        tmp = PQ.top( );
        PQ.pop( );

        if ( !visited[tmp.to] )
        {
            //add tmp to graph
            result.addEdge( tmp.from, tmp.to, tmp.cost );
            result.addEdge( tmp.to, tmp.from, tmp.cost );

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

            //set visited to true for current vertex
            visited[tmp.to] = true;
        }
    }

    return result;
}

vector<string> myGraph::Dijkstra( int start )
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
    result[start] = to_string( start );

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
            if ( tmpMatrix[curr][i] > 0 && distance[curr] + tmpMatrix[curr][i] < distance[i] )
            {
                distance[i] = distance[curr] + tmpMatrix[curr][i];
                result[i] = result[curr] + " " + to_string( i );
            }
        }

        //set visited to true for current vertex
        visited[curr] = true;
    }

    return result;
}




void pushSources( vector<vector<int>> &g, queue<edge> &Q )
{
    int i, j, size = g.size();
    edge tmp;

    //call isSource for each vertex and push if it is
    for ( i = 0; i < size; i++ )
    {
        if(isSource(g, i ) )
        {
            tmp.from = i;
            tmp.to = i;
            tmp.cost = 0;
            Q.push( tmp );
        }
    }
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



bool isSource( vector<vector<int>> &g, int vertex )
{
    int i, size = g.size();

    //search the column for a non-zero value
    for ( i = 0; i < size; i++ )
    {
        //return false if not zero
        if ( g[i][vertex] )
            return false;
    }

    return true;
}



void readDot( ifstream &fin, myGraph &g )
{
    bool directed = false;
    string temp;
    vector<string> lines;
    int i, size = 0, space, first, second, weight;

    //read whole file in
    while ( getline( fin, temp ) )
    {
        //ignore comments
        auto t = temp.find( "//" );
        if(t != string::npos )
            temp.erase( t, string::npos );

        //ignore empty lines
        if ( !temp.empty( ) && temp.find_first_of( "{}" ) == string::npos || temp.find( "raph" ) != string::npos )
        {
            //remove - and >
            temp.erase( remove( temp.begin( ), temp.end( ), '-' ), temp.end( ) );
            temp.erase( remove( temp.begin( ), temp.end( ), '>' ), temp.end( ) );
            temp.erase( remove( temp.begin( ), temp.end( ), '[' ), temp.end( ) );
            temp.erase( remove( temp.begin( ), temp.end( ), ']' ), temp.end( ) );
            lines.push_back( temp );
        }
    }

    if ( lines[0].find("digraph") != string::npos )
        directed = true;

    for ( i = 1; i < lines.size(); i++ )
    {
        space = lines[i].find( " " );
        first = stoi( lines[i].substr( 0, space ) );
        second = stoi( lines[i].substr( space, string::npos ) );

        if ( first > size )
            size = first;
        if ( second > size )
            size = second;
    }
    size++;

    myGraph tempGraph( size );

    for ( i = 1; i < lines.size(); i++ )
    {
        if ( lines[i].find( "weight" ) != string::npos )
            weight = stoi( lines[i].substr( lines[i].find( "=" ) + 1, string::npos ) );
        else
            weight = 1;

        space = lines[i].find( " " );
        first = stoi( lines[i].substr( 0, space ) );
        second = stoi( lines[i].substr( space, string::npos ) );

        tempGraph.addEdge( first, second, weight );
        if ( !directed )
            tempGraph.addEdge( second, first, weight );
    }

    g = tempGraph;
}



void readAdjMatrix( ifstream &fin, myGraph &g )
{
    int x;
    vector<int> tmp;

    //read a single value in
    while ( fin >> x )
    {
        //if -1 it is the end of the row
        if ( x == -1 )
        {
            //push row and clear
            g.adjMatrix.push_back( tmp );
            tmp.clear( );
        }
        //push to temp
        else
            tmp.push_back( x );
    }
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



bool operator==( const myGraph &l, const myGraph &r )
{
    //use vector compare
    return l.adjMatrix == r.adjMatrix;
}