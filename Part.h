#ifndef PART_H
#define PART_H
//
enum position {
	LEFT,
	TOP,
	RIGHT,
	BOTTOM
};

class Part
{
	int m_iId, m_iLeft, m_iTop, m_iRight, m_iBottom;
	int m_iRow, m_iCol;

public:
	Part(int id=0, int left=0, int top=0, int right=0, int bottom=0);

	int getId()					{ return m_iId; }
	int getLeft()				{ return m_iLeft; }
	int getTop()				{ return m_iTop; }
	int getRight()				{ return m_iRight; }
	int getBottom()				{ return m_iBottom; }
	int getRow()				{ return m_iRow; }
	int getCol()				{ return m_iCol; }
	void setRow(int row)		{ m_iRow  = row; }
	void setCol(int col)		{ m_iCol = col; }
	bool isConnectedTo(Part& other, position pos);
//private:
	//rotate

};








#endif
