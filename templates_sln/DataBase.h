#ifndef DATABASE_H
#define DATABASE_H

#include "DataMap.h"
#include "Puzzle2dPiece.h"
#include <iostream>

using namespace std;


template<int DIM, int K>
class DataBase 
{
	DataMap<DIM,K> _map;

public:
	DataBase(typename list<Puzzle2dPiece<K>>::iterator _begin, typename list<Puzzle2dPiece<K>>::iterator _end)
	{
		for (auto& it = _begin; it != _end; it++)
		{
			_map.insert(&(*it));
		}
	}

	list<Puzzle2dPiece<K>*> get(int a, int b, int c, int d)
	{

		Puzzle2dPiece<K> p(a, b, c, d);
		return _map.get(&p);
		

	}




};






#endif