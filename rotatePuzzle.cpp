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

list<pair<list<Part>*, int>> rotatePuzzle::getMatches(int left, int top, int right, int bottom)
{
	list<pair<list<Part>*, int>> retlist = m_mPartMap[make_pair(left, top)];
	if (retlist.empty())
		return retlist;

	retlist.erase(std::remove_if(retlist.begin(), retlist.end(),
		[right, bottom](const pair<list<Part>*, int> value) {
			list<Part>* partList = value.first;
			if (partList->empty())
				return true;

			auto& p = partList->begin();
			int pright = p->getRight();
			int pbottom = p->getBottom();
			int pleft = p->getLeft();
			int ptop = p->getTop();

		//if right/bottom doesn't exist, just set them to p.right/p.bottom
		int _right = (right == -2) ? pright : right;
		int _bottom = (bottom == -2) ? pbottom : bottom;

		return ((_right == pright && _bottom == pbottom) ||
				(_right == pbottom && _bottom == pleft)	||
				(_right == pleft && _bottom == ptop) ||
				(_right == ptop	&& _bottom == pright));
		}),
		retlist.end()
	);

	return retlist;
}