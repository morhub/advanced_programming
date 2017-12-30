// advanced_programming.cpp : Defines the entry point for the console application.
//

#include <fstream>
#include <string>
#include <cstring>
#include <iostream>
#include "Puzzle.h"
#include "rotatePuzzle.h"
#include "nonRotatePuzzle.h"
#include "Table.h"


using std::cout;
using std::endl;

int main(int argc, char *argv[])
{
	int rc = 0;
	char *input_file, *output_file;
	bool rotate;
	Puzzle* puz;
	string Rotate = "-rotate";
	int threads = 0;

	switch (argc) {
	case 3:
		input_file = argv[1];
		output_file = argv[2];
		rotate = false;
		break;
	case 4:
		if (!Rotate.compare(argv[1])) {
			input_file = argv[2];
			output_file = argv[3];
			rotate = true;
			break;
		} else if (!Rotate.compare(argv[2])) {
			input_file = argv[1];
			output_file = argv[3];
			rotate = true;
			break;
		} else if (!Rotate.compare(argv[3])) {
			input_file = argv[1];
			output_file = argv[2];
			rotate = true;
			break;
		} else
			/* pass through */ 
	default:
		cout << "Usage: " << argv[0] << " <input_file> <output_file>" << endl;
		return -1;
	}

	std::ofstream output(output_file);

	if (rotate)
		puz = new rotatePuzzle();
	else
		puz = new nonRotatePuzzle();

	puz->setOutputStream(&output);

	rc = puz->init(input_file);
	if (rc) {
		return rc;
	}

	rc = puz->preProcess();
	if (rc) {
		return rc;
	}

	puz->initPartsMap();

	Table table = puz->Solve(threads);
	if (table.getTable())
		table.print(output, puz);
	else
		rc = -1;
	
	return rc;
}

