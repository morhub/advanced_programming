#ifndef PUZZLEPIECE_H
#define PUZZLEPIECE_H

#include <vector>
#include <iostream>
#include <list>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;


class PuzzlePiece {
protected:
	vector<int> _coordinates;

	//private constructor to disable instantiation of abstract class
	PuzzlePiece() {};

public:
	vector<int>::iterator begin() { return _coordinates.begin(); }
	vector<int>::iterator end() { return _coordinates.end(); }
	int getCoorAt(int t)const { return _coordinates.at(t); }
};
#endif