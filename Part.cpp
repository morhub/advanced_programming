#include "Part.h"
//
Part::Part(int id, int left, int top, int right, int bottom)
{
	m_iId = id;
	m_iLeft = left; 
	m_iTop = top;
	m_iRight = right;
	m_iBottom = bottom;
	m_iRow = m_iCol = -1; ///Check this !!! 
}

Part::Part(const Part &p)
{
	//id = new int;
	//*id = *p.m_iId;


}

bool Part::isConnectedTo(Part& other, position pos)
{
	other.m_iRow = -2;
	if (pos)
		return true;
	return true;

}
