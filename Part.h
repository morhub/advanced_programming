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

public:
	Part(int id=0, int left=0, int top=0, int right=0, int bottom=0);

	int getId()					{ return m_iId; }
	int getLeft()				{ return m_iLeft; }
	int getTop()				{ return m_iTop; }
	int getRight()				{ return m_iRight; }
	int getBottom()				{ return m_iBottom; }
};

#endif
