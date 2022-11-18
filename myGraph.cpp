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

    while(fin >> x)
    {
        if ( x == -1 )
        {
            adjMatrix.push_back( tmp );
            tmp.clear( );
        }
        else
            tmp.push_back( x );
    }

}



myGraph::myGraph( vector<vector<int>> g )
{
    adjMatrix = g;
}



myGraph::~myGraph ( )
{
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

    if (!findCycle( ).empty( ) )
        return vector<int>( );

    tmpMatrix = adjMatrix;
    

    while ( !isEmpty(tmpMatrix) )
    {
        i = findSource( tmpMatrix );
        if ( i == -1 )
            return vector<int>( );

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

    for ( i = 0; i < size; i++ )
    {
        result.push_back( "" + start );
        visited.push_back( false );
        distance.push_back( INT_MAX );
    }
    distance[start] = 0;
    result[start] = to_string(start);

    Q.push( start );

    while ( !Q.empty( ) )
    {
        curr = Q.front( );
        Q.pop( );
        for ( i = 0; i < size; i++ )
        {
            if ( tmpMatrix[curr][i] > 0 && !visited[i] )
                Q.push( i );

            if ( tmpMatrix[curr][i] > 0 && distance[curr] + 1 < distance[i] )
            {
                distance[i] = distance[curr] + 1;
                result[i] = result[curr] + " " + to_string(i);
            }
        }

        visited[curr] = true;
    }

    /*for ( i = 0; i < size; i++ )
        result[i].erase( 0, 1 );*/

    return result;
}




int findSource( vector<vector<int>> &g )
{
    int i, j, size = g.size();
    bool found = false;
    
    for ( i = 0; i < size; i++ )
    {
        for ( j = 0; !found && j < size; j++ )
        {
            if ( g[j][i] != 0 )
                found = true;
        }
        
        if ( !found )
            return i;

        found = false;
    }

    return -1;
}

bool isEmpty( vector<vector<int>> &g )
{
    int i, j, size = g.size( );

    for ( i = 0; i < size; i++ )
    {
        for ( j = 0; j < size; j++ )
        {
            if ( g[i][j] != -1 )
                return false;
        }
    }
    return true;
}



ostream &operator<< ( ostream &out, myGraph &g )
{
    int size = g.adjMatrix.size();
    int i, j;

    for(i = 0; i < size; i++)
    {
        for(j = 0; j < size; j++)
        {
            out << g.adjMatrix[i][j];
            if(j == size - 1)
                out << '\n';
            else
                out << "  ";
        }
    }

    return out;
}
