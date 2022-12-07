#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

#include "Graphs.h"

const bool RUNCATCH = true;


int main ( int argc, char **argv)
{
    Catch::Session session;
    int result;

    if( RUNCATCH )
    {
        result = session.run();
        if(result != 0)
        {
            std::cout << "Test cases didn't pass." << std::endl;
            return result;
        }
    }

    //check command line arguments
    if ( !checkArgs( argc ) )
        return 1;

    callFuncs( argv, argc );

    return 0;
}
