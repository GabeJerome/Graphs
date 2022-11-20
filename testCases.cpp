#include "catch.hpp"


#include "Graphs.h"
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;


TEST_CASE("file constructor")
{
    ostringstream sout;

    SECTION("undirected graph")
    {
        myGraph g("g1.txt");
        sout << g;
        REQUIRE(sout.str() == "0  1  0  0  1  1\n"
                              "1  0  1  1  0  1\n"
                              "0  1  0  1  0  0\n"
                              "0  1  1  0  1  1\n"
                              "1  0  0  1  0  1\n"
                              "1  1  0  1  1  0\n");
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
        vector<int> cmp = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
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
        vector<int> cmp = { };
        vector<int> tmp;
        vector<vector<int>> t =
        {
            { 1 }
        };
        myGraph g( t );

        tmp = g.topologicalSort( );

        REQUIRE( tmp == cmp );
    }
    SECTION( "1 node, no cycle" )
    {
        vector<int> cmp = { 0 };
        vector<int> tmp;
        vector<vector<int>> t =
        {
            { 0 }
        };
        myGraph g( t );

        tmp = g.topologicalSort( );

        REQUIRE( tmp == cmp );
    }
    SECTION( "2 nodes, no cycle" )
    {
        vector<int> cmp = { 0, 1 };
        vector<int> tmp;
        vector<vector<int>> t =
        {
            { 0, 1 },
            { 0, 0 }
        };
        myGraph g( t );

        tmp = g.topologicalSort( );

        REQUIRE( tmp == cmp );
    }
    SECTION( "small solution" )
    {
        vector<int> cmp = { 4, 2, 0, 1, 3 };
        vector<int> tmp;
        vector<vector<int>> t =
        {
            {0,1,0,0,0 },
            {0,0,0,1,0 },
            {1,1,0,1,0 },
            {0,0,0,0,0 },
            {0,0,1,1,0 }
        };

        myGraph g( t );

        tmp = g.topologicalSort( );

        REQUIRE( tmp == cmp );
    }
    SECTION( "larger solution" )
    {
        vector<int> cmp = { 1, 3, 4, 0, 2, 5, 6, 9, 10, 8, 7 };
        vector<int> tmp;
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
            { 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
        };

        myGraph g( t );

        tmp = g.topologicalSort( );

        REQUIRE( tmp == cmp );
    }
    SECTION( "larger solution, two sources" )
    {
        vector<int> cmp = { 1, 3, 4, 0, 2, 10, 5, 6, 8, 7, 9 };
        vector<int> tmp;
        vector<vector<int>> t =
        {
            { 0, 0, 8, 0, 0, 1, 0, 0, 0, 0, 0},
            { 0, 0, 2, 1, 0, 0, 0, 0, 0, 0, 0},
            { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
            { 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
            { 1, 0, 0, 0, 0, 6, 1, 0, 0, 0, 0},
            { 0, 0, 0, 0, 0, 0, 8, 0, 1, 0, 0},
            { 0, 0, 0, 0, 0, 0, 0, 2, 3, 1, 0},
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            { 0, 0, 0, 0, 0, 0, 0, 9, 0, 0, 0},
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            { 0, 0, 0, 0, 0, 5, 0, 0, 1, 0, 0},
        };

        myGraph g( t );

        tmp = g.topologicalSort( );

        REQUIRE( tmp == cmp );
    }
    SECTION( "large cyclic" )
    {
        vector<int> cmp = { };
        vector<int> tmp;
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
        myGraph g( t );

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
    SECTION( "" )
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
        vector<string> cmp = { "0", "0 1" };
        vector<string> tmp;
        vector<vector<int>> t =
        {
            { 0, 1 },
            { 1, 0 }
        };

        myGraph g( t );

        tmp = g.primsMST( 0 );

        REQUIRE( tmp == cmp );
    }
    SECTION( "five vertices weighted" )
    {
        vector<string> cmp = { "0", "0 1", "0 1 2", "0 1 3", "0 1 3 4" };
        vector<string> tmp;
        vector<vector<int>> t =
        {
            { 0, 1, 0, 0, 0 },
            { 1, 0, 3, 2, 8 },
            { 0, 3, 0, 0, 0 },
            { 0, 2, 0, 0, 4 },
            { 0, 8, 0, 4, 0 },
        };

        myGraph g( t );

        tmp = g.primsMST( 0 );

        REQUIRE( tmp == cmp );
    }
    SECTION( "in class example" )
    {
        vector<string> cmp = { "0", "0 1", "0 3 2", "0 3", "0 3 6 4", "0 3 6 5", "0 3 6" };
        vector<string> tmp;
        vector<vector<int>> t =
        {
            { 0, 2, 4, 1, 0, 0, 0 },
            { 2, 0, 0, 3, 10, 0, 0 },
            { 4, 0, 0, 2, 0, 5, 0 },
            { 1, 3, 2, 0, 7, 8, 4 },
            { 0, 10, 0, 7, 0, 0, 6 },
            { 0, 0, 5, 8, 0, 0, 1 },
            { 0, 0, 0, 4, 6, 1, 0 },
        };

        myGraph g( t );

        tmp = g.primsMST( 0 );

        REQUIRE( tmp == cmp );
    }

}