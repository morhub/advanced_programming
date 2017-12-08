#include <fstream>
#include <string>
#include <cstring>
#include <iostream>
#include <assert.h> 
#include "Puzzle.h"
#include <algorithm>
#include <memory>

using std::getline;
using std::string;
using std::endl;
using std::pair;



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
	std::vector<string> wrongIds, missingIds;
	std::vector<pair<int, string>> wrongFormats;
	input.open(path);
	if (!input.is_open()) {
		*fout << "Failed to open input file" << endl;
		return -EINVAL;
	}

	getline(input, line);
	pos = line.find("=");
	if (pos != string::npos) {
		token = line.substr(0, pos);
		if (token.length() < 11 ||
			token.compare(0, 11, "NumElements")) {
			*fout << "Invalid first line in input file" << endl;
			rc = -EINVAL;
		}
		else
			line.erase(0, pos + 1);

		token = line.substr(line.find_first_not_of(" "), string::npos);
		std::istringstream buf(token);

		buf >> m_iNumOfElements;
		if (m_iNumOfElements < 1) {
			*fout << "Invalid NumOfElements" << endl;
		}
	}
	std::vector<shared_ptr<Part>> *Parts = new std::vector<shared_ptr<Part>>(m_iNumOfElements);

	while (input && getline(input, line) && line.length()!=0) {
		int id, left, up, right, down, eol;
		std::istringstream iss;
		iss.str(line);

		iss >> id;
		if (iss.fail()) {
			wrongIds.emplace_back(std::to_string(id));
			rc = -1;
			continue;
		}

		if (id <= 0 || id > (int)m_iNumOfElements) {
			wrongIds.emplace_back(std::to_string(id));
			rc = -1;
			continue;
		}


		iss >> left;
		if (iss.fail() || abs(left)>1 ) {
			wrongFormats.emplace_back(make_pair(id, line));
			rc = -1;
			continue;
		}
	
		iss >> up;
		if(iss.fail() || abs(up)>1) {
			wrongFormats.emplace_back(make_pair(id, line));
			rc = -1;
			continue;
		}
	
		iss >> right;
		if(iss.fail() || abs(right)>1) {
			wrongFormats.emplace_back(make_pair(id, line));
			rc = -1;
			continue;
		}
	
		iss >> down;
		if(iss.fail() || abs(down)>1) {
			wrongFormats.emplace_back(make_pair(id, line));
			rc = -1;
			continue;
		}
	
		iss >> eol;
		if(!iss.fail() || !iss.eof()) {
			wrongFormats.emplace_back(make_pair(id, line));
			rc = -1;
			continue;
		}

		Parts->at(id-1) = make_shared<Part>(id, left, up, right, down);


	}

	for (int i = 0; i < (int)Parts->size(); i++) {
		Part& p = *Parts->at(i);
		if(!p.getId()) { //only missing, not wrong ID
			missingIds.emplace_back(std::to_string(i+1));
			rc = -1;
		}
	}


	if ((int)missingIds.size() > 0)
	{
		bool printEndl = false; 
		bool firstRound = true;
		for (int i = 0; i < (int)missingIds.size(); i++)
		{
			string deli = 
				(i == (int)missingIds.size() - 1) ? "" : ", ";
			//print only if part is not a wrong-format ID
			auto itr = find_if(wrongFormats.begin(), wrongFormats.end(),
				[id = missingIds.at(i)](const auto& format) {
				return std::to_string(format.first) == id;
			});
			if (itr == wrongFormats.end())
			{
				if (firstRound)
				{
					*fout << "Missing puzzle element(s) with the following IDs: ";
					firstRound = false;
				}
				*fout << missingIds[i] << deli;
				printEndl = true;
			}	
		}
		if(printEndl)
			*fout << endl;
	}

	if ((int)wrongIds.size() > 0)
	{
		*fout << "Puzzle of size " << m_iNumOfElements << " cannot have the following IDs: ";
		for (int i = 0; i < (int)wrongIds.size(); i++)
		{
			string deli =
				(i == (int)wrongIds.size() - 1) ? "" : ", ";
			*fout << wrongIds[i] << deli;
		}
		*fout << endl;
	}

	for (const pair<int, string> &line : wrongFormats)
	{
		*fout << "Puzzle ID " << line.first << " has wrong data: " << line.second << endl;
	}
	m_vParts = Parts;
	return rc;
}


int Puzzle::solveRec(size_t i, size_t j, Table& tab)
{
	//if(i>1)
	//	cout << "i:" << i << ", j:" << j << endl;

	int** table = tab.getTable();
	list<pair<list<shared_ptr<Part>>*, int>> matches;

	int leftpeek, toppeek, rightpeek, bottompeek;
	rightpeek = bottompeek = -2; //there is no part to the right/bottom
	leftpeek  = toppeek    = 0; //there is a frame part to the left/top

	if (j > 0 && table[i][j - 1] >= 0)
	{
		int angle = (*m_vParts)[table[i][j - 1] - 1]->getRotation();
		leftpeek = 0 - ((*m_vParts)[table[i][j - 1] - 1]->getRightAfterRotate(angle));
	}
	if (i > 0 && table[i - 1][j] >= 0)
	{
		int angle = (*m_vParts)[table[i - 1][j] - 1]->getRotation();
		toppeek = 0 - ((*m_vParts)[table[i - 1][j] - 1]->getBottomAfterRotate(angle));
	}
	if(j == (size_t)tab.getCols() - 1)   //last in line (e.g. frame part)
		rightpeek = 0;
	if (i == (size_t)tab.getRows() - 1) //last in col (e.g frame part)
		bottompeek = 0;

	if (rightpeek == -2 && bottompeek == -2) //common case in our algorithm
		matches = m_mMatches[make_pair(leftpeek, toppeek)];
	else
		matches = getMatches(leftpeek, toppeek, rightpeek, bottompeek);

	//We always check the top-left directions - 
	//solve the puzzle from top-left to bottom-right
	for (auto& match : matches)
	{
		list<shared_ptr<Part>>* matchlist = match.first;
		int rotation = match.second;

		//no parts of this left-top edges are avilable
		if (matchlist->empty())
			continue;

		//if we got so far, we have match in this list - continue checking this part
		shared_ptr<Part> current = matchlist->front();
		matchlist->pop_front();
		current->addRotation(rotation);
		table[i][j] = current->getId();
		
		//End of table
		if ((i == (size_t)tab.getRows() - 1) && (j == (size_t)tab.getCols() - 1))
			return 0; //solve succeeded

		//End of line
		if (j == (size_t)tab.getCols() - 1)
		{
			if (solveRec(i + 1, 0, tab) == 0) //move to the next line, and first column
				return 0;
			else
			{
				table[i][j] = 0;
				current->addRotation(-rotation);
				matchlist->push_back(current);
				continue;
			}
		}
		else // "middle" cell in line
		{
			if (solveRec(i, j + 1, tab) == 0) //continue solving along the current line
				return 0;
			else
			{
				table[i][j] = 0;
				current->addRotation(-rotation);
				matchlist->push_back(current);
				continue;
			}
		}
	}
	return -1;
}

Table Puzzle::Solve()
{
	unsigned int i;
	int ret;
	unsigned int size = m_iNumOfElements;
	
	preComputeCommonCase();

	for(i = 1; i <= size; i++) {
		if (size % i == 0) {
			if (!isValidStraightEdges(i, size / i))
				continue;
				
			Table table(i, size/i); 
			cout << "size:" << i << " X " << size / i << endl << endl;
			if(i!=2 && i!=3)
				ret = solveRec(0, 0, table);
			if (ret == 0)
			{
				return table;
			}
		}
	}
	
	*fout << "Cannot solve puzzle : it seems that there is no proper solution" << endl;
	
	return Table();
}

int Puzzle::preProcess()
{
	int sum = 0;
	bool tr = false;
	bool tl = false;
	bool br = false;
	bool bl = false;
	int ret = 0;

	if (cornerCheck(tr, tl, br, bl) == false) 
	{
		ret = -1;
		if (tl == false)
			*fout << "Cannot solve puzzle: missing corner element: TL" << endl;
		if (tr == false)
			*fout << "Cannot solve puzzle: missing corner element: TR" << endl;
		if (bl == false)
			*fout << "Cannot solve puzzle: missing corner element: BL" << endl;
		if (br == false)
			*fout << "Cannot solve puzzle: missing corner element: BR" << endl;
	}

	for (size_t i = 0; i < m_iNumOfElements; i++)
	{
		sum += (*m_vParts)[i]->getLeft();
		sum += (*m_vParts)[i]->getTop();
		sum += (*m_vParts)[i]->getRight();
		sum += (*m_vParts)[i]->getBottom();
	}
	if (sum != 0)
	{
		*fout << "Cannot solve puzzle : sum of edges is not zero" << endl;
		ret = -1;
	}

	return ret;
}

void Puzzle::preComputeCommonCase()
{
	//pre-compute the common case (no right,bottom edges)
	for (int i = -1; i < 2; i++)
		for (int j = -1; j < 2; j++)
			m_mMatches[make_pair(i, j)] = getMatches(i, j, -2, -2);
}