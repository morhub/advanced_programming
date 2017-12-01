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


nonRotatePuzzle::nonRotatePuzzle()
{
	for (int i = -1; i < 2; i++)
	{
		for (int j = -1; j < 2; j++)
		{
			for (int k = -1; k < 2; k++)
			{
				for (int s = -1; s < 2; s++)
				{
					m_mPartMap[make_pair(i, j)][make_pair(k, s)] = new list<Part>();
				}
			}
		}
	}
}


nonRotatePuzzle::~nonRotatePuzzle()
{
	for (int i = -1; i < 2; i++)
	{
		for (int j = -1; j < 2; j++)
		{
			for (int k = -1; k < 2; k++)
			{
				for (int s = -1; s < 2; s++)
				{
					delete m_mPartMap[make_pair(i, j)][make_pair(k, s)];
				}
			}
		}
	}
}


void nonRotatePuzzle::initPartsMap()
{
	int l, t, r, b;
	for (size_t i = 0; i < m_iNumOfElements; i++)
	{
		Part& p = m_vParts->at(i);
		l = p.getLeft();
		t = p.getTop();
		r = p.getRight();
		b = p.getBottom();

		m_mPartMap[make_pair(l, t)][make_pair(r, b)]->push_back(p);
	}
}


bool nonRotatePuzzle::isValidStraightEdges(int sizei, int sizej)
{
	int leftStraight = 0;
	int topStraight = 0;
	for (size_t i = 0; i < m_iNumOfElements; i++)
	{
		int left = (*m_vParts)[i].getLeft();
		int top = (*m_vParts)[i].getTop();

		if (left == 0)
			leftStraight++;
		if (top == 0)
			topStraight++;
	}
	if (leftStraight < sizei || topStraight < sizej)
		return false;
	return true;
}