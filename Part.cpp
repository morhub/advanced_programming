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

bool Part::isConnectedTo(Part& other, direction dir)
{
	int sum, currentEdge, otherEdge = -2;

	switch (dir)
	{
	case(TOP):
		currentEdge = this->getTop();
		otherEdge   = other.getBottom();
		break;
	case(BOTTOM):
		currentEdge = this->getBottom();
		otherEdge   = other.getTop();
		break;
	case(LEFT):
		currentEdge = this->getLeft();
		otherEdge   = other.getRight();
		break;
	case(RIGHT):
		currentEdge = this->getRight();
		otherEdge   = other.getLeft();
		break;
	}

	sum = currentEdge + otherEdge;
	if(sum == 0)
		return true;
	return false;
}
