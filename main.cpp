// advanced_programming.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include <fstream>
#include <string>
#include <cstring>
#include <iostream>
#include "Puzzle.h"

using std::perror;
using std::cout;
using std::endl;

int main(int argc, char *argv[])
{
	int rc = 0;
	bool debug = false;
	std::streambuf *coutbuf;

	if (argc != 3 && argc != 4) {
		printf("Usage: %s <input_file> <output_file>\n", argv[0]);
		return -EINVAL;
	}
	if(argc == 4) {
		if(!std::strncmp(argv[3], "-d", 2))
			debug = true;
		else {
			printf("Usage: %s <input_file> <output_file>\n", argv[0]);
			return -EINVAL;
		}
	}

	std::ofstream output(argv[2]);
	if (debug) {
		coutbuf = std::cout.rdbuf(); //save old buf
		cout.rdbuf(output.rdbuf()); //redirect std::cout to output	
	}	

	Puzzle* puz = new Puzzle(&output);

	puz->setOutputStream(&output);

	rc = puz->init(argv[1]);
	if (rc) {
		perror("Failed to init Puzzle\n");
		goto ERR_EXIT;
	}

	rc = puz->preProcess();
	if (rc) {
		perror("Failed in pre-Processing Stage\n");
		goto ERR_EXIT;
	}

	rc = puz->Solve();
	if (rc) {
		perror("Failed Solving the puzzle\n");
		goto ERR_EXIT;
	}

	rc = puz->print(); 
	if (rc) {
		perror("Failed printing the puzzle to output\n");
		goto ERR_EXIT;
	}

ERR_EXIT:
	if (debug)
		cout.rdbuf(coutbuf); //reset to standard output again
    return 0;
}

