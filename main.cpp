// advanced_programming.cpp : Defines the entry point for the console application.
//

#include <fstream>
#include <string>
#include <cstring>
#include <iostream>
#include "Puzzle.h"
#include "Table.h"
#include <windows.h>

using std::cout;
using std::endl;

int main(int argc, char *argv[])
{
	int rc = 0;

	if (argc != 3) {
		cout << "Usage: " << argv[0] << " <input_file> <output_file>" << endl;
		return -1;
	}

	LARGE_INTEGER frequency;        // ticks per second
	LARGE_INTEGER t1, t2;           // ticks
	double elapsedTime;

	// get ticks per second
	QueryPerformanceFrequency(&frequency);

	// start timer
	QueryPerformanceCounter(&t1);

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
	

	// stop timer
	QueryPerformanceCounter(&t2);

	// compute and print the elapsed time in millisec
	elapsedTime = (t2.QuadPart - t1.QuadPart) * 1000.0 / frequency.QuadPart;
	cout << "time: " << elapsedTime << endl;

	return rc;
}

