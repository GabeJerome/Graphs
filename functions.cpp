#include "Graphs.h"

bool interpretDOT( string &fileName, myGraph &g )
{
    ifstream fin;
    bool directed;
    string temp;
    vector<string> lines;

    fin.open( fileName );
    if ( !fin.is_open( ) )
        return false;

    //read whole file in
    while ( getline( fin, temp ) )
    {
        //ignore comments
        temp.erase( temp.find( "//" ), string::npos );

        //ignore empty lines
        if(!temp.empty() )
            lines.push_back( temp );
    }
    

    return true;
}