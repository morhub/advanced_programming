#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <string>
#include <sstream>


using namespace std;
#define ILLEGAL_THREADS -3


class Parser
{
	string inputFile;
	string outputFile;
	bool rotate;
	int threads;


public:
	Parser(int argc, char *argv[]);
	
	string getInputFile()   { return inputFile; }
	string getOutputFile()  { return outputFile; }
	bool   getRotate()		{ return rotate; }
	int    getThreads()		{ return threads; }






};




#endif
