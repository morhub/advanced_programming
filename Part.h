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
	int m_iRow, m_iColl; 

public:
	Part(int id, int left, int top, int right, int bottom);
	int getId()					{ return m_iId; }
	int getLeft()				{ return m_iLeft; }
	int getTop()				{ return m_iTop; }
	int getRight()				{ return m_iRight; }
	int getBottom()				{ return m_iBottom; }
	int getRow()				{ return m_iRow; }
	int getColl()				{ return m_iColl; }
	void setRow(int row)		{ m_iRow  = row; }
	void setColl(int coll)		{ m_iColl = coll; }
	bool isConnectedTo(Part other, direction dir);


//private:
	//rotate

};








#endif