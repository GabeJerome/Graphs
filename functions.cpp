#include "Graphs.h"

bool checkArgs( int argc )
{
    //incorrect numbe of arguments is given, output usage message
    if ( argc != 3 && argc != 4 )
    {
        cout << "Incorrect command line arguments." << endl;
        cout << "Usage: Graphs.exe [graphFileName] [operation] [optional out file name]" << endl;
        cout << "Valid options are:\n1. findCycle \n2. Topological"
            << "\n3. shortestPath \n4. primsMST \n5. Dijkstras \n6. maxFlow"
            << "\n7. kruskalsMST \n8. eulerCircuit" << endl;
        return false;
    }

    return true;
}

void callFuncs( char **argv, int argc )
{
    myGraph graph( argv[1] ), resultGraph;
    vector<int> cycle;
    vector<string> paths;
    string operation = argv[2], fileName = argv[1];
    string outFile;
    int i, start, end, flow;

    //check for correct construction of graph
    if ( graph.isEmpty( ) )
        return;

    if ( argc == 4 )
        //if given set output file name
        outFile = argv[3];
    else
        //create default file name
        outFile = fileName.substr( 0, fileName.find( '.' ) ) + "Out";

    if ( operation == "findCycle" )
    {
        //call findCycle
        cycle = graph.findCycle( );

        //if result is empty, there are no cycles. Else, print cycle
        if ( cycle.empty( ) )
            cout << "This graph has no cycles" << endl;
        else
            printCycle( cycle );
        return;
    }
    if ( operation == "Topological" )
    {
        //call topologicalSort
        resultGraph = graph.topologicalSort( );

        //if result is empty, there is a cycle in the graph. Else run
        if ( resultGraph.isEmpty( ) )
            cout << "This graph is cyclic" << endl;
        else
        {
            cout << "The topological graph is in " << outFile << ".gv" << endl;
            graph.makeDotFile( outFile );
        }
        return;
    }
    if ( operation == "shortestPath" )
    {
        //prompt user for starting point
        cout << "Enter a starting point for the shortest paths: ";
        cin >> start;

        //call shortestPath and print result
        paths = graph.shortestPath( start );
        printPaths( paths, start );
        return;
    }
    if ( operation == "primsMST" )
    {
        //prompt user for startin point
        cout << "Enter a starting point for the minimum spanning tree: ";
        cin >> start;

        //call primsMST with given start
        resultGraph = graph.primsMST( start );

        //if result is empty, the given start was invalid
        if ( resultGraph.isEmpty( ) )
            cout << "That is not a valid input" << endl;
        //else, run and tell the user the file name
        else
        {
            resultGraph.makeDotFile( outFile );
            cout << "The minimum spanning tree is in " << outFile << ".gv" << endl;
        }

        return;
    }
    if ( operation == "Dijkstras" )
    {
        //prompt user for starting point
        cout << "Enter a starting point for Dijkstras: ";
        cin >> start;

        //call Dijkstras
        paths = graph.Dijkstra( start );

        //if paths is empty, the start is invalid. Else print
        if ( paths.empty( ) )
            cout << "That is not a valid start" << endl;
        else
            printPaths( paths, start );
        return;
    }
    if ( operation == "maxFlow" )
    {
        //prompt user for source and sink
        cout << "Enter the source followed by the sink: ";
        cin >> start >> end;
        
        //call FordFulkerson with given source and sink
        flow = graph.FordFulkerson( start, end, resultGraph );

        //if flow is -1, inputs were not valid
        if ( flow == -1 )
            cout << "That is not a valid input" << endl;
        //else, print results
        else
        {
            cout << "The max flow from " << start << " to " << end
                << " is " << flow << endl;
            cout << "The residual graph is in " << outFile << ".gv" << endl;
            resultGraph.makeDotFile( outFile );
        }
        return;
    }
    if ( operation == "kruskalsMST" )
    {
        //call kruskalsMST and make dot file
        resultGraph = graph.kruskalsMST( );
        resultGraph.makeDotFile( outFile );

        //tell user the file name
        cout << "The minimum spanning tree is in " << outFile << ".gv" << endl;
        return;
    }
    if ( operation == "eulerCircuit" )
    {
        //call eulerCiruit
        resultGraph = graph.eulerCircuit( );

        //if result is empty the graph does not have an Euler Circuit
        if ( resultGraph.isEmpty( ) )
            cout << "This graph does not have an Euler Circuit" << endl;
        //else make dot file and inform user
        else
        {
            resultGraph.makeDotFile( outFile );
            cout << "The Euler Circuit is in " << outFile << ".gv" << endl;
        }

        return;
    }

    //if this is reached the operation did not match any valid operations
    //print valid options
    cout << "Your operation is invalid." << endl;
    cout << "Valid options are:\n1. findCycle \n2. Topological"
         << "\n3. shortestPath \n4. primsMST \n5. Dijkstras \n6. maxFlow"
         << "\n7. kruskalsMST \n8. eulerCircuit" << endl;
}

void printCycle( vector<int> &cycle )
{
    int i;

    //print title
    cout << "Cycle: ";

    //loop through vector and print with format
    for ( i = 0; i < cycle.size( ); i++ )
    {
        if ( i % 10 != 0 || i == 0 )
            cout << cycle[i] << " ";
        else
            cout << '\n';
    }
    cout << endl;
}

void printPaths( vector<string> &paths, int start )
{
    int i;

    //loop through vector and print each string
    for ( i = 0; i < paths.size( ); i++ )
    {
        cout << "From " << start << " to " << i << ": ";
        if ( paths[i] == to_string(start) && i != start )
            cout << "Cannot reach " << i << " from " << start << endl;
        else
            cout << paths[i] << endl;
    }
}
