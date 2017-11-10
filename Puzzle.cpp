#include <fstream>
#include <string>
#include <cstring>
#include <iostream>
#include <assert.h> 
#include "Puzzle.h"


using std::getline;
using std::string;
using std::cout;
using std::endl;

Part framePart(-1);

Puzzle::Puzzle() 
{
	m_vParts = NULL;
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

	if ((int)missingIds.size() > 0)
	{
		cout << "Missing puzzle element(s) with the following IDs: ";
		for (int i = 0; i < (int)missingIds.size(); i++)
		{
			string deli = (i == (int)missingIds.size() - 1) ?
				"" : ", ";
			cout << missingIds[i] << deli;
		}
		cout << endl;
	}

	*fout << "Puzzle of size <SIZE> cannot have the following IDs: ";
	for(string s : wrongIds)
		*fout << s << ", ";
	*fout << endl;
	
	for (string s : wrongFormats)
	{
		*fout << "Puzzle ID " ;
		*fout << s;
		*fout << " has wrong data: "<< endl;
	}
	m_vParts = Parts;
	return rc;
}


int Puzzle::solveRec(size_t i, size_t j, Table& tab)//Table& table
{
	bool isPartMatch = true;
	int** table = tab.getTable(); 

	for(size_t k = 0; k < m_iNumOfElements; k++)
	{
		Part& current = (*m_vParts)[k];
		assert(table[i - 1][j]); //  top edge of the frame - false when 0
		assert(table[i][j-1]);  //	left edge of the frame - false when 0
	
		//We always check the left and top directions - 
		//solve the puzzle from top-left to bottom-right
		
		if ((table[i - 1][j]) == -1) //the top frame 
		{
			if (!current.isConnectedTo(framePart, TOP))
			{
				isPartMatch = false;
			}
		}
		else
		{
			if (!current.isConnectedTo((*m_vParts)[table[i - 1][j]], TOP))
			{
				isPartMatch = false;
			}
		}
		

		if (table[i][j - 1] == -1) // the left frame
		{
			if (!current.isConnectedTo(framePart, LEFT))
			{
				isPartMatch = false;
			}
		}
		else
		{
			if (!current.isConnectedTo((*m_vParts)[table[i][j - 1]], LEFT))
			{
				isPartMatch = false;
			}
		}
		

		if (table[i][j + 1] != 0) // right edge of the frame is here
		{
			if (!current.isConnectedTo(framePart, RIGHT))
			{
				isPartMatch = false;
			}
		}


		if (table[i+1][j] != 0) // bottom edge of the frame is here
		{
			if (!current.isConnectedTo(framePart, BOTTOM))
			{
				isPartMatch = false;
			}
		}

		if (isPartMatch) // this part is matched to the current place of the table
		{
			table[i][j] = current.getId();

			//End of table
			if ((i == tab.getCols() - 1) && (j == tab.getRows() - 1))
				return 0; //solve succeeded

			//End of line
			if (i == tab.getCols() - 1)
			{
				if (solveRec(i + 1, 1, tab) == 0) //move to the next line, and first column
					return 0;
				else
					continue;
			}
			else
			{
				if (solveRec(i, j + 1, tab) == 0) //continue solving along the current line
					return 0;
				else
					continue;
			}
		}
		else
			continue;
	}
	tab.clean(i, j);
	return -1;

}

Table Puzzle::Solve()
{
	int i, ret;
	int size = m_iNumOfElements;

	for(i = 0; i < size; i++) {
		if (size % i == 0) {
			Table table(i+2, size/i+2); //+2 for margins of size 1
			table.setFrame(-1);
			ret = solveRec(1, 1, table);
			if (ret == 0)
				return table;
		}
	}
	return Table();
}

int Puzzle::preProcess()
{
	int sum = 0; 
	int topStraight = 0;
	int bottomStraight = 0;
	int leftStraight = 0;
	int rightStraight = 0;
	bool tr, tl, br, bl = false;

	for (size_t i = 0; i < m_iNumOfElements; i++)
	{
		int left =   (*m_vParts)[i].getLeft();
		int top =    (*m_vParts)[i].getTop();
		int right =  (*m_vParts)[i].getRight();
		int bottom = (*m_vParts)[i].getBottom();

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

		sum += (*m_vParts)[i].getLeft();
		sum += (*m_vParts)[i].getTop();
		sum += (*m_vParts)[i].getRight();
		sum += (*m_vParts)[i].getBottom();
	}

	if (topStraight != bottomStraight || leftStraight != rightStraight)
		*fout <<  "Cannot solve puzzle: wrong number of straight edges\n" << endl;

	if (tl == false)
		*fout << "Cannot solve puzzle: missing corner element: TL" << endl;
	if (tr == false)
		*fout << "Cannot solve puzzle: missing corner element: TR" << endl;
	if (bl == false)
		*fout << "Cannot solve puzzle: missing corner element: BL" << endl;
	if (br == false)
		*fout << "Cannot solve puzzle: missing corner element: BR" << endl;

	if (sum != 0)
		*fout << "Cannot solve puzzle : sum of edges is not zero" << endl;

	return 0;
}
