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
	for (int i = -1; i < 2; i++)
	{
		for (int j = -1; j < 2; j++)
		{
			m_mPartMap[make_pair(i, j)] = *(new list<pair<list<shared_ptr<Part>>*, list<int>>>());	
		}
	}
}

rotatePuzzle::~rotatePuzzle()
{
	for (int i = -1; i < 2; i++)
	{
		for (int j = -1; j < 2; j++)
		{
			delete &m_mPartMap[make_pair(i, j)];
		}
	}
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
	bool foundAList = false;

	//from m_vParts to list(list(part))
	list<list<shared_ptr<Part>>*> templist;

	//first part - new list 
	templist.emplace_back(new list<shared_ptr<Part>>{ m_vParts->at(0) });

	for (int i = 1; i < getNumOfElements(); i++)
	{
		foundAList = false;

		for (auto& partList : templist) 
		{
			//this is a list<Part>
			list<int> rotate = m_vParts->at(i)->getPermutations(*partList->front());
			if (!rotate.empty()) //there is a permotation
			{
				//in that case it's a real part, meaning right&bottom != -2.
				// and so its not a special case=> there is only 1 rotation angle
				m_vParts->at(i)->setRotation(rotate.front());
				partList->emplace_back(m_vParts->at(i));
				foundAList = true;
				break; //move to the next part
			}
		}
		//didnt find a list for this part- create new one 
		if (!foundAList)
			templist.emplace_back(new list<shared_ptr<Part>>{ m_vParts->at(i) });
	}

	//init the map member : 
	for (int left = -1; left < 2; left++) 
	{
		for (int top = -1; top < 2; top++) 
		{
			for (auto& partList : templist)
			{
				list<int> rotates = partList->front()->getPermutations(left, top, -2, -2);
				if (rotates.empty()) //this list doesnt match to these left, top
					continue;
				else
				{	//map that list&rotation to these left, top
					auto pr = make_pair(partList, rotates);
					m_mPartMap[make_pair(left, top)].emplace_back(pr);
				}
			}
		}
	}
}


list<pair<list<shared_ptr<Part>>*, list<int>>> rotatePuzzle::getMatches(int left, int top, int right, int bottom)
{
	list<pair<list<shared_ptr<Part>>*, list<int>>> retlist = m_mPartMap[make_pair(left, top)];
	if (retlist.empty())
		return retlist;

	retlist.erase(std::remove_if(retlist.begin(), retlist.end(),
		[left, top, right, bottom](pair<list<shared_ptr<Part>>*, list<int>> value) {
		list<shared_ptr<Part>>* partList = value.first;
		if (partList->empty())
			return true;

		auto& p = partList->front();
		return ((p->getPermutations(left, top, right, bottom)).empty());
	}),
		retlist.end()
		);
	return retlist;
}