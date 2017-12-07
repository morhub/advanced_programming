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

int Part::isPermotation(Part b)
{
	int angle = 0; 

	vector<int> p(4);
	p.at(0) = this->getLeft();
	p.at(1) = this->getTop();
	p.at(2) = this->getRight();
	p.at(3) = this->getBottom();

	for (int i = 0; i < 4; i++)
	{
		if ((b.getLeft() == -2   || p.at(0) == b.getLeft())    &&
			(b.getTop() == -2    || p.at(1) == b.getTop())     &&
			(b.getRight() == -2  || p.at(2) == b.getRight())   &&
			(b.getBottom() == -2 || p.at(3) == b.getBottom()))
			return angle;
		else
		{
			rotate(p.begin(),
				p.end() - 1, // this will be the new first element
				p.end());

			angle++;
		}		
	}
	return -1;
}


int Part::isPermotation(int left, int top, int right, int bottom)
{
	return isPermotation(*(new Part(0, left, top, right, bottom)));
}


int Part::matchLeftTop(int left, int top)
{
	int angle=0;
	vector<int> p(4);
	p.at(0) = this->getLeft();
	p.at(1) = this->getTop();
	p.at(2) = this->getRight();
	p.at(3) = this->getBottom();

	for (int i = 0; i < 4; i++)
	{
		if (p.at(0) == left &&
			p.at(1) == top)
			return angle;
		else
		{	
			rotate(p.begin(),
			p.end() - 1, // this will be the new first element
			p.end());

			angle++;
		}
	}
	return -1;
}


int Part::getRightAfterRotate(int angle)
{
	vector<int> p(4);
	p.at(0) = this->getLeft();
	p.at(1) = this->getTop();
	p.at(2) = this->getRight();
	p.at(3) = this->getBottom();

	for (int i = 0; i < angle; i++)
	{
		rotate(p.begin(),
			p.end() - 1, // this will be the new first element
			p.end());
	}

	return p.at(2); //right after rotation
}


int Part::getBottomAfterRotate(int angle)
{
	vector<int> p(4);
	p.at(0) = this->getLeft();
	p.at(1) = this->getTop();
	p.at(2) = this->getRight();
	p.at(3) = this->getBottom();

	for (int i = 0; i < angle; i++)
	{
		rotate(p.begin(),
			p.end() - 1, // this will be the new first element
			p.end());
	}

	return p.at(3); //right after rotation
}


//void isSpecialPart()
//{
//	int l = this->getLeft();
//	int t = p->getTop();
//	int r = p->getRight();
//	int b = p->getBottom();
//
//	if ((l == t && t == r) || (t == r && r == b) || (r == b && b == l) || (b == l && l == t))
//		p->setIsSpecial(true);
//}
