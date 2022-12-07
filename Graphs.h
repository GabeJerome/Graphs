#pragma once

using namespace std;

#include "myGraph.h"
#include <iostream>


bool checkArgs( int argc );

void callFuncs( char **argv, int argc );

void printCycle( vector<int> &cycle );

void printPaths( vector<string> &paths );