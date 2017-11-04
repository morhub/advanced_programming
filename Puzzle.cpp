#include <fstream>
#include <string>
#include <iostream>
#include "Puzzle.h"
//

Puzzle::Puzzle(FILE* out)
{
	m_fOutput = out;
	m_iNumOfCols = m_iNumOfRows = -1;
}

Puzzle::~Puzzle()
{
	for (int i = 0; i < m_iNumOfElements; i++)
	{
		delete &m_vParts[i];  //check this 
	}
	delete m_vParts;
	//delete the file ? 
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
	int sum = 0;
	int topStraight = 0;
	int bottomStraight = 0;
	int leftStraight = 0;
	int rightStraight = 0;
	bool tr, tl, br, bl = false;

	for (std::vector<Part>::size_type i = 0; i != m_vParts->size(); i++)
	{
		int left = (*m_vParts).at(i).getLeft();
		int top = (*m_vParts).at(i).getTop();
		int right = (*m_vParts).at(i).getRight();
		int bottom = (*m_vParts).at(i).getBottom();

		if (left == 0)
			leftStraight++;
		if (top == 0)
			topStraight++;
		if (right == 0)
			rightStraight++;
		if (bottom == 0)
			bottomStraight++;

		if (top == 0 && right == 0)
			tr = true;
		if (top == 0 && left == 0)
			tl = true;
		if (bottom == 0 && right == 0)
			br = true;
		if (bottom == 0 && left == 0)
			bl = true;

		sum += (*m_vParts).at(i).getLeft();
		sum += (*m_vParts).at(i).getTop();
		sum += (*m_vParts).at(i).getRight();
		sum += (*m_vParts).at(i).getBottom();
	}

	if (topStraight != bottomStraight || leftStraight != rightStraight)
		perror("Cannot solve puzzle: wrong number of straight edges\n");

	if(tl == false)
		perror("Cannot solve puzzle: missing corner element: TL\n");
	if (tr == false)
		perror("Cannot solve puzzle: missing corner element: TR\n");
	if (bl == false)
		perror("Cannot solve puzzle: missing corner element: BL\n");
	if (br == false)
		perror("Cannot solve puzzle: missing corner element: BR\n");

	if (sum != 0)
		perror("Cannot solve puzzle : sum of edges is not zero");

	return 0;
}

int** Puzzle::finalPuzzle()
{
	int rows = m_iNumOfRows;
	int cols = m_iNumOfCols;
	int** res = new int*[rows];
	
	for (int i=0; i<m_iNumOfElements; i++)
	{
		res[i] = new int[cols];
	}

	for (int i = 0; i < rows; i++)
	{
		res[(*m_vParts)[i].getRow()][(*m_vParts)[i].getCol()] = (*m_vParts)[i].getId();
	}

	return res;
}


int Puzzle::print()
{
	int** final = Puzzle::finalPuzzle();
	for (int i = 0; i < sizeof(final); i++) //rows
	{
		for (int j = 0; j < sizeof(final[0]); j++) //cols
		{
			fprintf(m_fOutput, "%d ", final[i][j]);
		}
		fprintf(m_fOutput, "\n");
	}

	return 0;
}
