#include "Part.h"

Part::Part(int id, int left, int top, int right, int bottom)
{
	m_iId = id;
	m_iLeft = left; 
	m_iTop = top;
	m_iRight = right;
	m_iBottom = bottom;
	m_iRow = m_iColl = -1; ///Check this !!! 
}


bool Part::isConnectedTo(Part other, direction dir)
{

	return true;

}