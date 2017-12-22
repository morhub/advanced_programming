#ifndef PART_H
#define PART_H

#include <iostream>
#include <vector>
#include <list>

using namespace std;


#define MODULO(a,b) (a%b+b)%b

enum direction {
	LEFT=0,
	TOP,
	RIGHT,
	BOTTOM
};

class Part
{
	int m_iId, m_iLeft, m_iTop, m_iRight, m_iBottom;
	int rotateAngle;
	bool m_bCorner;

public:
	Part(int id=0, int left=0, int top=0, int right=0, int bottom=0);

	int getId()					{ return m_iId; }
	int getLeft()				{ return m_iLeft; }
	int getTop()				{ return m_iTop; }
	int getRight()				{ return m_iRight; }
	int getBottom()				{ return m_iBottom; }
	int getRotation()			{ return rotateAngle; }
	bool isCorner()				{ return m_bCorner; }
	void setCorner(bool b)		{ m_bCorner = b; }
	void setRotation(int angle) { rotateAngle = MODULO(angle, 4); }

	int getEdgeAfterRotate(int angle, enum direction dir);

	bool isSpecial();

	

	/*
	 *	is this part is a permotation of part b? 
	 */
	list<int> getPermutations(Part b);
	list<int> getPermutations(int left, int top, int right, int bottom);

	/*
	 * does this part have a permotation witch suites the 
	 * input top, left 
	 * @return -1 if there is no permotation that suites 
	 *  if there is, return 0-3 according to the rotation angle
	 * (1 for 90, 2 for 180, 3 for 360)
	 */
	//list<int> matchLeftTop(int left, int top);
	
	
	void addRotation(int addition) { rotateAngle = MODULO(rotateAngle + addition, 4); }

};

#endif
