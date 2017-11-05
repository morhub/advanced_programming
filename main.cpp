// advanced_programming.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include <fstream>
#include <string>
#include <iostream>
#include "Puzzle.h"

using std::perror;
using std::cout;
using std::endl;

int main(int argc, char *argv[])
{
	if (argc != 3) {
		printf("Usage: %s <input_file> <output_file>\n", argv[0]);
		return -EINVAL;
	}
	int rc = 0;

	std::ofstream output(argv[2]);

	Puzzle* puz = new Puzzle(&output);

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
    return 0;
}

