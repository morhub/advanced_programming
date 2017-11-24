// advanced_programming.cpp : Defines the entry point for the console application.
//

#include <fstream>
#include <string>
#include <cstring>
#include <iostream>
#include "Puzzle.h"
#include "Table.h"


using std::cout;
using std::endl;

int main(int argc, char *argv[])
{
	int rc = 0;

	if (argc != 3) {
		cout << "Usage: " << argv[0] << " <input_file> <output_file>" << endl;
		return -1;
	}

	std::ofstream output(argv[2]);

	Puzzle* puz = new Puzzle();

	puz->setOutputStream(&output);

	rc = puz->init(argv[1]);
	if (rc) {
		return rc;
	}

	rc = puz->preProcess();
	if (rc) {
		return rc;
	}

	puz->initPartsMap();

	Table table = puz->Solve();
	if (table.getTable())
		table.print(output);
	else
		rc = -1;
	

	return rc;
}

