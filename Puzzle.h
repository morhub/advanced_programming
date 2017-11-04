#ifndef PUZZLE_H
#define PUZZLE_H

#include "Part.h"
#include <fstream>
#include <string>
#include <iostream>
#include <vector>

class Puzzle
{
	std::vector<Part>* m_vParts;
	int m_iNumOfElements, m_iNumOfRows, m_iNumOfColls;
	//file* m_fOutputFile;

public:
	Puzzle(std::string inputFile, FILE* outputFile);//file* outputFile;
	int getSize()		{ return m_iNumOfElements; }
	int getNumOfRows()	{ return m_iNumOfRows; }
	int getNumOfColls() { return m_iNumOfColls; }

	//get array
	//get file ? 

	void setNumOfRows(int rows)		{ m_iNumOfRows  = rows; }
	void setNumOfColls(int colls)	{ m_iNumOfColls = colls; }
	void init(std::string path);
	bool Solve();
	void preProcess();
	void printPuzzle(std::string outputPath);

private:
	//array finalPuzzle()
};




#endif