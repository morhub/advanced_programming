#include "Part.h"

Part::Part(int id, int left, int top, int right, int bottom)
{
	m_iId = id;
	m_iLeft = left; 
	m_iTop = top;
	m_iRight = right;
	m_iBottom = bottom;
	m_iRow = m_iCol = -1; ///Check this !!! 
}

Part::Part()
{
	m_iId = -1;
	m_iLeft = 0; 
	m_iTop = 0;
	m_iRight = 0;
	m_iBottom = 0;
	m_iRow = m_iCol = 0; ///Check this !!! 
}

bool Part::isConnectedTo(Part& other, position pos)
{
	other.m_iRow = -2;
	if (pos)
		return true;
	return true;

}

Part Part::operator=(const Part& p) {
	m_iId = p.m_iId;
	m_iLeft = p.m_iLeft;
   	m_iTop = p.m_iTop;
    m_iRight = p.m_iRight;
    m_iBottom = p.m_iBottom;
	m_iRow = p.m_iRow;
	m_iCol = p.m_iCol;

	return *this;
}
