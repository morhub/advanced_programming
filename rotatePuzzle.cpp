#include <fstream>
#include <string>
#include <cstring>
#include <iostream>
#include <assert.h> 
#include "rotatePuzzle.h"
#include <algorithm>

using std::getline;
using std::string;
using std::endl;
using std::pair;


rotatePuzzle::rotatePuzzle()
{
	
}

rotatePuzzle::~rotatePuzzle()
{
	
}

bool rotatePuzzle::isValidStraightEdges(int sizei, int sizej)
{
	return true;
}

bool rotatePuzzle::cornerCheck(bool &tr, bool &tl, bool &br, bool &bl)
{
	return true;
}

void rotatePuzzle::initPartsMap()
{

}

list<pair<list<Part>*, int>> rotatePuzzle::getMatches(int left, int top)
{
	return m_mPartMap[make_pair(left, top)];
}