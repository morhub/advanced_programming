#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <assert.h> 
#include "Puzzle.h"
#include <algorithm>
#include <memory>
#include <chrono>
#include <ctime>
#include <future>
#include <thread>


using std::getline;
using std::string;
using std::endl;
using std::pair;
using std::mutex;
using std::lock;

//static std::mutex print_mutex;

//static global variable that should signal all threads that
//someone has got a solution to the problem and they can close themselves
static bool winner = false;


Table foo(int i) {
	return Table();
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
	shared_ptr<vector<Part>> Parts = make_shared<vector<Part>>(m_iNumOfElements);

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

		Parts->at(id-1) = *(new Part(id, left, up, right, down));


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
	m_vParts = *Parts;
	return rc;
}



void Puzzle::computePeeks(int& leftpeek, int& toppeek, int& rightpeek, int& bottompeek, int**& table, 
	vector<Part>& vParts, size_t i, size_t j, Table& tab)
{
	if (j > 0 && table[i][j - 1] >= 0)
	{
		int angle = (vParts)[table[i][j - 1] - 1].getRotation();
		leftpeek = 0 - ((vParts)[table[i][j - 1] - 1].getRightAfterRotate(angle));
	}
	if (i > 0 && table[i - 1][j] >= 0)
	{
		int angle = (vParts)[table[i - 1][j] - 1].getRotation();
		toppeek = 0 - ((vParts)[table[i - 1][j] - 1].getBottomAfterRotate(angle));
	}
	
	if (j == (size_t)tab.getCols() - 1)   //last in line (e.g. frame part)
		rightpeek = 0;
	if (i == (size_t)tab.getRows() - 1) //last in col (e.g frame part)
		bottompeek = 0;

}

bool Puzzle::EndOfTable(size_t i, size_t j, Table& tab)
{
	return (i == (size_t)tab.getRows() - 1) && (j == (size_t)tab.getCols() - 1);
}


bool Puzzle::EndOfLine(size_t j, Table& tab)
{
	return (j == (size_t)tab.getCols() - 1);
}


int Puzzle::solveRec(size_t i, size_t j, Table& tab, common_match_t& cm, full_match_t& fm, vector<Part>& vParts)
{
	if (winner) //another thread already won, this thread need to finish
		return -1;

	int** table = tab.getTable();
	list<pair<list<Part*>*, list<int>>> matches;

	int leftpeek, toppeek, rightpeek, bottompeek;
	rightpeek = bottompeek = -2; //there is no part to the right/bottom
	leftpeek  = toppeek    = 0; //there is a frame part to the left/top

	computePeeks(leftpeek, toppeek, rightpeek, bottompeek, table, vParts, i, j, tab);

	/*
	 * We call solveRec a lot of times with the same left, top values,
	 * So we can use memoization to avoid redundant getMatches() computations
	 */
	if (rightpeek == -2 && bottompeek == -2) //common case in our algorithm
		matches = cm[make_pair(leftpeek, toppeek)];
	else
		matches = fm[make_tuple(leftpeek, toppeek, rightpeek, bottompeek)];

	//We always check the top-left directions - 
	//solve the puzzle from top-left to bottom-right
	for (auto& match : matches)
	{
		list<Part*>* matchlist = match.first;
		list<int> rotations = match.second;

		//no parts of this left-top edges are avilable
		if (matchlist->empty())
			continue;

		//if we got so far, we have match in this list - continue checking this part
		Part* current = matchlist->front();
		matchlist->pop_front();
		table[i][j] = current->getId();
		for (auto& rotation : rotations)
		{
			current->addRotation(rotation);

			if(EndOfTable(i, j, tab))
			{
				winner = true;
				return 0; //solve succeeded
			}

			if (EndOfLine(j, tab))
			{
				if (solveRec(i + 1, 0, tab, cm, fm, vParts) == 0) //move to the next line, and first column
					return 0;
				else
				{
					current->addRotation(-rotation);
					continue;
				}
			}
			else // "middle" cell in line
			{
				if (solveRec(i, j + 1, tab, cm, fm, vParts) == 0) //continue solving along the current line
					return 0;
				else
				{
					current->addRotation(-rotation);
					continue;
				}
			}
		}
		table[i][j] = 0;
		matchlist->push_back(current);

	}
	return -1;
}

vector<int> Puzzle::getMostProbableRowSizes()
{
	vector<int> sizes;
	int maxPossibleRows = getMaxPossibleRows();
	for (int i = 1; i <= maxPossibleRows; i++)
	{
		if (m_iNumOfElements % i == 0 && isValidStraightEdges(i, m_iNumOfElements / i))
			sizes.push_back(i);
	}

	int leftStraight = 0;
	int topStraight = 0;
	for (size_t i = 0; i < m_iNumOfElements; i++){
		int left = (m_vParts)[i].getLeft();
		int top =  (m_vParts)[i].getTop();
		if (left == 0)
			leftStraight++;
		if (top == 0)
			topStraight++;
	}

	std::sort(sizes.begin(), sizes.end(), 
		[size = m_iNumOfElements, diff = leftStraight - topStraight]
		(const int a, const int b) -> bool
		{
			int diffa = a - size / a;
			int diffb = b - size / b;
			return (abs(diffa - diff) < abs(diffb - diff));
		}
	);

	return sizes;
}

Table Puzzle::solveThread(const int rows)
{
	Table table(rows, m_iNumOfElements / rows);
	auto vPartsCopy = m_vParts;

	common_match_t cm;
	full_match_t fm;
	createDataBase(vPartsCopy, cm, fm);

	if (Puzzle::solveRec(0, 0, table, cm, fm, vPartsCopy) == 0) {
		table.setSolved();

		m_vParts = vPartsCopy; //the chosen one
	}

	return table;
}

Table Puzzle::Solve(int numThreads)
{
	
	std::chrono::milliseconds span(10);
	vector<std::future<Table>> threads;

	vector<int> possibleRows = getMostProbableRowSizes();
	if (numThreads == 0) {
		common_match_t cm;
		full_match_t fm;
		createDataBase(m_vParts, cm, fm);

		for (const auto& i : possibleRows) {
			Table table(i, m_iNumOfElements / i);
			if (solveRec(0, 0, table, cm, fm, m_vParts) == 0) 
				return table;
		}
	}
	else {
		for (const auto& i : possibleRows) {
			
		/*	print_mutex.lock();
			printf("*** rows %d ***\n", i);
			print_mutex.unlock();*/
			
			if (numThreads > 0) {
				threads.push_back(std::async(std::launch::async, &Puzzle::solveThread, this, i));
				numThreads--;

			} else {
				
			/*	print_mutex.lock();
				printf("Waiting...\n");
				print_mutex.unlock();*/
				
				for (int j = 0; j < (int)threads.size(); j = (j+1) % threads.size())
				{
					if (threads[j].wait_for(span) != std::future_status::timeout) {
						Table table = threads[j].get();
						
						if (table.isSolved()) {
							for (auto& thread : threads) {
								if (thread.valid())
									thread.wait();
							}
							return table;
						}
						else {
							if (!winner)
							{
								threads[j] = std::async(std::launch::async, &Puzzle::solveThread, this, i);
							}
							break;
						}
					}
				}
			}
			if (winner)
				break;
		}

		//wait for last threads to finish too
		for (auto& thread : threads)
			if (thread.valid())
				thread.wait();

		for (auto& thread : threads) {
			if (thread.valid())
			{
				Table& table = thread.get();
				if (table.isSolved())
					return table;
			}
		}
	}
	
	*fout << "Cannot solve puzzle : it seems that there is no proper solution" << endl;

	//empty table, failed to find solution in all threads
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
		sum += (m_vParts)[i].getLeft();
		sum += (m_vParts)[i].getTop();
		sum += (m_vParts)[i].getRight();
		sum += (m_vParts)[i].getBottom();
	}
	if (sum != 0)
	{
		*fout << "Cannot solve puzzle : sum of edges is not zero" << endl;
		ret = -1;
	}

	return ret;
}



