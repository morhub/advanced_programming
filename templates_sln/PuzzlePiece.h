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
	const size_t _range;
	PuzzlePiece(int range) : _range(range) {};

public:
	vector<int>::iterator begin() { return _coordinates.begin(); }
	vector<int>::iterator end() { return _coordinates.end(); }

	const vector<int>& getCoors()const { return _coordinates; }
	size_t getRange() { return _range; }
	int getCoorAt(int t) { return _coordinates.at(t); }
	int getDimension() { return _coordinates.size(); }
};





#endif