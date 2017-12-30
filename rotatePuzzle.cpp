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
			m_mPartMap[make_pair(i, j)] = *(new list<pair<list<Part*>*, list<int>>>());	
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
	int straight = 0;
	for (int i = 0; i < getNumOfElements(); i++) {
		int left =   (m_vParts)[i].getLeft();
		int top =	 (m_vParts)[i].getTop();
		int bottom = (m_vParts)[i].getBottom();
		int right =  (m_vParts)[i].getRight();


		straight += ((left == 0) + (top == 0) +
					(right == 0) + (bottom == 0));
	}
	return (straight > sizei + sizej);
}


bool rotatePuzzle::cornerCheck(bool &tr, bool &tl, bool &br, bool &bl)
{
	tr = tl = br = bl = true;
	return true;
}


void rotatePuzzle::initPartsMap()
{
	bool foundAList = false;

	//from m_vParts to list(list(part))
	list<list<Part*>*> templist;

	//first part - new list 
	templist.emplace_back(new list<Part*>{&(m_vParts.at(0))});

	for (int i = 1; i < getNumOfElements(); i++)
	{
		foundAList = false;

		for (auto& partList : templist) 
		{
			//this is a list<Part>
			list<int> rotate = m_vParts.at(i).getPermutations(*(partList->front()));
			if (!rotate.empty()) //there is a permotation
			{
				//in that case it's a real part, meaning right&bottom != -2.
				// and so its not a special case=> there is only 1 rotation angle
				m_vParts.at(i).setRotation(rotate.front());
				partList->emplace_back(&(m_vParts.at(i)));
				foundAList = true;
				break; //move to the next part
			}
		}
		//didnt find a list for this part- create new one 
		if (!foundAList)
			templist.emplace_back(new list<Part*>{&(m_vParts.at(i))});
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


list<pair<list<Part*>*, list<int>>> rotatePuzzle::getMatches(int left, int top, int right, int bottom)
{
	list<pair<list<Part*>*, list<int>>> retlist = m_mPartMap[make_pair(left, top)];
	if (retlist.empty())
		return retlist;

	for(auto& element : retlist)
	{
		
		if (element.first->empty())
			continue;
		element.second = element.first->front()->getPermutations(left, top, right, bottom);
	}
	

	retlist.erase(std::remove_if(retlist.begin(), retlist.end(),
		[left, top, right, bottom](pair<list<Part*>*, list<int>> value) {
		list<Part*>* partList = value.first;
		if (partList->empty())
			return true;

		return (value.second.empty());
	}),
		retlist.end()
		);


	return retlist;
}
