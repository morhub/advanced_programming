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
	bool foundAList = false;

	//from m_vParts to list(list(part))
	list<list<Part>*> templist;

	for (int i = 0; i < getNumOfElements(); i++)
	{
		foundAList = false;

		if (templist.empty())
		{
			list<Part> li;
			li.push_back(m_vParts->at(i));
			templist.push_back(li);
			foundAList = true;
		}
		for (std::list<list<Part>>::iterator it = templist.begin(); it != templist.end(); ++it)
		{
			//it is a list<Part>
			if (m_vParts->at(i).isPermotation(*it.pop_front()))
			{
				it->emplace_back(m_vParts->at(i));
				foundAList = true;
				break; //move to the next part
			}
		}
		//didnt find a list for this part- create new one 
		if (!foundAList)
		{
			list<Part> l;
			l.push_back(m_vParts->at(i));
			templist.emplace_back(l);
		}
	}


	//each part - bool Part::isPermotation(Part b)
	//if true - pushback(current list)
	//if false- new list(part)



	//init the map member : 
	for (int i = -1; i < 2; i++)
	{
		for (int j = -1; j < 2; j++)
		{
			for (std::list<list<Part>>::iterator it = templist.begin(); it != templist.end(); ++it)
			{
				if(it->pop_front()->ma)
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