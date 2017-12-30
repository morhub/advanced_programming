#include "Table.h"
#include <string>
#include <iostream>

using std::string;
using std::endl;
using namespace std;


Table::Table(unsigned int rows, unsigned int cols):
	m_iRows(rows),
	m_iCols(cols),
	m_bSolved(false)
{
	unsigned int i;

	if(m_iRows > 0 && m_iCols > 0) {
		m_iTable = new int*[m_iRows];
		for (i = 0; i < m_iRows; i++)
			m_iTable[i] = new int[m_iCols]();
	} else
		m_iTable = NULL;
}

Table::~Table()
{
	unsigned int i;

	if(m_iRows > 0 && m_iCols > 0) {
		for (i = 0; i < m_iRows; i++)
			delete m_iTable[i];
		delete m_iTable;
	}
}

Table::Table(const Table& table):
	Table(table.m_iRows,
		  table.m_iCols)
{
	unsigned int i, j;
	for (i = 0; i < table.m_iRows; i++)
		for (j = 0; j < table.m_iCols; j++)
			m_iTable[i][j] = table.m_iTable[i][j];
}


void Table::print(std::ofstream& fout, Puzzle* puz)
{
	unsigned int i, j;
	string deli;
	for (i = 0; i < m_iRows; i++) {
		for (j = 0; j < m_iCols; j++) {
			if (j == m_iCols - 1)
				deli = "\n";
			else
				deli = " ";
			int r = puz->getPartAt(m_iTable[i][j] - 1)->getRotation();
			if(r != 0 )
				fout << m_iTable[i][j] << " [" << r*90 << "] " << deli;
			else
				fout << m_iTable[i][j] << deli;
		}
	}
}
