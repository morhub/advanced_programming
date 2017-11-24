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
#include<list>
using namespace std;


class Puzzle
{
	vector<Part> *m_vParts;
	size_t m_iNumOfElements;
	ofstream* fout;
	map<pair<int, int>, map<pair<int, int>, list<Part>*>> m_mPartMap;

public:
	Puzzle();
	~Puzzle();
	Puzzle& operator=(const Puzzle&) = delete;
	Puzzle(const Puzzle&) = delete;

	int getNumOfElements()  { return m_iNumOfElements; }

	void setOutputStream(std::ofstream* f) { fout = f; }
	std::vector<Part>* getParts() { return m_vParts; }

	bool isValidStraightEdges(int sizei, int sizej);


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
	int preProcess();


	/*
	* A data structure which contains:
	* 1- a map of <left, top> keys, the value is:
	* 2- a map of <right, bottom> keys, the value is:
	* 3- list of parts that has the edges of the keys indexes
	* 
	*/
	void initPartsMap();


private:
	int solveRec(size_t i, size_t j, Table& tab);
};
#endif
