#include <iostream>
#include <unistd.h>
#include <string>

#include "Simulator.h"

using namespace::std;

int main(int argc, char * argv[])
{
     int c;
     bool verbose = false;
     string sValue = "";
     
     while ((c = getopt (argc, argv, "vs:")) != -1)
     if (c == 'v')
     verbose = true;
     else
     if (c == 's')
     sValue = optarg;
     
     string inputFileName = argv[optind];
     string randFileName = argv[optind + 1];
     
    /*for test in xcode
    string inputFileName1 = "/Users/Duffy/Documents/2015Fall/OS/lab2/lab2_assign/input5";
    string randFileName1 = "/Users/Duffy/Documents/2015Fall/OS/lab2/lab2_assign/rfile";
    bool verbose1 = true;
    string sValue1 = "P5";
     */
    Simulator simulator;
    simulator.Run(inputFileName, randFileName, verbose, sValue);
    simulator.Print();
    
    return 0;
}
