#ifndef TABLE_H
#define TABLE_H
#include <iostream>
#include <fstream>

class Table
{
	const unsigned int m_iRows;
	const unsigned int m_iCols;
	int** m_iTable;

public:
	Table(unsigned int rows=0, unsigned int cols=0);
	~Table();
	Table(const Table&);
	Table& operator=(const Table&) = delete;

	int getRows() { return m_iRows; }
	int getCols() { return m_iCols; }
	int getSize() { return m_iRows * m_iCols; }
	int** getTable() {return m_iTable; }
	void setFrame(int);
	void print(std::ofstream&);
	void clean(int x=0, int y=0, int marginSize=0);

};
#endif
