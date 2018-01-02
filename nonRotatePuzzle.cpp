#include <fstream>
#include <string>
#include <cstring>
#include <iostream>
#include <assert.h> 
#include "nonRotatePuzzle.h"
#include <algorithm>

using std::getline;
using std::string;
using std::endl;
using std::pair;


void nonRotatePuzzle::initiatePartMap(partMapNonRotate_t& pmap)
{
	for (int i = -1; i < 2; i++)
	{
		for (int j = -1; j < 2; j++)
		{
			for (int k = -1; k < 2; k++)
			{
				for (int s = -1; s < 2; s++)
				{
					pmap[make_pair(i, j)][make_pair(k, s)] = new list<Part*>();
				}
			}
		}
	}
}


partMapNonRotate_t nonRotatePuzzle::setPartsMap(vector<Part>& parts)
{
	int l, t, r, b;
	partMapNonRotate_t retMap;
	initiatePartMap(retMap);

	for (size_t i = 0; i < m_iNumOfElements; i++)
	{
		Part& p = parts.at(i);
		l = p.getLeft();
		t = p.getTop();
		r = p.getRight();
		b = p.getBottom();

		retMap[make_pair(l, t)][make_pair(r, b)]->push_back(&p);
	}

	return retMap;
}


bool nonRotatePuzzle::isValidStraightEdges(int sizei, int sizej)
{
	int leftStraight = 0;
	int topStraight = 0;
	for (size_t i = 0; i < m_iNumOfElements; i++)
	{
		int left = (m_vParts)[i].getLeft();
		int top =  (m_vParts)[i].getTop();

		if (left == 0)
			leftStraight++;
		if (top == 0)
			topStraight++;

	}
	if (leftStraight < sizei || topStraight < sizej)
		return false;
	return true;
}


int nonRotatePuzzle::preProcess()
{
	int ret = 0;
	int topStraight = 0;
	int bottomStraight = 0;
	int leftStraight = 0;
	int rightStraight = 0;

	for (size_t i = 0; i < m_iNumOfElements; i++)
	{
		if ((m_vParts)[i].getLeft() == 0)
			leftStraight++;
		if ((m_vParts)[i].getTop() == 0)
			topStraight++;
		if ((m_vParts)[i].getRight() == 0)
			rightStraight++;
		if ((m_vParts)[i].getBottom() == 0)
			bottomStraight++;
	}

	if (!((topStraight == bottomStraight && topStraight != 0) && (leftStraight == rightStraight && leftStraight != 0)))
	{
		*fout << "Cannot solve puzzle: wrong number of straight edges" << endl;
		ret = -1;
	}

	ret |= Puzzle::preProcess();

	return ret;
}

bool nonRotatePuzzle::cornerCheck(bool &tr, bool &tl, bool &br, bool &bl)
{
	//the easy case - only one element
	if (m_iNumOfElements == 1) {
		Part& p = (m_vParts)[0];
		tr = p.getTop() == 0	&& p.getRight() == 0;
		tl = p.getTop() == 0	&& p.getLeft() == 0;
		br = p.getBottom() == 0 && p.getRight() == 0;
		bl = p.getBottom() == 0 && p.getLeft() == 0;
		return (tr && tl && br && bl);
	}

	//the regular case - different 4 corner parts
	for (size_t i = 0; i < m_iNumOfElements; i++)
	{
		Part& pi = (m_vParts)[i];
		if (pi.getTop() == 0 && pi.getRight() == 0)
		{
			pi.setCorner(true);
			for (size_t j = 0; j < m_iNumOfElements; j++)
			{
				Part& pj = (m_vParts)[j];
				if (!pj.isCorner() && pj.getTop() == 0 && pj.getLeft() == 0)
				{
					pj.setCorner(true);
					for (size_t k = 0; k < m_iNumOfElements; k++)
					{
						Part& pk = (m_vParts)[k];
						if (!pk.isCorner() && pk.getBottom() == 0 && pk.getRight() == 0)
						{
							pk.setCorner(true);
							for (size_t m = 0; m < m_iNumOfElements; m++)
							{
								Part& pm = (m_vParts)[m];
								if (!pm.isCorner() && pm.getBottom() == 0 && pm.getLeft() == 0)
								{
									pm.setCorner(true);
									return true;
								}
							}
							pk.setCorner(false);
						}
					}
					pj.setCorner(false);
				}
			}
			pi.setCorner(false);
		}
	}

	//the row case - 2 corner parts
	for (size_t i = 0; i < m_iNumOfElements; i++)
	{
		Part& pi = (m_vParts)[i];

		//if a single part isn't straight on top/bottom, it will fail
		if (pi.getTop() != 0 || pi.getBottom() != 0)
			break;

		if (pi.getRight() == 0)
		{
			pi.setCorner(true);
			for (size_t j = 0; j < m_iNumOfElements; j++)
			{
				Part& pj = (m_vParts)[j];
				if (!pj.isCorner() && pj.getLeft() == 0)
				{
					pj.setCorner(true);
					return true;
				}
			}
			pi.setCorner(false);
		}
	}

	//the col case - 2 corner parts
	for (size_t i = 0; i < m_iNumOfElements; i++)
	{
		Part& pi = (m_vParts)[i];

		//if a single part isn't straight on right/left, it will fail
		if (pi.getLeft() != 0 || pi.getRight() != 0)
			break;

		if (pi.getTop() == 0)
		{
			pi.setCorner(true);
			for (size_t j = 0; j < m_iNumOfElements; j++)
			{
				Part& pj = (m_vParts)[j];
				if (!pj.isCorner() && pj.getBottom() == 0)
				{
					pj.setCorner(true);
					return true;
				}
			}
			pi.setCorner(false);
		}
	}

	// if we got so far, it means there is no available solution (not enough corners)!
	for (size_t i = 0; i < m_iNumOfElements; i++)
	{
		Part& p = (m_vParts)[i];
		if (p.getTop() == 0 && p.getRight() == 0) {
			tr = true;
			continue;
		}
		if (p.getTop() == 0 && p.getLeft() == 0) {
			tl = true;
			continue;
		}
		if (p.getBottom() == 0 && p.getRight() == 0) {
			br = true;
			continue;
		}
		if (p.getBottom() == 0 && p.getLeft() == 0) {
			bl = true;
			continue;
		}
	}
	return false;
}

list<pair<list<Part*>*, list<int>>> nonRotatePuzzle::getMatches(int left, int top, int right, int bottom, partMapNonRotate_t& partMap)
{
	list<pair<list<Part*>*, list<int>>> retlist;
	const auto& MatchMap = partMap[make_pair(left, top)];

	/* transform "map<pair<int, int>, list<Part>*>" into "list<pair<list<Part>*, int>>".
	 * the "0" stands for zero rotation, since no rotation are allowed in this scenario */
	std::transform(MatchMap.begin(), MatchMap.end(),
				   std::back_inserter(retlist),
				   [](const std::map<pair<int, int>, list<Part*>*>::value_type pair)
					 {
		return make_pair(pair.second, list<int>{0});
					 }
				  );

	if (retlist.empty())
		return retlist;

	retlist.erase(std::remove_if(retlist.begin(), retlist.end(),
		[right, bottom](const pair<list<Part*>*, list<int>> value) {
			list<Part*>* partList = value.first;
			if (partList->empty())
				return true;

			auto& p = partList->front();
			//if right/bottom doesn't exist, just set them to p.right/p.bottom
			int _right =  (right == -2)  ? p->getRight()  : right;
			int _bottom = (bottom == -2) ? p->getBottom() : bottom;

			return (_right != p->getRight() || _bottom != p->getBottom());
		}),
		retlist.end()
	);

	return retlist;
}

void nonRotatePuzzle::preComputeCommonCase(partMapNonRotate_t& partMap, common_match_t& cm)
{
	//pre-compute the common case (no right,bottom edges)
	for (int i = -1; i < 2; i++)
		for (int j = -1; j < 2; j++)
			cm[make_pair(i, j)] = getMatches(i, j, -2, -2, partMap);
}


void nonRotatePuzzle::preComputeFullCase(partMapNonRotate_t& partMap, full_match_t& fm)
{
	//pre-compute the full case (no right,bottom edges)
		for (int i = -2; i < 2; i++)
			for (int j = -2; j < 2; j++)
				for (int k = -2; k < 2; k++)
					for (int l = -2; l < 2; l++)
						fm[make_tuple(i, j, k, l)] = getMatches(i, j, k, l, partMap);
}


void nonRotatePuzzle::createDataBase(vector<Part>& parts, common_match_t& cm, full_match_t& fm)
{
	auto partMap = setPartsMap(parts);
	preComputeCommonCase(partMap, cm);
	preComputeFullCase(partMap, fm);
}
