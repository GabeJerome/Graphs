#include "catch.hpp"


#include "Graphs.h"
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;


TEST_CASE( "file constructor" )
{
    ostringstream sout;

    SECTION( "undirected unweighted graph" )
    {
        myGraph g( "g1.txt" );
        sout << g;
        REQUIRE( sout.str( ) == "0  1  0  0  1  1\n"
            "1  0  1  1  0  1\n"
            "0  1  0  1  0  0\n"
            "0  1  1  0  1  1\n"
            "1  0  0  1  0  1\n"
            "1  1  0  1  1  0\n" );
    }
    SECTION( "undirected weighted graph" )
    {
        myGraph g( "g2.txt" );
        sout << g;
        REQUIRE( sout.str( ) ==
            "0  1  0  0  1  6  1\n"
            "1  0  1  7  0  0  3\n"
            "0  1  0  1  0  0  0\n"
            "0  7  1  0  4  0  1\n"
            "1  0  0  4  0  2  5\n"
            "6  0  0  0  2  0  0\n"
            "1  3  0  1  5  0  0\n" );
    }
    SECTION( "directed unweighted graph" )
    {
        myGraph g( "g3.txt" );
        sout << g;
        REQUIRE( sout.str( ) ==
            "0  1  0  1  0  0\n"
            "0  0  1  0  0  1\n"
            "0  0  0  0  1  1\n"
            "0  0  0  0  0  0\n"
            "0  0  0  1  0  1\n"
            "0  0  0  1  0  0\n" );
    }
    SECTION( "directed unweighted graph" )
    {
        myGraph g( "g4.txt" );
        sout << g;
        REQUIRE( sout.str( ) ==
            "0  4  0  9  0  0\n"
            "0  0  2  0  0  2\n"
            "0  0  0  0  6  7\n"
            "0  0  0  0  0  0\n"
            "0  0  0  2  0  1\n"
            "0  0  0  1  0  0\n" );
    }
    //TODO: add directed and weighted graphs
}



TEST_CASE( "find Cycle" )
{
    SECTION( "1 node, no cycle" )
    {
        vector<int> cmp = { };
        vector<int> tmp;
        vector<vector<int>> t =
        {
            { 0 }
        };
        myGraph g( t );

        tmp = g.findCycle( );

        REQUIRE( tmp == cmp );
    }
    SECTION( "1 node cycle" )
    {
        vector<int> cmp = { 0 };
        vector<int> tmp;
        vector<vector<int>> t =
        {
            { 1 }
        };
        myGraph g( t );

        tmp = g.findCycle( );

        REQUIRE( tmp == cmp );
    }
    SECTION( "2 nodes no cycle" )
    {
        vector<int> cmp = { };
        vector<int> tmp;
        vector<vector<int>> t =
        {
            { 0, 1 },
            { 0, 0 },
        };
        myGraph g( t );

        tmp = g.findCycle( );

        REQUIRE( tmp == cmp );
    }
    SECTION( "2 nodes cycle" )
    {
        vector<int> cmp = { 0, 1 };
        vector<int> tmp;
        vector<vector<int>> t =
        {
            { 0, 1 },
            { 1, 0 },
        };
        myGraph g( t );

        tmp = g.findCycle( );

        REQUIRE( tmp == cmp );
    }
    SECTION( "3 node cycle" )
    {
        vector<int> cmp = { 0, 1, 2 };
        vector<int> tmp;
        vector<vector<int>> t =
        {
            { 0, 1, 0 },
            { 0, 0, 1 },
            { 1, 0, 0 }
        };
        myGraph g( t );

        tmp = g.findCycle( );

        REQUIRE( tmp == cmp );
    }
    SECTION( "4 node cycle in cycle" )
    {
        vector<int> cmp = { 0, 1, 2, 3 };
        vector<int> tmp;
        vector<vector<int>> t =
        {
            { 0, 1, 0, 0 },
            { 0, 0, 1, 0 },
            { 1, 0, 0, 1 },
            { 1, 0, 0, 0 }
        };
        myGraph g( t );

        tmp = g.findCycle( );

        REQUIRE( tmp == cmp );
    }
    SECTION( "large cycle" )
    {
        vector<int> cmp = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
        vector<int> tmp;
        vector<vector<int>> t =
        {
        {0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0},
        {1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0},
        {1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 1, 0},
        {0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0},
        {0, 0, 1, 0, 0, 0, 0, 0, 9, 0, 0, 0},
        {0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0},
        {0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 1, 0, 0, 1, 1, 1, 0, 1, 0, 1},
        {0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1},
        {0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0}
        };
        myGraph g( t );

        tmp = g.findCycle( );

        REQUIRE( tmp == cmp );
    }
    SECTION( "large no cycle" )
    {
        vector<int> cmp = { };
        vector<int> tmp;
        vector<vector<int>> t =
        {
            { 0, 1, 1, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 1, 0, 0, 0, 0 },
            { 0, 0, 0, 1, 0, 1, 0, 0, 0 },
            { 0, 1, 0, 0, 0, 0, 1, 1, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 1, 0, 0, 1, 1 },
            { 0, 0, 0, 0, 0, 1, 0, 0, 1 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0 }
        };
        myGraph g( t );

        tmp = g.findCycle( );

        REQUIRE( tmp == cmp );
    }
}



TEST_CASE( "topologicalSort" )
{
    SECTION( "1 node cycle" )
    {
        vector<vector<int>> t =
        {
            { 1 }
        };
        vector<vector<int>> c =
        {
            { 0 }
        };

        myGraph g( t ), cmp( c ), tmp;

        tmp = g.topologicalSort( );

        REQUIRE( tmp == cmp );
    }
    SECTION( "1 node, no cycle" )
    {
        vector<vector<int>> t =
        {
            { 0 }
        };
        vector<vector<int>> c =
        {
            { 0 }
        };

        myGraph g( t ), cmp( c ), tmp;

        tmp = g.topologicalSort( );

        REQUIRE( tmp == cmp );
    }
    SECTION( "2 nodes, no cycle" )
    {
        vector<vector<int>> t =
        {
            { 0, 1 },
            { 0, 0 }
        };
        vector<vector<int>> c =
        {
            { 0, 1 },
            { 0, 0 }
        };

        myGraph g( t ), cmp( c ), tmp;

        tmp = g.topologicalSort( );

        REQUIRE( tmp == cmp );
    }
    SECTION( "small solution" )
    {
        vector<vector<int>> t =
        {
            {0, 1, 0, 0, 0 },
            {0, 0, 0, 1, 0 },
            {1, 1, 0, 1, 0 },
            {0, 0, 0, 0, 0 },
            {0, 0, 1, 1, 0 }
        };
        vector<vector<int>> c =
        {
            {0, 1, 0, 0, 0 },
            {0, 0, 0, 1, 0 },
            {1, 0, 0, 0, 0 },
            {0, 0, 0, 0, 0 },
            {0, 0, 1, 0, 0 }
        };

        myGraph g( t ), cmp( c ), tmp;

        tmp = g.topologicalSort( );

        REQUIRE( tmp == cmp );
    }
    SECTION( "larger solution" )
    {
        //vector<int> cmp = { 1, 3, 4, 0, 2, 5, 6, 9, 10, 8, 7 };
        vector<vector<int>> t =
        {
            { 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0},
            { 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0},
            { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
            { 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
            { 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0},
            { 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0},
            { 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0},
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            { 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            { 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0}
        };
        vector<vector<int>> c =
        {
            { 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
            { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
            { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
            { 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
            { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            { 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
            { 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0},
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            { 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        };

        myGraph g( t ), cmp( c ), tmp;

        tmp = g.topologicalSort( );

        REQUIRE( tmp == cmp );
    }
    SECTION( "larger solution, two sources" )
    {
        //vector<int> cmp = { 1, 3, 4, 0, 2, 10, 5, 6, 8, 7, 9 };
        vector<vector<int>> t =
        {
            { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
            { 0, 0, 2, 1, 0, 0, 0, 0, 0, 0, 0},
            { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
            { 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
            { 1, 0, 0, 0, 0, 6, 1, 0, 0, 0, 0},
            { 0, 0, 0, 0, 0, 0, 8, 0, 1, 0, 0},
            { 0, 0, 0, 0, 0, 0, 0, 2, 3, 1, 0},
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            { 0, 0, 0, 0, 0, 0, 0, 9, 0, 0, 0},
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            { 0, 0, 7, 0, 0, 5, 0, 0, 0, 0, 0},
        };
        vector<vector<int>> c =
        {
            { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
            { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            { 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
            { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            { 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0},
            { 0, 0, 0, 0, 0, 0, 0, 0, 3, 1, 0},
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            { 0, 0, 0, 0, 0, 0, 0, 9, 0, 0, 0},
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            { 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0},
        };

        myGraph g( t ), cmp( c ), tmp;

        tmp = g.topologicalSort( );

        REQUIRE( tmp == cmp );
    }
    SECTION( "large cyclic" )
    {
        vector<vector<int>> t =
        {
            {0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0},
            {1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0},
            {1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 1, 0},
            {0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0},
            {0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0},
            {0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0},
            {0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
            {0, 0, 1, 0, 0, 1, 1, 1, 0, 1, 0, 1},
            {0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1},
            {0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0}
        };
        vector<vector<int>> c =
        {
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

        };

        myGraph g( t ), cmp( c ), tmp;

        tmp = g.topologicalSort( );

        REQUIRE( tmp == cmp );
    }
}



TEST_CASE( "shortest path" )
{
    SECTION( "single vertex" )
    {
        vector<string> cmp = { "0" };
        vector<string> tmp;
        vector<vector<int>> t =
        {
            { 0 }
        };

        myGraph g( t );

        tmp = g.shortestPath( 0 );

        REQUIRE( tmp == cmp );
    }
    SECTION( "two vertices" )
    {
        vector<string> cmp = { "0", "0 1" };
        vector<string> tmp;
        vector<vector<int>> t =
        {
            { 0, 1 },
            { 0, 0 }
        };

        myGraph g( t );

        tmp = g.shortestPath( 0 );

        REQUIRE( tmp == cmp );
    }
    SECTION( "large graph" )
    {
        vector<string> cmp = { "1 3 4 0", "1", "1 2", "1 3", "1 3 4", "1 2 5", "1 2 5 6", "1 2 5 6 7", "1 2 5 8", "1 2 5 6 9", "1 2 10" };
        vector<string> tmp;
        vector<vector<int>> t =
        {
            { 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0},
            { 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0},
            { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
            { 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
            { 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0},
            { 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0},
            { 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0},
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            { 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            { 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0}
        };

        myGraph g( t );

        tmp = g.shortestPath( 1 );

        REQUIRE( tmp == cmp );
    }
}


TEST_CASE( "primsMST" )
{
    SECTION( "two vertices" )
    {
        vector<vector<int>> c =
        {
            { 0, 1 },
            { 1, 0 }
        };
        vector<vector<int>> t =
        {
            { 0, 1 },
            { 1, 0 }
        };

        myGraph g( t ), cmp( c ), tmp;

        tmp = g.primsMST( 0 );

        REQUIRE( tmp == cmp );
    }
    SECTION( "five vertices weighted" )
    {
        vector<vector<int>> c =
        {
            { 0, 1, 0, 0, 0 },
            { 1, 0, 3, 2, 0 },
            { 0, 3, 0, 0, 0 },
            { 0, 2, 0, 0, 4 },
            { 0, 0, 0, 4, 0 },
        };
        vector<vector<int>> t =
        {
            { 0, 1, 0, 0, 0 },
            { 1, 0, 3, 2, 8 },
            { 0, 3, 0, 0, 0 },
            { 0, 2, 0, 0, 4 },
            { 0, 8, 0, 4, 0 }
        };

        myGraph g( t ), cmp( c ), tmp;

        tmp = g.primsMST( 0 );

        REQUIRE( tmp == cmp );
    }
    SECTION( "in class example" )
    {
        vector<vector<int>> c =
        {
            { 0, 2, 0, 1, 0, 0, 0 },
            { 2, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 2, 0, 0, 0 },
            { 1, 0, 2, 0, 0, 0, 4 },
            { 0, 0, 0, 0, 0, 0, 6 },
            { 0, 0, 0, 0, 0, 0, 1 },
            { 0, 0, 0, 4, 6, 1, 0 }
        };
        vector<vector<int>> t =
        {
            { 0, 2, 4, 1, 0, 0, 0 },
            { 2, 0, 0, 3, 10, 0, 0 },
            { 4, 0, 0, 2, 0, 5, 0 },
            { 1, 3, 2, 0, 7, 8, 4 },
            { 0, 10, 0, 7, 0, 0, 6 },
            { 0, 0, 5, 8, 0, 0, 1 },
            { 0, 0, 0, 4, 6, 1, 0 }
        };

        myGraph g( t ), cmp( c ), tmp;

        tmp = g.primsMST( 0 );

        REQUIRE( tmp == cmp );
    }
    SECTION( "tesselation" )
    {
        vector<vector<int>> c =
        {
            { 0, 8, 12, 0, 0, 0, 0, 0, 0 },
            { 8, 0, 0, 0, 9, 0, 0, 0, 0 },
            { 12, 0, 0, 14, 0, 0, 0, 0, 0 },
            { 0, 0, 14, 0, 0, 8, 0, 0, 0 },
            { 0, 9, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 8, 0, 0, 0, 11, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 11 },
            { 0, 0, 0, 0, 0, 11, 0, 0, 9 },
            { 0, 0, 0, 0, 0, 0, 11, 9, 0 }
        };
        vector<vector<int>> t =
        {
            { 0, 8, 12, 0, 0, 0, 0, 0, 0 },
            { 8, 0, 13, 25, 9, 0, 0, 0, 0 },
            { 12, 13, 0, 14, 0, 0, 21, 0, 0 },
            { 0, 25, 14, 0, 20, 8, 12, 12, 16 },
            { 0, 9, 0, 20, 0, 19, 0, 0, 0 },
            { 0, 0, 0, 8, 19, 0, 0, 11, 0 },
            { 0, 0, 21, 12, 0, 0, 0, 0, 11 },
            { 0, 0, 0, 12, 0, 11, 0, 0, 9 },
            { 0, 0, 0, 16, 0, 0, 11, 9, 0 }
        };

        myGraph g( t ), cmp( c ), tmp;

        tmp = g.primsMST( 0 );

        REQUIRE( tmp == cmp );
    }
}



TEST_CASE( "readDot" )
{
    //use command: dot -Tpng name.gv -o name.png
    ostringstream sout1, sout2;

    SECTION( "undirected unweighted" )
    {
        myGraph g( "g1.gv" ), c( "g1.txt" );
        sout1 << g;
        sout2 << c;
        //cout << g << endl << endl << c;

        REQUIRE( sout1.str( ) == sout2.str( ) );
    }
    SECTION( "undirected weighted" )
    {
        myGraph g( "g2.gv" ), c( "g2.txt" );
        sout1 << g;
        sout2 << c;
        //cout << g << endl << endl << c;

        REQUIRE( sout1.str( ) == sout2.str( ) );
    }
    SECTION( "directed unweighted" )
    {
        myGraph g( "g3.gv" ), c( "g3.txt" );
        sout1 << g;
        sout2 << c;
        //cout << g << endl << endl << c;

        REQUIRE( sout1.str( ) == sout2.str( ) );
    }
    SECTION( "directed weighted" )
    {
        myGraph g( "g4.gv" ), c( "g4.txt" );
        sout1 << g;
        sout2 << c;
        //cout << g << endl << endl << c;

        REQUIRE( sout1.str( ) == sout2.str( ) );
    }
}


TEST_CASE( "Dijkstra" )
{
    SECTION( "small graph" )
    {
        vector<vector<int>> t =
        {
            { 0, 2, 5, 0 },
            { 2, 0, 2, 0 },
            { 5, 2, 0, 6 },
            { 0, 0, 6, 0 },
        };
        myGraph g( t );
        vector<string> cmp = { "2 1 0", "2 1", "2", "2 3" }, tmp;

        tmp = g.Dijkstra( 2 );

        REQUIRE( tmp == cmp );
    }
    SECTION( "small graph" )
    {
        myGraph g( "g2.gv" );
        vector<string> cmp = { "2 1 0", "2 1", "2", "2 3", "2 1 0 4", "2 1 0 4 5", "2 3 6" }, tmp;

        tmp = g.Dijkstra( 2 );

        REQUIRE( tmp == cmp );
    }
}


TEST_CASE( "Ford Fulkerson" )
{
    SECTION( "in class flow example" )
    {
        vector<vector<int>> t =
        {
            { 0, 4, 2, 0, 0, 0 },
            { 0, 0, 1, 2, 4, 0 },
            { 0, 0, 0, 0, 2, 0 },
            { 0, 0, 0, 0, 0, 3 },
            { 0, 0, 0, 0, 0, 3 },
            { 0, 0, 0, 0, 0, 0 }
        };
        myGraph g( t ), residual;
        int tmp = g.FordFulkerson( 0, 5, residual );

        REQUIRE( tmp == 5 );
    }
    SECTION( "another example" )
    {
        vector<vector<int>> t =
        {
            { 0, 1, 3, 0, 0, 0 },
            { 0, 0, 0, 99, 99, 0 },
            { 0, 0, 0, 0, 99, 0 },
            { 0, 0, 0, 0, 0, 2 },
            { 0, 0, 0, 0, 0, 2 },
            { 0, 0, 0, 0, 0, 0 }
        };
        myGraph g( t ), residual;
        int tmp = g.FordFulkerson( 0, 5, residual );

        REQUIRE( tmp == 3 );
    }
    SECTION( "g4" )
    {
        myGraph g( "g4.gv" ), residual;
        int tmp = g.FordFulkerson( 0, 3, residual );

        REQUIRE( tmp == 12 );
    }
}



TEST_CASE( "BFS" )
{
    SECTION( "g3" )
    {
        myGraph g( "g3.gv" );
        vector<int> cmp = { 0, 1, 5 }, tmp;

        tmp = g.BFS( 0, 5 );

        REQUIRE( tmp == cmp );
    }
    SECTION( "g4" )
    {
        myGraph g( "g4.gv" );
        vector<int> cmp = { 0, 1, 2, 4 }, tmp;

        tmp = g.BFS( 0, 4 );

        REQUIRE( tmp == cmp );
    }
    SECTION( "in class flow example" )
    {
        vector<vector<int>> t =
        {
            { 0, 4, 2, 0, 0, 0 },
            { 0, 0, 1, 2, 4, 0 },
            { 0, 0, 0, 0, 2, 0 },
            { 0, 0, 0, 0, 0, 3 },
            { 0, 0, 0, 0, 0, 3 },
            { 0, 0, 0, 0, 0, 0 }
        };
        myGraph g( t );
        vector<int> cmp = { 0, 1, 4, 5 }, tmp;

        tmp = g.BFS( 0, 5 );

        REQUIRE( tmp == cmp );
    }
    SECTION( "in class flow example 2" )
    {
        vector<vector<int>> t =
        {
            { 0, 4, 2, 0, 0, 0 },
            { 0, 0, 5, 2, 4, 0 },
            { 0, 0, 0, 0, 2, 0 },
            { 0, 0, 0, 0, 0, 2 },
            { 0, 0, 0, 0, 0, 3 },
            { 0, 0, 0, 0, 0, 0 }
        };
        myGraph g( t );
        vector<int> cmp = { 0, 1, 2, 4, 5 }, tmp;

        tmp = g.BFS( 0, 5 );

        REQUIRE( tmp == cmp );
    }

}



TEST_CASE( "kruskal's" )
{
    SECTION( "two vertices" )
    {
        vector<vector<int>> c =
        {
            { 0, 1 },
            { 1, 0 }
        };
        vector<vector<int>> t =
        {
            { 0, 1 },
            { 1, 0 }
        };

        myGraph g( t ), cmp( c ), tmp;

        tmp = g.kruskalsMST( );

        REQUIRE( tmp == cmp );
    }
    SECTION( "five vertices weighted" )
    {
        vector<vector<int>> c =
        {
            { 0, 1, 0, 0, 0 },
            { 1, 0, 3, 2, 0 },
            { 0, 3, 0, 0, 0 },
            { 0, 2, 0, 0, 4 },
            { 0, 0, 0, 4, 0 },
        };
        vector<vector<int>> t =
        {
            { 0, 1, 0, 0, 0 },
            { 1, 0, 3, 2, 8 },
            { 0, 3, 0, 0, 0 },
            { 0, 2, 0, 0, 4 },
            { 0, 8, 0, 4, 0 }
        };

        myGraph g( t ), cmp( c ), tmp;

        tmp = g.kruskalsMST( );

        REQUIRE( tmp == cmp );
    }
    SECTION( "in class example" )
    {
        vector<vector<int>> c =
        {
            { 0, 2, 0, 1, 0, 0, 0 },
            { 2, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 2, 0, 0, 0 },
            { 1, 0, 2, 0, 0, 0, 4 },
            { 0, 0, 0, 0, 0, 0, 6 },
            { 0, 0, 0, 0, 0, 0, 1 },
            { 0, 0, 0, 4, 6, 1, 0 }
        };
        vector<vector<int>> t =
        {
            { 0, 2, 4, 1, 0, 0, 0 },
            { 2, 0, 0, 3, 10, 0, 0 },
            { 4, 0, 0, 2, 0, 5, 0 },
            { 1, 3, 2, 0, 7, 8, 4 },
            { 0, 10, 0, 7, 0, 0, 6 },
            { 0, 0, 5, 8, 0, 0, 1 },
            { 0, 0, 0, 4, 6, 1, 0 }
        };

        myGraph g( t ), cmp( c ), tmp;

        tmp = g.kruskalsMST( );

        REQUIRE( tmp == cmp );
    }
    SECTION( "tesselation" )
    {
        vector<vector<int>> c =
        {
            { 0, 8, 12, 0, 0, 0, 0, 0, 0 },
            { 8, 0, 0, 0, 9, 0, 0, 0, 0 },
            { 12, 0, 0, 14, 0, 0, 0, 0, 0 },
            { 0, 0, 14, 0, 0, 8, 0, 0, 0 },
            { 0, 9, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 8, 0, 0, 0, 11, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 11 },
            { 0, 0, 0, 0, 0, 11, 0, 0, 9 },
            { 0, 0, 0, 0, 0, 0, 11, 9, 0 }
        };
        vector<vector<int>> t =
        {
            { 0, 8, 12, 0, 0, 0, 0, 0, 0 },
            { 8, 0, 13, 25, 9, 0, 0, 0, 0 },
            { 12, 13, 0, 14, 0, 0, 21, 0, 0 },
            { 0, 25, 14, 0, 20, 8, 12, 12, 16 },
            { 0, 9, 0, 20, 0, 19, 0, 0, 0 },
            { 0, 0, 0, 8, 19, 0, 0, 11, 0 },
            { 0, 0, 21, 12, 0, 0, 0, 0, 11 },
            { 0, 0, 0, 12, 0, 11, 0, 0, 9 },
            { 0, 0, 0, 16, 0, 0, 11, 9, 0 }
        };

        myGraph g( t ), cmp( c ), tmp;

        tmp = g.kruskalsMST( );

        REQUIRE( tmp == cmp );
    }
}



TEST_CASE( "BFSCount" )
{
    SECTION( "g1.gv" )
    {
        vector<vector<int>> g =
        {
            { 0, 1, 0, 0, 1, 1 },
            { 1, 0, 1, 1, 0, 1 },
            { 0, 1, 0, 1, 0, 0 },
            { 0, 1, 1, 0, 1, 1 },
            { 1, 0, 0, 1, 0, 1 },
            { 1, 1, 0, 1, 1, 0 }
        };
        int result;

        result = BFSCount( g, 2 );
        
        REQUIRE( result == 5 );
    }
    SECTION( "g1.gv modified" )
    {
        vector<vector<int>> g =
        {
            { 0, 0, 0, 0, 0, 0 },
            { 0, 0, 1, 1, 0, 1 },
            { 0, 1, 0, 1, 0, 0 },
            { 0, 1, 1, 0, 1, 1 },
            { 0, 0, 0, 1, 0, 1 },
            { 0, 1, 0, 1, 1, 0 }
        };
        int result;

        result = BFSCount( g, 2 );

        REQUIRE( result == 4 );
    }
}



TEST_CASE( "eulerCircuit" )
{
    SECTION( "g2.gv" )
    {
        vector<vector<int>> tmp =
        {
            { 0, 1, 0, 0, 1, 0, 0 },
            { 0, 0, 1, 0, 0, 0, 3 },
            { 0, 0, 0, 1, 0, 0, 0 },
            { 0, 7, 0, 0, 0, 0, 1 },
            { 0, 0, 0, 4, 0, 2, 0 },
            { 6, 0, 0, 0, 0, 0, 0 },
            { 1, 0, 0, 0, 5, 0, 0 }
        };
        myGraph g( "g2.gv" ), result, cmp( tmp );

        result = g.eulerCircuit( );

        REQUIRE( result == cmp );
    }
    SECTION( "g2.gv modified" )
    {
        vector<vector<int>> tmp =
        {
            { 0, 1, 0, 0, 0, 6, 0 },
            { 0, 0, 1, 0, 0, 0, 0 },
            { 0, 0, 0, 1, 0, 0, 0 },
            { 0, 7, 0, 0, 4, 0, 0 },
            { 1, 0, 0, 0, 0, 0, 5 },
            { 0, 0, 0, 0, 2, 0, 0 },
            { 1, 0, 0, 1, 0, 0, 0 }
        };
        myGraph g( "g2.gv" ), result, cmp( tmp );
        g.removeEdge( 1, 6 );
        g.removeEdge( 6, 1 );

        result = g.eulerCircuit( );

        REQUIRE( result == cmp );
    }

}