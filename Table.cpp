#include "Table.h"
#include <string>
#include <iostream>

using std::string;
using std::endl;

Table::Table(unsigned int rows, unsigned int cols, unsigned int margins):
	m_iRows(rows + 2*margins),
	m_iCols(cols + 2*margins),
	m_iMargin(margins)
{
	unsigned int i;

	if(rows > 0 && cols > 0) {
		m_iTable = new int*[rows];
		for (i = 0; i < rows; i++)
			m_iTable[i] = new int[cols];
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
	m_iRows(table.m_iRows),
	m_iCols(table.m_iCols),
	m_iMargin(table.m_iMargin)
{
	unsigned int i, j;

	if(m_iRows > 0 && m_iCols > 0) {
		for(i = 0; i < table.m_iRows; i++)
			for(j = 0; j < table.m_iCols; j++)
				m_iTable[i][j] = table.m_iTable[i][j];
	} else {
		m_iTable = NULL;
	}
}


void Table::print(std::ofstream& fout)
{
	unsigned int i, j;
	string deli;

	for (i = m_iMargin; i < m_iRows-m_iMargin; i++) {
		for (j = m_iMargin; j < m_iCols-m_iMargin; j++) {
			if (i == m_iRows-m_iMargin - 1)
				deli = "\n";
			else
				deli = " ";
			fout << m_iTable[i][j] << deli;
		}
	}
}

void Table::setFrame(int value=0) {
	unsigned int i, j;

	for (i = 0; i < m_iRows; i++)
		m_iTable[i][0] = m_iTable[i][m_iRows-1] = value;

	for (j = 1; j < m_iCols-1; j++)
		m_iTable[0][j] = m_iTable[m_iCols-1][j] = value;
}

void Table::clean(int x, int y) {
	unsigned int i, j;

	for (i = x + m_iMargin; i < m_iRows - m_iMargin; i++) {
		for (j = y; j < m_iCols - m_iMargin; j++)
			m_iTable[i][j] = 0;	
		y = m_iMargin;
	}
}
