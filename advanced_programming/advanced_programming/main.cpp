// advanced_programming.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <fstream>
#include <string>
#include <iostream>
#include "Part.h"
#include "Puzzle.h"


int main()
{
	//fopen - output
	FILE* output;// = fopen from cmd... 
	Puzzle* puz = new Puzzle("sfsf", output); //input, output
	puz->preProcess();
	puz->Solve();
	puz->printPuzzle("sdfsf");//output file-name from cmd... 
	
	//fclose - output
    return 0;
}

