#include <fstream>
#include <string>
#include <iostream>
#include "Puzzle.h"


Puzzle::Puzzle(FILE* out)
{
	m_fOutput = out;
	m_iNumOfCols = m_iNumOfRows = -1;
}


int Puzzle::init(std::string path)
{
	m_iNumOfElements = -1;
	m_vParts = NULL;
	path = "";
	return 0;
}


int Puzzle::Solve()
{
	return true;
}


int Puzzle::preProcess()
{
//	int sum;
//	for (std::vector<Part>::size_type i = 0; i != m_vParts->size(); i++)
//	{
//		sum += m_vParts[i]->getLeft();
//
//	}
	return 0;
}


int Puzzle::print()
{
	return 0;
}
