#ifndef DATAMAP_H
#define DATAMAP_H

#include "Puzzle2dPiece.h"
#include <map>

using namespace std;

template<int Order, int K>
class DataMap
{
	map<int, DataMap<Order - 1, K>> _map;
	static const int joker = std::numeric_limits<int>::min();

public:
	void insert(Puzzle2dPiece<K>* p) {
		//gets the Order's coordinate *from the end* of Part
		int dim  = p->getDimension();
		int coor = p->getCoorAt(dim-Order);

		//if new entry, create a list for it
		if (_map.find(coor) == _map.end()) //element not found
			_map[coor] = DataMap<Order - 1, K>();

		//recursively insert to lower level
		_map[coor].insert(p);
		_map[joker].insert(p);
	}

	list<Puzzle2dPiece<K>*> get(Puzzle2dPiece<K>* p) {
		int dim =  p->getDimension();
		int coor = p->getCoorAt(dim - Order);
		
		if (_map.find(coor) != _map.end()) //element found
			return _map[coor].get(p);

		return list<Puzzle2dPiece<K>*>();
	}
};

template<int K>
class DataMap<1, K>
{
	map<int, list<Puzzle2dPiece<K>*>> _map;
	static const int joker = std::numeric_limits<int>::min();

public:
	void insert(Puzzle2dPiece<K>* p) {
		//gets the last coordinate *from the end* of Part
		int dim = p->getDimension();
		int coor = p->getCoorAt(dim - 1);

		//if new entry, create a list for it
		if (_map.find(coor) == _map.end()) //element not found
			_map[coor] = list<Puzzle2dPiece<K>*>();

		//actually insert part to list
		_map[coor].push_back(p);
		_map[joker].push_back(p);
	}

	 list<Puzzle2dPiece<K>*> get(Puzzle2dPiece<K>* p) {
		int dim = p->getDimension();
		int coor = p->getCoorAt(dim - 1);

		if (_map.find(coor) != _map.end()) //element found
			return _map[coor];

		return list<Puzzle2dPiece<K>*>();
	}

};

#endif