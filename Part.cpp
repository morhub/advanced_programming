#include "Part.h"

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


list<int> Part::getPermutations(Part& b)
{
	list<int> angles;
	int i;

	vector<int> p(4);
	p.at(0) = m_iLeft;
	p.at(1) = m_iTop;
	p.at(2) = m_iRight;
	p.at(3) = m_iBottom;

	for (i = 0; i < 4; i++)
	{
		if ((b.getLeft()   == -2 || p.at(0) == b.getLeft())   &&
			(b.getTop()    == -2 || p.at(1) == b.getTop())    &&
			(b.getRight()  == -2 || p.at(2) == b.getRight())  &&
			(b.getBottom() == -2 || p.at(3) == b.getBottom()))
		{
			angles.push_back(i);
			if (this->isSpecial() &&
				(b.getRight() == -2 && b.getBottom() == -2) &&
				(b.getLeft() == b.getTop()))
			{
				rotate(p.begin(),
					p.end() - 1, // this will be the new first element
					p.end());
				continue;
			}
			else
				break;
		}
		else
		{
			rotate(p.begin(),
				p.end() - 1, // this will be the new first element
				p.end());
		}		
	}

	return angles;
}


list<int> Part::getPermutations(int left, int top, int right, int bottom)
{
	return getPermutations(Part(0, left, top, right, bottom));
}


//list<int> Part::matchLeftTop(int left, int top)
//{
//	int angle=0;
//	vector<int> p(4);
//	p.at(0) = this->getLeft();
//	p.at(1) = this->getTop();
//	p.at(2) = this->getRight();
//	p.at(3) = this->getBottom();
//
//	for (int i = 0; i < 4; i++)
//	{
//		if (p.at(0) == left &&
//			p.at(1) == top)
//			return angle;
//		else
//		{	
//			rotate(p.begin(),
//			p.end() - 1, // this will be the new first element
//			p.end());
//
//			angle++;
//		}
//	}
//	return -1;
//}


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


bool Part::isSpecial()
{
	int l = m_iLeft;
	int t = m_iTop;
	int r = m_iRight;
	int b = m_iBottom;

	return ((l == t && t == r && r != b)   ||
		   (t == r && r == b && b != l)    ||
		   (r == b && b == l && l != t)    ||
		   (b == l && l == t && t != r));
}
