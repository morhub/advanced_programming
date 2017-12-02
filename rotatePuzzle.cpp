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
			m_mPartMap[make_pair(i, j)] = *(new list<pair<list<Part>*, int>>());	
		}
	}
}

rotatePuzzle::~rotatePuzzle()
{
	/*for (int i = -1; i < 2; i++)
	{
		for (int j = -1; j < 2; j++)
		{
			delete m_mPartMap[make_pair(i, j)];
		}
	}*/
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
	list<list<Part>*> templist;

	//first part - new list 
	templist.emplace_back(new list<Part>{ m_vParts->at(0) });

	for (int i = 1; i < getNumOfElements(); i++)
	{
		foundAList = false;

		for (auto& partList : templist) 
		{
			//this is a list<Part>
			int rotate = m_vParts->at(i).isPermotation(partList->front());
			if (rotate != -1) //there is a permotation
			{
				m_vParts->at(i).setRotation(rotate);
				partList->emplace_back(m_vParts->at(i));
				foundAList = true;
				break; //move to the next part
			}
		}
		//didnt find a list for this part- create new one 
		if (!foundAList)
			templist.emplace_back(new list<Part>{ m_vParts->at(i) });
	}

	//init the map member : 
	for (int left = -1; left < 2; left++) 
	{
		for (int top = -1; top < 2; top++) 
		{
			for (auto& partList : templist)
			{
				Part temp = partList->front();  //// part&?
				int rotate = partList->front().matchLeftTop(left, top);
				if (rotate == -1) //this list doesnt match to these left, top
					continue;
				else
				{	//map that list&rotation to these left, top
					auto pr = make_pair(partList, rotate);
					m_mPartMap[make_pair(left, top)].emplace_back(pr);
				}
			}
		}
	}

	//for(for(left, top)) - for each i,j : 
	//is the current list has a permotaion with suited left, top ? 
	//with int Part::matchTopLeft(int top, int left)
	//return -1 if there is no match, or 0-3 if there is a match and
	//the shift-level 
	//if -1 : move to the next list(parts)
	//else : push-back this list(part) to the list-value of
	//this top-left-key
}


list<pair<list<Part>*, int>> rotatePuzzle::getMatches(int left, int top, int right, int bottom)
{
	list<pair<list<Part>*, int>> retlist = m_mPartMap[make_pair(left, top)];
	if (retlist.empty())
		return retlist;

	retlist.erase(std::remove_if(retlist.begin(), retlist.end(),
		[left, top, right, bottom](const pair<list<Part>*, int> value) {
			list<Part>* partList = value.first;
			if (partList->empty())
				return true;

			auto& p = partList->begin();
			return ((p->isPermotation(left, top, right, bottom))==-1);
		}),
		retlist.end()
	);

	return retlist;
}