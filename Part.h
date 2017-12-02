#ifndef PART_H
#define PART_H

enum direction {
	LEFT,
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
	void setRotation(int angle) { rotateAngle = angle; }

	/*
	 *	is this part is a permotation of part b? 
	 */
	bool isPermotation(Part b);

	/*
	 * does this part have a permotation witch suites the 
	 * input top, left 
	 * @return -1 if there is no permotation that suites 
	 *  if there is, return 0-3 according to the rotation angle
	 * (1 for 90, 2 for 180, 3 for 360)
	 */
	int Part::matchTopLeft(int top, int left);

};

#endif
