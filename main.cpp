// advanced_programming.cpp : Defines the entry point for the console application.
//

#include <fstream>
#include <string>
#include <cstring>
#include <iostream>
#include "Puzzle.h"
#include "Table.h"


using std::perror;
using std::cout;
using std::endl;

int main(int argc, char *argv[])
{
	int rc = 0;

	if (argc != 3) {
		printf("Usage: %s <input_file> <output_file>\n", argv[0]);
		return -EINVAL;
	}

	std::ofstream output(argv[2]);

	Puzzle* puz = new Puzzle();

	puz->setOutputStream(&output);

	rc = puz->init(argv[1]);
	if (rc) {
		perror("Failed to init Puzzle\n");
		return rc;

	}

	rc = puz->preProcess();
	if (rc) {
		perror("Failed in pre-Processing Stage\n");
		return rc;

	}

	Table table = puz->Solve();
	if (table.getTable())
		table.print(output);
	else
	{
		rc = -1;
		cout << "no solution" << endl;
	}
	return rc;
	
}

