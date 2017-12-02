#ifndef PUZZLE_H
#define PUZZLE_H

#include "Part.h"
#include "Table.h"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <list>

using namespace std;

class Table;

class Puzzle
{
protected:
	vector<Part> *m_vParts;
	size_t m_iNumOfElements;
	ofstream* fout;

public:
	Puzzle();
	~Puzzle();
	Puzzle& operator=(const Puzzle&) = delete;
	Puzzle(const Puzzle&) = delete;

	int getNumOfElements()  { return m_iNumOfElements; }
	void setOutputStream(std::ofstream* f) { fout = f; }
	std::vector<Part>* getParts() { return m_vParts; }

	/*
	 * Creates an unsolved Puzzle out of input file path
	 * @param input: input file to read from
	 * @return 0 for success
	 */
	int init(std::string input);

	/*
	 * Solves a puzzle, basically sets each part's
	 * (row, col) to its relevant position
	 *
	 * @param input: input path to read from
	 */
	Table Solve();

	/*Checking 3 possible problems that end the game.. 
	* 1- Have we got 4 corners?
	* 2- Wrong number of straight edges? (left = right , bottom = top)		
	* 3- Is the sum of edges equal to 0 ? 
	*
	*returns 0 on success 
	*/
	virtual int preProcess();

	virtual bool isValidStraightEdges(int sizei, int sizej) = 0;
	virtual bool cornerCheck(bool &tr, bool &tl, bool &br, bool &bl) = 0;
	virtual void initPartsMap() = 0;
	virtual list<pair<list<Part>*, int>> getMatches(int left, int top, int right, int bottom) = 0;

private:
	int solveRec(size_t i, size_t j, Table& tab);
};


#endif
