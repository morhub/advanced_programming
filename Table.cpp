#include "Table.h"
#include <string>
#include <iostream>

using std::string;
using std::endl;
using namespace std;


Table::Table(unsigned int rows, unsigned int cols, bool solved):
	m_iRows(rows),
	m_iCols(cols),
	m_bSolved(solved)
{
	if(m_iRows > 0 && m_iCols > 0) {
		m_iTable = new int*[m_iRows];
		for (int i = 0; i < m_iRows; i++)
			m_iTable[i] = new int[m_iCols]();
	} else
		m_iTable = NULL;
}

Table::~Table()
{
	if(m_iRows > 0 && m_iCols > 0) {
		for (int i = 0; i < m_iRows; i++)
			delete m_iTable[i];
		delete m_iTable;
	}
}

Table::Table(const Table& table):
	Table(table.m_iRows,
		  table.m_iCols,
		  table.m_bSolved)
{
	for (int i = 0; i < (int)table.m_iRows; i++)
		for (int j = 0; j < (int)table.m_iCols; j++)
			m_iTable[i][j] = table.m_iTable[i][j];
}

Table& Table::operator=(const Table& table)
{
	if (m_iRows > 0 && m_iCols > 0) {
		for (int i = 0; i < (int)m_iRows; i++)
			delete m_iTable[i];
		delete m_iTable;
	}

	m_iRows = table.m_iRows;
	m_iCols = table.m_iCols;
	m_bSolved = table.m_bSolved;

	if (m_iRows > 0 && table.getCols() > 0) {
		m_iTable = new int*[m_iRows];
		for (int i = 0; i < m_iRows; i++)
			m_iTable[i] = new int[m_iCols]();
	}

	for (int i = 0; i < m_iRows; i++)
		for (int j = 0; j < m_iCols; j++)
			m_iTable[i][j] = table.m_iTable[i][j];

	return *this;
}

void Table::print(std::ofstream& fout, Puzzle* puz)
{
	string deli;
	for (int i = 0; i < m_iRows; i++) {
		for (int j = 0; j < m_iCols; j++) {
			if (j == m_iCols - 1)
				deli = "\n";
			else
				deli = " ";
			int r = puz->getPartAt(m_iTable[i][j] - 1).getRotation();
			if(r != 0 )
				fout << m_iTable[i][j] << " [" << r*90 << "] " << deli;
			else
				fout << m_iTable[i][j] << deli;
		}
	}
}
