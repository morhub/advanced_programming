#ifndef PUZZLE_H
#define PUZZLE_H

#include "Part.h"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <vector>

class Puzzle
{
	std::vector<Part> *m_vParts;
	size_t m_iNumOfElements, m_iNumOfRows, m_iNumOfCols;
	std::ofstream* fout;

public:
	Puzzle();
	~Puzzle();
	Puzzle& operator=(const Puzzle&) = delete;
	Puzzle(const Puzzle&) = delete;

	int getSize()		{ return m_iNumOfElements; }
	int getNumOfRows()	{ return m_iNumOfRows; }
	int getNumOfCols() { return m_iNumOfCols; }
	int getNumOfElements() { return m_iNumOfElements; }

	void setNumOfRows(int rows)				{ m_iNumOfRows  = rows; }
	void setNumOfCols(int cols)				{ m_iNumOfCols = cols; }
	void setOutputStream(std::ofstream* f) { fout = f; }
	std::vector<Part>* getParts() { return m_vParts; }

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
	int** Solve();

	/*Checking 3 possible problems that end the game.. 
	* 1- Have we got 4 corners?
	* 2- Wrong number of straight edges? (left = right , bottom = top)		
	* 3- Is the sum of edges equal to 0 ? 
	*
	*returns 0 on success 
	*/
	int preProcess();

	int print();

private:
	int** initTable();

};
#endif
