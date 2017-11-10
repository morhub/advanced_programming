#ifndef TABLE_H
#define TABLE_H

class Table
{
	const size_t m_iRows;
	const size_t m_iCols;
	int** m_iTable;

public:
	Table(size_t rows=0, size_t cols=0);
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
