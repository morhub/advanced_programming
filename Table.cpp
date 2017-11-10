#include "Table.h"

Table::Table(int rows, int cols) {
	int i;

	m_iRows = rows;
	m_iCols = cols;

	m_iTable = new int*[rows];
	for (i = 0; i < rows; i++)
		m_iTable[i] = new int[cols];
}

Table::~Table() {
	int i;

	for (i = 0; i < m_iRows; i++)
		delete m_iTable[i];
	delete m_iTable;
}

/*
Table::Table(const Table& table) {
	int i, j;
	Table table_cpy(table.m_iRows, table.m_iCols);

	for(i = 0; i < table.m_iRows; i++)
		for(j = 0; j < table.m_iCols; j++)
			table_cpy.m_iTable[i][j] = table.m_iTable[i][j];

	return table_cpy;
}
*/

int Table::print(std::ofstream& fout)
{
	int i, j;
	string deli;

	for (i = 0; i < m_iRows; i++) {
		for (j = 0; j < m_iCols; j++) {
			deli = (i == m_iRows-1) ? endl : " ";
			fout << m_iTable[i][j] << deli;
		}
	}
}

void Table::setFrame(int value=0) {
	int i, j;

	for (i = 0; i < rows; i++)
		m_iTable[i][0] = m_iTable[i][rows-1] = value;

	for (j = 1; j < cols-1; j++)
		m_iTabl0[0][j] = m_iTable[cols-1][j] = value;
}

void Table::clean(int x=0, int y=0, marginSize=0) {
	int i, j;

	for (i = x; i < rows-marginSize; i++) {
		for (j = y; j < cols-marginSize; j++)
			m_iTable[i][j] = 0;	
		y = marginSize;
	}
}
