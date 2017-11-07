#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <iostream>
#include "Puzzle.h"
//

using std::getline;
using std::string;
using std::cout;
using std::endl;


Puzzle::Puzzle(std::ofstream *out)
{
	fout = out;
	m_iNumOfCols = m_iNumOfRows = -1;
}

Puzzle::~Puzzle()
{
	if (m_vParts)
		delete m_vParts;
}

int Puzzle::init(std::string path)
{
	int rc = 0;
	size_t pos;
	string line, token;
	std::ifstream input;
	std::vector<string> wrongIds, wrongFormats, missingIds;
	input.open(path);
	if (!input.is_open()) {
		perror("Failed to open input file\n");
		return -EINVAL;
	}

	getline(input, line);
	pos = line.find("=");
	if (pos != string::npos) {
		token = line.substr(0, pos);
		if (token.length() < 11 ||
			token.compare(0, 11, "NumElements")) {
			perror("Invalid first line in input file\n");
			rc = -EINVAL;
		} else
			line.erase(0, pos + 1);

		token = line.substr(line.find_first_not_of(" "), string::npos);
		std::istringstream buf(token);

		buf >> m_iNumOfElements;
		if (m_iNumOfElements < 1) {
			perror("Invalid NumOfElements\n");
		}
	}
	std::vector<Part> *Parts = new std::vector<Part>(m_iNumOfElements);
	
	while (input && getline(input, line)) {
		int id, left, up, right, down, eol;
		std::istringstream iss;
		iss.str(line);
		cout << "line: " << line << endl;

		iss >> id;
		if(iss.fail()) {
			wrongFormats.emplace_back(line);
			rc = -1;
			continue;
		}

		iss >> left;
		if(iss.fail()) {
			wrongFormats.emplace_back(line);
			rc = -1;
			continue;
		}
	
		iss >> up;
		if(iss.fail()) {
			wrongFormats.emplace_back(line);
			rc = -1;
			continue;
		}
	
		iss >> right;
		if(iss.fail()) {
			wrongFormats.emplace_back(line);
			rc = -1;
			continue;
		}
	
		iss >> down;
		if(iss.fail()) {
			wrongFormats.emplace_back(line);
			rc = -1;
			continue;
		}
	
		iss >> eol;
		if(!iss.fail() || !iss.eof()) {
			wrongFormats.emplace_back(line);
			rc = -1;
			continue;
		}
	
		if(id <= 0 || id > (int)m_iNumOfElements) {
			wrongIds.emplace_back(std::to_string(id));
			rc = -1;
			continue;
		}

		Parts->at(id-1) = Part(id, left, up, right, down);
	}

	for (int i = 0; i < (int)Parts->size(); i++) {
		Part& p = Parts->at(i);
		if(!p.getId()) { //only missing, not wrong ID
			missingIds.emplace_back(std::to_string(i+1));
			rc = -1;
		}
	}

	cout << "missing ids: ";
	for(string s : missingIds)
		cout << s << ",";
	cout << endl;

	cout << "wrong ids: ";
	for(string s : wrongIds)
		cout << s << ",";
	cout << endl;

	cout << "wrong formats:" << endl;
	for(string s : wrongFormats)
		cout << s << endl;
	cout << endl;
	m_vParts = Parts;
	return rc;
}


int Puzzle::Solve()
{
	return true;
}


int Puzzle::preProcess()
{
	int sum = 0;
	int topStraight = 0;
	int bottomStraight = 0;
	int leftStraight = 0;
	int rightStraight = 0;
	bool tr, tl, br, bl = false;

	for (std::vector<Part>::size_type i = 0; i != m_vParts->size(); i++)
	{
		int left = (*m_vParts).at(i).getLeft();
		int top = (*m_vParts).at(i).getTop();
		int right = (*m_vParts).at(i).getRight();
		int bottom = (*m_vParts).at(i).getBottom();

		if (left == 0)
			leftStraight++;
		if (top == 0)
			topStraight++;
		if (right == 0)
			rightStraight++;
		if (bottom == 0)
			bottomStraight++;

		if (top == 0 && right == 0)
			tr = true;
		if (top == 0 && left == 0)
			tl = true;
		if (bottom == 0 && right == 0)
			br = true;
		if (bottom == 0 && left == 0)
			bl = true;

		sum += (*m_vParts).at(i).getLeft();
		sum += (*m_vParts).at(i).getTop();
		sum += (*m_vParts).at(i).getRight();
		sum += (*m_vParts).at(i).getBottom();
	}

	if (topStraight != bottomStraight || leftStraight != rightStraight)
		*fout <<  "Cannot solve puzzle: wrong number of straight edges\n" << endl;

	if (tl == false)
		*fout << "Cannot solve puzzle: missing corner element: TL\n" << endl;
	if (tr == false)
		*fout << "Cannot solve puzzle: missing corner element: TR\n" << endl;
	if (bl == false)
		*fout << "Cannot solve puzzle: missing corner element: BL\n" << endl;
	if (br == false)
		*fout << "Cannot solve puzzle: missing corner element: BR\n" << endl;

	if (sum != 0)
		*fout << "Cannot solve puzzle : sum of edges is not zero" << endl;

	return 0;
}

int** Puzzle::finalPuzzle()
{
	size_t rows = m_iNumOfRows;
	size_t cols = m_iNumOfCols;
	int** res = new int*[rows];
	unsigned int i;

	for (i=0; i<m_iNumOfElements; i++)
	{
		res[i] = new int[cols];
	}

	for (i = 0; i < rows; i++)
	{
		res[(*m_vParts)[i].getRow()][(*m_vParts)[i].getCol()] = (*m_vParts)[i].getId();
	}

	return res;
}


int Puzzle::print()
{
	int** final = Puzzle::finalPuzzle();
	unsigned int i, j;

	for (i = 0; i < sizeof(final); i++) //rows
	{
		for (j = 0; j < sizeof(final[0]); j++) //cols
		{
			*fout << final[i][j] << " ";
		}
		*fout << endl;
	}

	return 0;
}

