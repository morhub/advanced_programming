#ifndef DATAMAP_H
#define DATAMAP_H

#include <map>

using namespace std;
static const int joker = std::numeric_limits<int>::min();

/* DataMap - Recursively Templated Data structure.
 * Each i-Order templated class holds a mapping
 * w.r.t the i-th coordinate in DataType class.
 */
template<typename DataType, size_t Order>
class DataMap
{
	map<int, DataMap<DataType, Order - 1>> _map;

public:
	void insert(DataType* p) {
		int dim  = p->Dimension;
		int coor = p->getCoorAt(dim-Order);

		//if new entry, create a list for it
		if (_map.find(coor) == _map.end())
			_map[coor] = DataMap<DataType, Order - 1>();

		//recursively insert to lower level
		_map[coor].insert(p);
		_map[joker].insert(p);
	}

	const list<DataType*>* get(DataType* p) {
		int dim =  p->Dimension;
		int coor = p->getCoorAt(dim - Order);
		
		if (_map.find(coor) != _map.end())
			return _map[coor].get(p);

		return nullptr;
	}
};

/* DataMap<1> - Base for Recursive Templated Data structure.
 * Holds a mapping w.r.t the last coordinate in DataType class.
 * Practically implements the DB interface (insert, get) by directly
 * insert to / retrieve from the relevat list. 
 */
template<typename DataType>
class DataMap<DataType, (size_t)1>
{
	map<int, list<DataType*>> _map;

public:
	void insert(DataType* p) {
		int dim = p->Dimension;
		int coor = p->getCoorAt(dim - 1);

		//if new entry, create a list for it
		if (_map.find(coor) == _map.end())
			_map[coor] = list<DataType*>();

		//actually insert part to list
		_map[coor].push_back(p);
		_map[joker].push_back(p);
	}

	 const list<DataType*>* get(DataType* p) {
		int dim = p->Dimension;
		int coor = p->getCoorAt(dim - 1);

		if (_map.find(coor) != _map.end())
			return &_map[coor];

		return nullptr;
	}
};

#endif