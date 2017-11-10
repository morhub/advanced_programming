#include "Table.h"

Table::Table(size_t rows, size_t cols): m_iRows=rows, m_iCols=cols {
	size_t i;

	if(rows > 0 && cols > 0) {
		m_iTable = new int*[rows];
		for (i = 0; i < rows; i++)
			m_iTable[i] = new int[cols];
	} else
		m_iTable = NULL;
}

Table::~Table() {
	size_t i;

	if(rows > 0 && cols > 0) {
		for (i = 0; i < m_iRows; i++)
			delete m_iTable[i];
		delete m_iTable;
	}
}


Table::Table(const Table& table) {
	size_t i, j;
	Table table_cpy(table.m_iRows, table.m_iCols);

	if(m_iRows > 0 && m_iCols > 0) {
		for(i = 0; i < table.m_iRows; i++)
			for(j = 0; j < table.m_iCols; j++)
				table_cpy.m_iTable[i][j] = table.m_iTable[i][j];
	} else {
		table_cpy.m_iTable = NULL
	}
	return table_cpy;
}


int Table::print(std::ofstream& fout)
{
	size_t i, j;
	string deli;

	for (i = 0; i < m_iRows; i++) {
		for (j = 0; j < m_iCols; j++) {
			deli = (i == m_iRows-1) ? endl : " ";
			fout << m_iTable[i][j] << deli;
		}
	}
}

void Table::setFrame(int value=0) {
	size_t i, j;

	for (i = 0; i < m_iRows; i++)
		m_iTable[i][0] = m_iTable[i][m_iRows-1] = value;

	for (j = 1; j < m_iCols-1; j++)
		m_iTable[0][j] = m_iTable[m_iCols-1][j] = value;
}

void Table::clean(int x, int y, int marginSize) {
	size_t i, j;

	for (i = x; i < rows-marginSize; i++) {
		for (j = y; j < cols-marginSize; j++)
			m_iTable[i][j] = 0;	
		y = marginSize;
	}
}
