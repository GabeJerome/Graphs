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
    if(argc != 2)
    {
        cout << "Incorrect command line arguments." << endl;
        cout << "Usage: Graphs.exe [graphFileName]" << endl;
        return 1;
    }



    return 0;
}
