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
#include <list>
#include <cmath>

using namespace std;

typedef map<pair<int, int>, list<pair<list<Part*>*, list<int>>>> partMapRotate_t;

class rotatePuzzle : public Puzzle
{
public:
	
	virtual void createDataBase(vector<Part>& parts, common_match_t& cm, full_match_t& fm);

private:
	/*
	* A data structure which contains:
	* 1- a map of <left, top> keys, the value is:
	* 2- a list of <list*(Part), rotate_Angle>
	*	each of the list(part)s is a list of equivalent parts
	*  (the same part after rotation of size "rotate_Angle").
	*	each of the lists can be pointed to by several pairs of the map.
	*/
	partMapRotate_t setPartsMap(vector<Part>& parts);

	void ComputeCommonDataBase(partMapRotate_t& partMap, common_match_t& cm);
	void ComputeFullDataBase(partMapRotate_t& partMap, full_match_t& fm);
	void initiatePartMap(partMapRotate_t& pmap);
	
	virtual int getMaxPossibleRows() { return (int)sqrt(m_iNumOfElements); }
	virtual bool isValidStraightEdges(int sizei, int sizej);
	virtual bool cornerCheck(bool &tr, bool &tl, bool &br, bool &bl);
	virtual list<pair<list<Part*>*, list<int>>> getMatches(int left, int top, int right, int bottom, partMapRotate_t& partMap);
	virtual void createDataBase(vector<Part>& parts, common_match_t& cm, full_match_t& fm);


};
#endif
