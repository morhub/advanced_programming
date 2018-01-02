// advanced_programming.cpp : Defines the entry point for the console application.
//

#include "Puzzle.h"
#include "rotatePuzzle.h"
#include "nonRotatePuzzle.h"
#include "Table.h"
#include "Parser.h"

#include <fstream>
#include <string>
#include <cstring>
#include <iostream>

using std::cout;
using std::endl;

int main(int argc, char *argv[])
{
	int rc = 0;
	Puzzle* puz;

	if (argc < 3)
	{
		cout << "Usage: " << argv[0] << " <input_file> <output_file> ";
		cout << "[-rotate] [-threads %d] " << endl;
		return -1;
	}
	
	Parser parser(argc, argv);
	std::ofstream output(parser.getOutputFile());

	printf("num of threads %d\n", parser.getThreads());
	printf("rotate %d\n", parser.getRotate());
	printf("input file %s\n", parser.getInputFile().c_str());
	printf("output file %s\n", parser.getOutputFile().c_str());

	if (parser.getRotate())
		puz = new rotatePuzzle();
	else
		puz = new nonRotatePuzzle();

	puz->setOutputStream(&output);

	rc = puz->init(parser.getInputFile());
	if (rc) {
		return rc;
	}

	rc = puz->preProcess();
	if (rc) {
		return rc;
	}

	Table table = puz->Solve(parser.getThreads());
	if (table.getTable())
		table.print(output, puz);
	else
		rc = -1;
	
	return rc;
}

