#ifndef TABLE_H
#define TABLE_H
#include <iostream>
#include <fstream>

class Table
{
	const unsigned int m_iRows;
	const unsigned int m_iCols;
	const unsigned int m_iMargin;
	int** m_iTable;

public:
	Table(unsigned int rows=0, unsigned int cols=0, unsigned int margins=0);
	~Table();
	Table(const Table&);
	Table& operator=(const Table&) = delete;

	int getRows() { return m_iRows; }
	int getCols() { return m_iCols; }
	int getMargin() { return m_iMargin; }
	int getSize() { return m_iRows * m_iCols; }
	int** getTable() {return m_iTable; }
	void print(std::ofstream&);
	void clean(int x=0, int y=0);
	void init();

private:
	void setFrame(int);

};
#endif
