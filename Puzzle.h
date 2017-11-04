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
	int m_iNumOfElements, m_iNumOfRows, m_iNumOfCols;
	FILE* m_fOutput;

public:
	Puzzle(FILE* outputFile);
	~Puzzle();

	int getSize()		{ return m_iNumOfElements; }
	int getNumOfRows()	{ return m_iNumOfRows; }
	int getNumOfColls() { return m_iNumOfCols; }

	void setNumOfRows(int rows)		{ m_iNumOfRows  = rows; }
	void setNumOfCols(int cols)		{ m_iNumOfCols = cols; }

	/*
	 * Creates an unsolved Puzzle out of input file path
	 * @param input: input file to read from
	 */
	int init(std::string input);

	/*
	 * Solves a puzzle, basically sets each part's
	 * (row, col) to its relevant position
	 *
	 * @param input: input path to read from
	 */
	int Solve();

	int preProcess();

	int print();
};
#endif
