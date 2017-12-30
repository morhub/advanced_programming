#ifndef TABLE_H
#define TABLE_H

#include <iostream>
#include <fstream>
#include "Puzzle.h"

class Puzzle; 

class Table
{
	int m_iRows;
	int m_iCols;
	int** m_iTable;
	bool m_bSolved;

public:
	Table(unsigned int rows=0, unsigned int cols=0, bool solved=false);
	~Table();
	Table(const Table&);
	Table& operator=(const Table&);

	int getRows()const { return m_iRows; }
	int getCols()const { return m_iCols; }
	int getSize() { return m_iRows * m_iCols; }
	int** getTable() {return m_iTable; }
	virtual void print(std::ofstream& fout, Puzzle* puz);
	void setSolved() { m_bSolved = true; }
	bool isSolved() { return m_bSolved; }
	bool isEmpty() { return m_iTable == NULL; }
};


#endif
