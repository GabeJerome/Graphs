#include "Graphs.h"

bool checkArgs( int argc )
{
    if ( argc != 3 && argc != 4 )
    {
        cout << "Incorrect command line arguments." << endl;
        cout << "Usage: Graphs.exe [graphFileName] [operation] [optional out file name]" << endl;
        cout << "operations: findCycle Topological shortestPath primsMST"
            << " Dijkstras maxFlow kruskalsMST eulerCircuit" << endl;
        return false;
    }

    return true;
}

void callFuncs( char **argv, int argc )
{
    myGraph graph( argv[1] ), resultGraph;
    vector<int> cycle;
    string operation = argv[2], outFile = string(argv[1]) + "Out";
    int i, start, end;

    if ( argc == 4 )
        outFile = argv[3];

    if ( operation == "findCycle" )
    {
        cycle = graph.findCycle( );
        if ( cycle.empty( ) )
        {
            cout << "This graph has no cycles" << endl;
            return;
        }
        printCycle( cycle );
        return;
    }
    if ( operation == "Topological" )
    {
        resultGraph = graph.topologicalSort( );
        graph.makeDotFile( outFile );
        return;
    }
    if ( operation == "shortestPath" )
    {
        cout << "Enter a starting point: ";
        cin >> start;

        
    }
}

void printCycle( vector<int> &cycle )
{
    int i;
    cout << "Cycle: ";
    for ( i = 0; i < cycle.size( ); i++ )
    {
        if ( i % 10 != 0 || i == 0 )
            cout << cycle[i] << " ";
        else
            cout << '\n';
    }
    cout << '\n';
}

void printPaths( vector<string> &paths )
{
}
