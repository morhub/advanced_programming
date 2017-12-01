#ifndef ROTATEPUZZLE_H
#define ROTATEPUZZLE_H

#include "Part.h"
#include "Table.h"
#include "Puzzle.h"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include<list>
using namespace std;


class rotatePuzzle : public Puzzle
{
	map<pair<int, int>, list<pair<list<Part>*, int>>> m_mPartMap;

public:
	rotatePuzzle();
	~rotatePuzzle();
	rotatePuzzle& operator=(const rotatePuzzle&) = delete;
	rotatePuzzle(const rotatePuzzle&) = delete;


	/*
	* A data structure which contains:
	* 1- a map of <left, top> keys, the value is:
	* 2- a list of <list*(Part), rotate_Angle>
	*	each of the list(part)s is a list of equivalent parts 
	*  (the same part after rotation of size "rotate_Angle").
	*	each of the lists can be pointed to by several pairs of the map.
	*/
	virtual void initPartsMap();

	virtual bool isValidStraightEdges(int sizei, int sizej);
	virtual bool cornerCheck(bool &tr, bool &tl, bool &br, bool &bl);
	virtual list<pair<list<Part>*, int>> getMatches(int left, int top);

private:
//	int solveRec(size_t i, size_t j, Table& tab);
};
#endif
