//
// Created by 7537969 on 11/14/2022.
//

#include "myGraph.h"


//default constructor
myGraph::myGraph( )
= default;


//creates graph from file.
//file format is an adjacency matrix with weights and -1 to mark the
//  end of a row.
myGraph::myGraph( string fileName )
{
    ifstream fin;
    string tmp;

    /********** Change this between VS and CLion **********/
    fin.open( "../../../" + fileName );
    if ( !fin.is_open( ) )
    {
        cout << "Cannot open file: " << fileName << endl;
        return;
    }

    //read file extension and call appropriate function
    if ( fileName.substr( fileName.find( '.' ), string::npos ) == ".gv" )
        readDot( fin, *this );
    else
        readAdjMatrix( fin, *this );

    fin.close( );
}



myGraph::myGraph( vector<vector<int>> &g )
{
    //set adjacency matrix to given
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



myGraph::~myGraph( )
{
}

bool myGraph::isEmpty( )
{
    return( adjMatrix.empty() ) ? true : false;
}

void myGraph::addEdge( int from, int to, int weight )
{
    //set point to given cost
    adjMatrix[from][to] = weight;
}

void myGraph::removeEdge( int from, int to )
{
    //set edge to 0
    addEdge( from, to, 0 );
}



vector<int> myGraph::findCycle( )
{
    vector<vector<int>> tmpMatrix = adjMatrix;
    vector<int> result;
    queue<int> Q;
    int *inDegree = nullptr;
    int size = adjMatrix.size( );
    int i, j, tmp;

    //allocate array
    inDegree = new ( nothrow ) int[size];
    if ( inDegree == nullptr )
    {
        cout << "error allocating memory in findCycle" << endl;
        return vector<int>( );
    }

    //initialize to zero
    for ( i = 0; i < size; i++ )
        inDegree[i] = 0;


    //compute in-degree of each vertex
    for ( i = 0; i < size; i++ )
    {
        for ( j = 0; j < size; j++ )
        {
            if ( tmpMatrix[i][j] != 0 )
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
    //will be empty if no cycle
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
    myGraph result( size );
    queue<edge> Q;
    edge curr, tmpEdge;
    bool found;

    //determine if it is acyclic
    if ( !findCycle( ).empty( ) )
        return myGraph();

    //create a temp matrix to preserve original
    tmpMatrix = adjMatrix;

    pushSources( tmpMatrix, Q );


    //loop until queue is empty
    while ( !Q.empty( ) )
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

    if ( start >= size || start < 0 )
        return vector<string>( size, to_string(start ) );

    //initialize all structures
    for ( i = 0; i < size; i++ )
    {
        result.push_back( to_string(start) );
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
            if ( tmpMatrix[curr][i] > 0 && distance[curr] + 1 < distance[i] )
            {
                distance[i] = distance[curr] + 1;
                result[i] = result[curr] + " " + to_string( i );
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
    int i, j, size = adjMatrix.size( );
    priority_queue <edge, vector<edge>, greater<edge> > PQ;
    edge tmp, next;
    vector<int> cost( size );
    vector<bool> visited( size );
    vector<string> paths( size );
    myGraph result( size );

    //check for valid starting point
    if ( start >= size || start < 0 )
        return myGraph();

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

    if ( start < 0 || start >= size )
        return vector<string>( );

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



int myGraph::FordFulkerson( int s, int t, myGraph &residual )
{
    residual = adjMatrix;
    vector<int> tmpPath = residual.BFS( s, t );
    int flow = 0, currFlow, i, size, curr, next;

    //check for valid start and end
    if ( s < 0 || s >= adjMatrix.size( ) || t < 0 || t >= adjMatrix.size( ) )
        return -1;

    //while a path can still be found
    while ( !tmpPath.empty( ) )
    {
        currFlow = INT_MAX;
        size = tmpPath.size( );

        for ( i = 0; i < size - 1; i++ )
        {
            curr = tmpPath[i];
            next = tmpPath[i + 1];

            //if edge weight is smallest so far
            if ( residual.adjMatrix[curr][next] < currFlow )
                currFlow = residual.adjMatrix[curr][next];
        }

        for ( i = 0; i < size - 1; i++ )
        {
            curr = tmpPath[i];
            next = tmpPath[i + 1];
            residual.adjMatrix[curr][next] -= currFlow;
            residual.adjMatrix[next][curr] += currFlow;
        }

        //add to flow
        flow += currFlow;

        //find next path
        tmpPath = residual.BFS( s, t );
    }

    return flow;
}



vector<int> myGraph::BFS( int s, int t )
{
    vector<vector<int>> tmpMatrix = adjMatrix;
    vector<vector<int>> result;
    vector<bool> visited;
    vector<int> temp;
    priority_queue<edge> PQ;
    int i, j, size = adjMatrix.size( );
    edge tmpEdge, curr;

    //initialize all structures
    for ( i = 0; i < size; i++ )
    {
        result.push_back( vector<int>( ) );
        visited.push_back( false );
    }

    //set start
    result[s] = { s };

    //push start to queue
    tmpEdge.from = s;
    tmpEdge.to = s;
    tmpEdge.cost = 0;
    PQ.push( tmpEdge );

    //while the queue is not empty
    while ( !PQ.empty( ) )
    {
        //pop and top queue
        curr = PQ.top( );
        PQ.pop( );

        //iterate through row for out-edges
        for ( i = 0; i < size; i++ )
        {
            //if an edge exists, push it to the queue
            if ( tmpMatrix[curr.to][i] > 0 && !visited[i] )
            {
                tmpEdge.from = curr.to;
                tmpEdge.to = i;
                tmpEdge.cost = tmpMatrix[tmpEdge.from][tmpEdge.to];
                PQ.push( tmpEdge );
                temp = result[curr.to];
                temp.push_back( i );
                result[i] = temp;

                if ( i == t )
                    return result[i];
            }
        }

        //set visited to true for current vertex
        visited[curr.to] = true;
    }

    return vector<int>( );
}



bool myGraph::isCyclicUndirected( int curr, vector<bool> visited, int last )
{
    // Mark the current vertex as visited
    visited[curr] = true;

    // Recur for all neighbors of curr
    int i, size = adjMatrix.size( );
    for ( i = 0; i < size; i++ )
    {
        //Recur for unvisited neighbor of curr
        if ( adjMatrix[curr][i] > 0 && !visited[i] )
        {
            if ( isCyclicUndirected( i, visited, curr ) )
                return true;
        }

        //If the neighbor is visited and it is not the
        //previous vertex, there is a cycle
        else if ( adjMatrix[curr][i] > 0 && i != last )
            return true;
    }

    return false;
}

myGraph myGraph::eulerCircuit( )
{
    int curr, count;
    int i, j, size = adjMatrix.size();
    myGraph result( size );
    vector<vector<int>> cpy = adjMatrix;

    //find start. If -1, graph is invalid
    curr = findOddVertex( cpy );
    if ( curr == -1 )
        return myGraph( );


    //function call
    eulerRecurs( cpy, result, curr );

    return result;
}

void myGraph::makeDotFile( string &name )
{
    ofstream fout;
    string header = "graph A {";
    string connector = " -- ";
    bool directed = isDirected( adjMatrix );
    int i, j, size = adjMatrix.size();


    /**** CHANGE THIS BETWEEN CLION AND VS ****/
    fout.open( "../../../" + name + ".gv" );
    if ( !fout.is_open( ) )
    {
        cout << "Could not open file: " << name << ".gv" << endl;
        return;
    }

    //if graph is directed, change print options
    if ( directed )
    {
        header = "digraph A {";
        connector = " -> ";
    }

    //print header
    fout << header << "\n";

    //if directed, print every edge
    if ( directed )
    {
        for ( i = 0; i < size; i++ )
        {
            for ( j = 0; j < size; j++ )
            {
                if ( adjMatrix[i][j] > 0 )
                    fout << "\t" << i << connector << j << " [weight = " << adjMatrix[i][j] << "]\n";
            }
        }
    }
    //if undirected, only need to check half of matrix
    else
    {
        for ( i = 0; i < size; i++ )
        {
            for ( j = i; j < size; j++ )
            {
                if ( adjMatrix[i][j] > 0 )
                    fout << "\t" << i << connector << j << " [weight = " << adjMatrix[i][j] << "]\n";
            }
        }
    }

    //print close bracket
    fout << "}";

    //close the output file
    fout.close( );
}



myGraph myGraph::kruskalsMST( )
{
    int edges = 0, size = adjMatrix.size( ), i, j;
    priority_queue <edge, vector<edge>, greater<edge> > PQ;
    edge tmp;
    myGraph g( size );
    vector<bool> visited( size, false );

    //push all edges into a priority queue
    //this will take care of choosing the smallest edge
    for ( i = 0; i < size; i++ )
    {
        for ( j = i; j < size; j++ )
        {
            if ( adjMatrix[i][j] > 0 )
            {
                tmp.from = i;
                tmp.to = j;
                tmp.cost = adjMatrix[i][j];
                PQ.push( tmp );
            }
        }
    }

    //while we have not reached every node or the PQ is not empty
    while ( edges < size - 1 && !PQ.empty( ) )
    {
        //top and pop queue
        tmp = PQ.top( );
        PQ.pop( );

        //add the edge from the queue and increase edge counter
        g.addEdge( tmp.from, tmp.to, tmp.cost );
        g.addEdge( tmp.to, tmp.from, tmp.cost );
        edges++;

        //check if the added edge created an undirected cycle
        if ( g.isCyclicUndirected( tmp.to, visited, -1 ) )
        {
            //if there is a cycle remove the edge and decrement the counter
            g.removeEdge( tmp.from, tmp.to );
            g.removeEdge( tmp.to, tmp.from );
            edges--;
        }
    }

    //return the result
    return g;
}



void pushSources( vector<vector<int>> &g, queue<edge> &Q )
{
    int i, j, size = g.size( );
    edge tmp;

    //call isSource for each vertex and push if it is
    for ( i = 0; i < size; i++ )
    {
        if ( isSource( g, i ) )
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
    int i, size = g.size( );

    //search the column for a non-zero value
    for ( i = 0; i < size; i++ )
    {
        //return false if not zero
        if ( g[i][vertex] )
            return false;
    }

    return true;
}

int findOddVertex( vector<vector<int>> &g )
{
    int i, j, size = g.size(), sum;
    int numOddVertices = 0;
    int lastOdd;

    //check for empty
    if ( g.empty( ) )
        return -1;

    //loop through each vertex
    for ( i = 0; i < size && numOddVertices <= 2; i++ )
    {
        //initialize sum to 0
        sum = 0;
        for ( j = 0; j < size; j++ )
        {
            //check for outgoing edge
            if ( g[i][j] > 0 )
                sum++;
        }

        //if number of outgoing edges is odd
        if ( sum % 2 != 0 )
        {
            //increase count and set lastOdd
            numOddVertices++;
            lastOdd = i;
        }
    }

    //if number of odd vertices is 2, return one of them
    if ( numOddVertices == 2 )
        return lastOdd;

    //if there are no odd vertices, return 0
    if ( numOddVertices == 0 )
        return 0;

    //else there is no Euler circuit in this graph
    return -1;
}

bool isNextValid( vector<vector<int>> g,  int from, int to )
{
    int i, size = g.size( );
    int count = 0, count1, count2, cost = g[from][to];

    //count out edges
    for ( i = 0; i < size; i++ )
    {
        if ( g[from][i] > 0 )
            count++;
    }

    //if this is the only out edge, it is valid
    if ( count == 1 )
        return true;

    //get number of reachable edges
    count1 = BFSCount( g, from );

    //remove edge
    g[from][to] = 0;

    //get new number of reachable edges
    count2 = BFSCount( g, from );

    //add edge back
    g[from][to] = cost;

    // if count1 is greater, this edge is not valid
    return (count1 > count2 ) ? false : true;
}


int BFSCount( vector<vector<int>> g, int start )
{
    vector<vector<int>> result;
    vector<bool> visited;
    vector<int> temp;
    priority_queue<edge> PQ;
    int i, j, size = g.size( ), count = 0;
    edge tmpEdge, curr;

    //initialize all structures
    for ( i = 0; i < size; i++ )
    {
        result.push_back( vector<int>( ) );
        visited.push_back( false );
    }

    //set start
    result[start] = { start };

    //push start to queue
    tmpEdge.from = start;
    tmpEdge.to = start;
    tmpEdge.cost = 0;
    PQ.push( tmpEdge );

    //while the queue is not empty
    while ( !PQ.empty( ) )
    {
        //pop and top queue
        curr = PQ.top( );
        PQ.pop( );

        if ( !visited[curr.to] )
            count++;

        //iterate through row for out-edges
        for ( i = 0; i < size; i++ )
        {
            //if an edge exists, push it to the queue
            if ( g[curr.to][i] > 0 && !visited[i] )
            {
                tmpEdge.from = curr.to;
                tmpEdge.to = i;
                tmpEdge.cost = g[tmpEdge.from][tmpEdge.to];
                PQ.push( tmpEdge );
            }
        }

        //set visited to true for current vertex
        visited[curr.to] = true;
    }

    return --count;
}



void eulerRecurs( vector<vector<int>> &cpy, myGraph &result, int curr )
{
    int size = cpy.size( ), i;

    //for every outgoing edge of the current vertex
    for ( i = 0; i < size; i++ )
    {
        //if there is a valid edge
        if ( cpy[curr][i] > 0 && isNextValid( cpy, curr, i ) )
        {
            //add the edge to the result and remove it from the current graph
            result.addEdge( curr, i, cpy[curr][i] );
            cpy[curr][i] = 0;
            cpy[i][curr] = 0;

            //recursive call the vertex that the edge is connected to
            eulerRecurs( cpy, result, i );
        }
    }
}

bool isDirected( vector<vector<int>> &g )
{
    int i, j, size = g.size( );

    //check if matrix is symmetric
    for ( i = 0; i < size; i++ )
    {
        for ( j = i; j < size; j++ )
        {
            if ( g[i][j] != g[j][i] )
                return true;
        }
    }

    return false;
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
        if ( t != string::npos )
            temp.erase( t - 1, string::npos );

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
    
    //determine if graph is directed
    if ( lines[0].find( "digraph" ) != string::npos )
        directed = true;

    //get the size of the graph
    for ( i = 1; i < lines.size( ); i++ )
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

    //parse through each line
    for ( i = 1; i < lines.size( ); i++ )
    {
        //if a weight is given set it. Default = 1
        if ( lines[i].find( "weight" ) != string::npos )
            weight = stoi( lines[i].substr( lines[i].find( "=" ) + 1, string::npos ) );
        else
            weight = 1;

        //get which vertices are connected
        space = lines[i].find( " " );
        first = stoi( lines[i].substr( 0, space ) );
        second = stoi( lines[i].substr( space, string::npos ) );

        //add the edge to the graph
        tempGraph.addEdge( first, second, weight );
        if ( !directed )
            tempGraph.addEdge( second, first, weight );
    }

    //set g
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
    int size = g.adjMatrix.size( );
    int i, j;

    //row loop
    for ( i = 0; i < size; i++ )
    {
        //column loop
        for ( j = 0; j < size; j++ )
        {
            //output with formatting
            out << g.adjMatrix[i][j];
            if ( j == size - 1 )
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