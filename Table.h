#ifndef TABLE_H
#define TABLE_H

class Table
{
	int m_iRows, m_iCols;
	int** m_iTable;

public:
	Table(int, int);
	~Table();
	/* We use copy c'tor, but we are satisfied with
	 * with shallow copy
	 */
	Table(const Table&) = delete;
	Table& operator=(const Table&) = delete;

	print(std::ofstream&);
	int getRows() { return m_iRows; }
	int getCols() { return m_iCols; }
	int getSize() { return m_iRows * m_iCols; }
	int** getTable() {return m_iTable; }
	void setFrame(int);
};
#endif
