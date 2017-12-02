#include "Part.h"
#include <iostream>
#include <vector>
using namespace std;


Part::Part(int id, int left, int top, int right, int bottom)
{
	m_iId = id;
	m_iLeft = left; 
	m_iTop = top;
	m_iRight = right;
	m_iBottom = bottom;
	m_bCorner = false;
	rotateAngle = 0;
}

bool Part::isPermotation(Part b)
{
	vector<int> p;
	p.at(0) = this->getLeft();
	p.at(1) = this->getTop();
	p.at(2) = this->getRight();
	p.at(3) = this->getBottom();

	for (int i = 0; i < 4; i++)
	{
		if (p.at(0) == b.getLeft() &&
			p.at(1) == b.getTop() &&
			p.at(2) == b.getRight() &&
			p.at(3) == b.getBottom())
			return true;
		else
			rotate(p.begin(),
					p.end(), // this will be the new first element
					 p.end());
	}
	return false;
}


int Part::matchTopLeft(int top, int left)
{
	vector<int> p;
	p.at(0) = this->getLeft();
	p.at(1) = this->getTop();
	p.at(2) = this->getRight();
	p.at(3) = this->getBottom();

	for (int i = 0; i < 4; i++)
	{
		if (p.at(0) == left &&
			p.at(1) == top)
			return true;
		else
			rotate(p.begin(),
					p.end(), // this will be the new first element
					 p.end());
	}
	return false;
}

