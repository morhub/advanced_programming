#include "Puzzle.h"



Puzzle::Puzzle(std::string inputFile, FILE* outputFile)
{
	m_iNumOfColls = m_iNumOfRows = -1;
	//read from file the size 
	//m_iNumOfElements = size from file
}


void Puzzle::init(std::string path)
{

}


bool Puzzle::Solve()
{
	return false;
}


void Puzzle::preProcess()
{
	int sum;
	for (std::vector<Part>::size_type i = 0; i != m_vParts->size(); i++)
	{
		sum += m_vParts[i]->getLeft();

	}
}


void Puzzle::printPuzzle(std::string outputPath)
{

}