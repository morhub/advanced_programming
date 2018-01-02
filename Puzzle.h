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
#include <memory>
#include <list>
using namespace std;

class Table;

typedef map<pair<int, int>, list<pair<list<Part*>*, list<int>>>>			common_match_t;
typedef map<tuple<int, int, int, int>, list<pair<list<Part*>*, list<int>>>> full_match_t;


class Puzzle
{
protected:
	vector<Part> m_vParts;
	map<pair<int, int>, list<pair<list<Part*>*, list<int>>>> m_mCommonMatches;
	map<tuple<int, int, int, int>, list<pair<list<Part*>*, list<int>>>> m_mFullMatches;
	size_t m_iNumOfElements;
	ofstream* fout;

public:
	int getNumOfElements()  { return m_iNumOfElements; }
	virtual int getMaxPossibleRows() { return m_iNumOfElements; }
	void setOutputStream(std::ofstream* f) { fout = f; }
	Part& getPartAt(int index) { return m_vParts.at(index); }

	/*
	 * Creates an unsolved Puzzle out of input file path
	 * @param input: input file to read from
	 * @return 0 for success
	 */
	int init(std::string input);

	/*
	 * Solves a puzzle, basically sets each part's
	 * (row, col) to its relevant position on table
	 *
	 * @param threads
	 * @return solution organized in table on success,
	 *  empty table on failure.
	 */
	Table Solve(int threads);

	/*Checking 3 possible problems that end the game.. 
	* 1- Have we got 4 corners?
	* 2- Wrong number of straight edges? (left = right , bottom = top)		
	* 3- Is the sum of edges equal to 0 ? 
	*
	*returns 0 on success 
	*/
	virtual int preProcess();

	/*
	 * Pure virtual function
	 * Checks whether the puzzle has enough straight edges 
	 * to support solution with i rows and j cols
	 */
	virtual bool isValidStraightEdges(int i, int j) = 0;
	virtual bool cornerCheck(bool &tr, bool &tl, bool &br, bool &bl) = 0;

	/*
	 * Pure virtual
	 * Creates a more suitable data structure from the part list,
	 * to make better use of puzzle different solution modes (rotate/non-rotate mode)
	 */
	virtual void initPartsMap() = 0;
	virtual list<pair<list<Part*>*, list<int>>> getMatches(int left, int top, int right, int bottom) = 0;

private:
	/*
	 * internal recursive call from Solve()
	 */
	Table Puzzle::solveThread(int rows);
	int solveRec(size_t i, size_t j, Table& tab, common_match_t& cm,full_match_t& fm, vector<Part>& vParts);

	/* Assuming that all "middle" parts are equaly distributed with 1,0,-1 edges,
	 * a difference between number of left and top straight edges will probably come
	 * from the frame size differences.
	 * Thus, it will be best to order all possible row sizes based on their probability
	 * to give a physible solution (with respect to topStraight,leftStraight diff).
	 */
	vector<int> getMostProbableRowSizes();

	/* update the maps pointers such that each thread will eventually point to a copy of
	* m_vparts, and also update this copy, so threads won't collide while solving the puzzle
	*
	*/
	void Puzzle::updatePointersPerThread(common_match_t& cm, full_match_t& fm, vector<Part>& vPartsCopy);

	void copyAndUpdateCommonMatch(vector<Part>& vPartsCopy, common_match_t& cm);
	void copyAndUpdateFullMatch(vector<Part>& vPartsCopy, full_match_t& fm);

protected:
	void preComputeCommonCase();
	void preComputeFullCase();
};


#endif
